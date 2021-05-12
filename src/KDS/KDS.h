#pragma once
#pragma execution_character_set("utf-8")//�����������

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

    QSqlDatabase database;//���ݿ�ʵ��
    MyPBC KDSPBC;//ʵ����MyPBC�࣬��������PBC�����Ԫ�صĳ�ʼ���Ȳ���
    ServerSetup Server;//ʵ����ServerSetup��,��ʼ�������ʵ��������Զ������

    //ÿ�ε�¼ע�ᶼҪ����RegisterLoginʵ�����ʴ�KDS��ȥ��
    //RegisterLogin regLogin;//ʵ����RegisterLogin�࣬ʵ���û���ע�����¼�߼�

    //Ϊ�����ֱ���model
    QSqlQueryModel* RawParamModel = new QSqlQueryModel(this);
    QSqlQueryModel* AccessPolicyMatrixModel = new QSqlQueryModel(this);
    QSqlQueryModel* UserModel = new QSqlQueryModel(this);
    QSqlQueryModel* LoggedUserModel = new QSqlQueryModel(this);
    QSqlQueryModel* NewUserModel = new QSqlQueryModel(this);

    int connectMYSQL();//���ӵ�Mysql,�ɹ�����0��ʧ�ܷ���-1

    /*
    ����KDS���ݿ⣬������KDS�õ���5����(���������ʲôҲ����):
    1����ʼ������(RawParam);�洢KDS��ʼ���Ĳ�����hx�洢h1,h2,...,hx��ɵ��ַ���������h1ΪU�е�һ�����Զ�Ӧ��G1�е�Ԫ��,UΪ����ȫ����MSKΪϵͳ��˽Կg_alpha��
       �ֶ�:g, e_g_g_alpha, g_a, hx, U, MSK;
     
    2�����ʲ��Ծ����(AccessPolicyMatrix);�洢�������ṩ�ķ��ʲ��Եȱ��μ����йص���Ϣ��KDSΪ���μ�������MUID(��ϢΨһ��ʶ��)(110���ַ�)��Ψһ��ʶ�˴μ��ܵ�ԭʼ���ģ������û����ܣ�ͬʱ����AP(���ʲ���)����APM(���ʲ��Ծ���)�洢�ڱ��С�
       �ֶ�:AccessPolicy, APMatrix, MUID;
     
    3���û���(User);�洢ע��ͨ�����û���Ϣ�������û��������롢�û����Լ�S���û�˽ԿSK��
       �ֶ�:name, password, S, SK;
      
    4�����û���(NewUser);�洢��ע����û���Ϣ���ȴ�KDS����Ա��ˣ���Ϊ�������û����Լ�S������SK����User����ɺ���ӱ���ɾ����
       �ֶ�:name, password;
     
    5���ѵ�¼�û���(LoggedUser);�洢�Ѿ���¼KDS���û���Ϣ�����û���¼ʱKDSΪ�������������ַ�����Ϊcookie(220���ַ�)���û�����ʱ����ӱ���ɾ����
       �ֶ�:name, cookie;
    */
    void createKDSAndTable();

    void showRawParam();//��ʾRawParam�������

    void showAccessPolicyMatrix();//��ʾRawParam�������

    void showUser();//��ʾUser�������

    void showLoggedUser();//��ʾLoggedUser�������

    void showNewUser();//��ʾNewUser�������

    void showServerIpPort();//��ʾ����˼�����IPv4�Ͷ˿�

    void insertRawParam(QString&);//����U����ϵͳ����PK��MSK�Ȳ���RawParam����

    void insertUser(QString& userName, QString& passwd, QString& S, QString& SK);//��KDS����Աͬ��ע����û���Ϣд��User��������û����Ե�¼

    QString getRandomString(int length);//�������length���ȣ�ֻ������Сд��ĸ�����ֵ��ַ���
    
    bool isSvalid(QString& S);//�ж��û����Լ�S�е������Ƿ�������ȫ��U�У�ȫ�������򷵻�true,���򷵻�false

    void deleteUserFromNewUser(QString& userName);//���û�userName��NewUser��ɾ������KDS����Աͬ���ܾ�ʱ����

    QString getUserSK(QString& S);//�����û����Լ�S�������û���˽ԿSK

    void isExistU();//KDS�����������ж����ݿ��Ƿ����U���������������U(��ʱ���ԣ�ϵͳĿǰֻ����һ������ȫ��U)

    Eigen::MatrixXd M_AND(Eigen::MatrixXd& m1, Eigen::MatrixXd& m2);//����m1&m2��Ӧ�ķ��ʲ��Ծ���

    Eigen::MatrixXd M_OR(Eigen::MatrixXd& m1, Eigen::MatrixXd& m2);//����m1|m2��Ӧ�ķ��ʲ��Ծ���

    Eigen::MatrixXd toMatrix(QString matrixQstr);//��matrixQstr��Ӧ�ľ���ԭ

    QString MatrixToQString(Eigen::MatrixXd& APM);//��APM����תΪQString

    QString getSubTMatrix(QString& MUID, int& firstRow, int& lastRow);//����MUID��Ӧ��APM�е�firstRow��lastRow֮��(����firstRow��lastRow)���Ӿ���

