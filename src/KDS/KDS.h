#pragma once
#pragma execution_character_set("utf-8")//解决中文乱码

#include <QtWidgets/QWidget>
#include "ui_KDS.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDebug>
#include <QMessageBox>
#include <QDate>
#include <qrandom.h>
#include <QInputDialog>
#include <Eigen/Dense>

#include "MyPBC.h"
#include "ServerSetup.h"
//#include "RegisterLogin.h"

class KDS : public QWidget
{
    Q_OBJECT

public:
    KDS(QWidget *parent = Q_NULLPTR);
    ~KDS();

    
    
private:
    Ui::KDSClass ui;

    QSqlDatabase database;//数据库实例
    MyPBC KDSPBC;//实例化MyPBC类，用来处理PBC库相关元素的初始化等操作
    ServerSetup Server;//实例化ServerSetup类,初始化服务端实例，处理远程连接

    //每次登录注册都要创建RegisterLogin实例，故从KDS中去掉
    //RegisterLogin regLogin;//实例化RegisterLogin类，实现用户的注册与登录逻辑

    //为五个表分别建立model
    QSqlQueryModel* RawParamModel = new QSqlQueryModel(this);
    QSqlQueryModel* AccessPolicyMatrixModel = new QSqlQueryModel(this);
    QSqlQueryModel* UserModel = new QSqlQueryModel(this);
    QSqlQueryModel* LoggedUserModel = new QSqlQueryModel(this);
    QSqlQueryModel* NewUserModel = new QSqlQueryModel(this);

    int connectMYSQL();//连接到Mysql,成功返回0，失败返回-1

    /*
    创建KDS数据库，并创建KDS用到的5个表(如果存在则什么也不做):
    1、初始参数表(RawParam);存储KDS初始化的参数。hx存储h1,h2,...,hx组成的字符串，其中h1为U中第一个属性对应的G1中的元素,U为属性全集、MSK为系统主私钥g_alpha。
       字段:g, e_g_g_alpha, g_a, hx, U, MSK;
     
    2、访问策略矩阵表(AccessPolicyMatrix);存储加密者提供的访问策略等本次加密有关的信息。KDS为本次加密生成MUID(消息唯一标识码)(110个字符)来唯一标识此次加密的原始明文，方便用户解密；同时根据AP(访问策略)生成APM(访问策略矩阵)存储于表中。
       字段:AccessPolicy, APMatrix, MUID;
     
    3、用户表(User);存储注册通过的用户信息。包括用户名、密码、用户属性集S、用户私钥SK。
       字段:name, password, S, SK;
      
    4、新用户表(NewUser);存储新注册的用户信息。等待KDS管理员审核，并为其设置用户属性集S，计算SK存入User表。完成后将其从表中删除。
       字段:name, password;
     
    5、已登录用户表(LoggedUser);存储已经登录KDS的用户信息。当用户登录时KDS为其分配随机定长字符串作为cookie(220个字符)，用户离线时将其从表中删除。
       字段:name, cookie;
    */
    void createKDSAndTable();

    void showRawParam();//显示RawParam表的内容

    void showAccessPolicyMatrix();//显示RawParam表的内容

    void showUser();//显示User表的内容

    void showLoggedUser();//显示LoggedUser表的内容

    void showNewUser();//显示NewUser表的内容

    void showServerIpPort();//显示服务端监听的IPv4和端口

    void insertRawParam(QString&);//根据U生成系统参数PK，MSK等插入RawParam表中

    void insertUser(QString& userName, QString& passwd, QString& S, QString& SK);//将KDS管理员同意注册的用户信息写入User表，代表此用户可以登录

    QString getRandomString(int length);//随机生成length长度，只包含大小写字母和数字的字符串
    
    bool isSvalid(QString& S);//判断用户属性集S中的属性是否在属性全集U中，全部存在则返回true,否则返回false

    void deleteUserFromNewUser(QString& userName);//将用户userName从NewUser表删除，当KDS管理员同意或拒绝时调用

    QString getUserSK(QString& S);//输入用户属性集S，返回用户的私钥SK

    void isExistU();//KDS程序启动后判断数据库是否存在U，存在则禁用输入U(临时策略，系统目前只允许一条属性全集U)

    Eigen::MatrixXd M_AND(Eigen::MatrixXd& m1, Eigen::MatrixXd& m2);//返回m1&m2对应的访问策略矩阵

    Eigen::MatrixXd M_OR(Eigen::MatrixXd& m1, Eigen::MatrixXd& m2);//返回m1|m2对应的访问策略矩阵

    Eigen::MatrixXd toMatrix(QString matrixQstr);//将matrixQstr对应的矩阵还原

    QString MatrixToQString(Eigen::MatrixXd& APM);//将APM矩阵转为QString

    QString getSubTMatrix(QString& MUID, int& firstRow, int& lastRow);//返回MUID对应的APM中的firstRow和lastRow之间(包括firstRow和lastRow)的子矩阵

private slots:
    void on_pushButton_clicked();//输入属性U点击确定按钮触发的槽函数

    void on_pushButton_2_clicked();//从NewUser表中手动删除选中的用户，因为这些用户不符合注册条件

public slots:
    //接受querySignal查询信号，查询queryQstr是否存在tableToQuery表的field字段中，存在则ret赋值为true，不存在赋值为false
    void isExisted(bool& ret, const QString& tableToQuery, const QString& field, const QString& queryQstr);
    
    //接受insertSignal插入信号，将相应用户信息插入tableToQuery表
    void insertNewUser(const QString& tableToQuery, const QString& name, const QString& passwd);
    
    //向User表查询用户名和密码是否匹配
    void matchNamePasswd(bool& ret, const QString& name, const QString& passwd);
    
    //将用户信息写入LoggedUser表，并返回给用户私钥，cookie等信息
    void userLogin(QString name);

    //客户端用户退出时调用，将用户从LoggedUser表删除
    void userLogOut(const QString& name, const QString& cookie);

    //KDS管理员鼠标双击NewUser表中的用户，表示同意此用户注册请求，在弹出的输入框中输入为该用户指定属性集S
    //然后将该用户从NewUser表中删除并存入User表中
    void agreeClickedUser(const QModelIndex&);

    //删除新注册用户的按钮只有当选中item时可用
    void isEnableDeleteButton(const QItemSelection&, const QItemSelection&);

    //判断cookie是否在LoggedUser表中，存在则ret=true否则ret=false
    void matchCookie(bool& ret, const QString& cookie);

    //收到getAPMatrixSignal信号根据访问策略列表APList生成访问策略矩阵并转为QString存入APMatrix,MaxSize为访问策略矩阵行数(访问策略中属性的个数)
    void getAPMatrix(QString& APMatrix, QStringList& APList, int MaxSize);

    //根据APList生成MUID存入给定的MUID中
    void getMUID(QString& MUID, QStringList& APList);

    //将访问策略、访问策略矩阵、MUID插入AccessPolicyMatrix表
    void insertAPM(QString& AccessPolicy, QString& APMatrix, QString& MUID);

    //将访问策略中的属性在U中的位置存入HXNUM中
    void getOrderHx(QString& APQstr, QString& HXNUM);

    //判断cookie对应的用户属性集是否满足MUID对应的访问策略,满足则把满足访问策略的用户属性集的子集中的元素在Kx中的顺序以及相应APM的行顺序存入KxAPMOrder
    void isAbleDecry(QString cookie, QString MUID);
};