private slots:
    void on_pushButton_clicked();//��������U���ȷ����ť�����Ĳۺ���

    void on_pushButton_2_clicked();//��NewUser�����ֶ�ɾ��ѡ�е��û�����Ϊ��Щ�û�������ע������

public slots:
    //����querySignal��ѯ�źţ���ѯqueryQstr�Ƿ����tableToQuery���field�ֶ��У�������ret��ֵΪtrue�������ڸ�ֵΪfalse
    void isExisted(bool& ret, const QString& tableToQuery, const QString& field, const QString& queryQstr);
    
    //����insertSignal�����źţ�����Ӧ�û���Ϣ����tableToQuery��
    void insertNewUser(const QString& tableToQuery, const QString& name, const QString& passwd);
    
    //��User���ѯ�û����������Ƿ�ƥ��
    void matchNamePasswd(bool& ret, const QString& name, const QString& passwd);
    
    //���û���Ϣд��LoggedUser�������ظ��û�˽Կ��cookie����Ϣ
    void userLogin(QString name);

    //�ͻ����û��˳�ʱ���ã����û���LoggedUser��ɾ��
    void userLogOut(const QString& name, const QString& cookie);

    //KDS����Ա���˫��NewUser���е��û�����ʾͬ����û�ע�������ڵ����������������Ϊ���û�ָ�����Լ�S
    //Ȼ�󽫸��û���NewUser����ɾ��������User����
    void agreeClickedUser(const QModelIndex&);

    //ɾ����ע���û��İ�ťֻ�е�ѡ��itemʱ����
    void isEnableDeleteButton(const QItemSelection&, const QItemSelection&);

    //�ж�cookie�Ƿ���LoggedUser���У�������ret=true����ret=false
    void matchCookie(bool& ret, const QString& cookie);

    //�յ�getAPMatrixSignal�źŸ��ݷ��ʲ����б�APList���ɷ��ʲ��Ծ���תΪQString����APMatrix,MaxSizeΪ���ʲ��Ծ�������(���ʲ��������Եĸ���)
    void getAPMatrix(QString& APMatrix, QStringList& APList, int MaxSize);

    //����APList����MUID���������MUID��
    void getMUID(QString& MUID, QStringList& APList);

    //�����ʲ��ԡ����ʲ��Ծ���MUID����AccessPolicyMatrix��
    void insertAPM(QString& AccessPolicy, QString& APMatrix, QString& MUID);

    //�����ʲ����е�������U�е�λ�ô���HXNUM��
    void getOrderHx(QString& APQstr, QString& HXNUM);

    //�ж�cookie��Ӧ���û����Լ��Ƿ�����MUID��Ӧ�ķ��ʲ���,�������������ʲ��Ե��û����Լ����Ӽ��е�Ԫ����Kx�е�˳���Լ���ӦAPM����˳�����KxAPMOrder
    void isAbleDecry(QString cookie, QString MUID);
};
