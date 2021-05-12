#pragma once
#pragma execution_character_set("utf-8")//解决中文乱码

#include <QtWidgets/QWidget>
#include "ui_EDClient.h"
#include <QMessageBox>
//#include <QDesktopServices>
#include <QFileDialog>

#include <pbc.h>
#include <cryptlib.h>
#include <sha.h>
#include <filters.h>
#include <hex.h>
#include <Eigen/Dense>

//程序主界面
class EDClient : public QWidget
{
    Q_OBJECT

public:
    EDClient(QWidget *parent = Q_NULLPTR);
    ~EDClient();

private:
    Ui::EDClientClass ui;
    pairing_t pairing;//a类型对
    QString fileName;//存放要加密消息的文件名
    QString fileContent;//存放要加密消息的内容
    QStringList PK;//存储系统参数PK[g,e(g,g)^alpha,g^a,hx]
    QStringList SK;//存储用户私钥SK[z,K((g^alpha)*g^(a*t*(1/z))),L(g^t),Kx(hx^t)],用户S的每个属性对应一个Kx
    QString sQstr;//存储加密时的共享变量s
    QString rQstr;//存储加密时GT中的元素r

    QStringList hxOrderList;//存储访问策略中的属性对应的hx的位置
    QStringList blindPairIndex4;//对应存储四个盲化对的指数
    QStringList blindPairValue4;//存储blindPairIndex4中对应指数在生成元g为底数时的值
    bool vSignal = false;
    QString cipher;//存储解密时从SS下载的base64解密的字符串[C;C_1;C_2;daw;C1;D1;...;Ci;Di]
    QString MUID;//存放要解密文件的MUID

    const char* aTypeStr = "type a\
		q 8780710799663312522437781984754049815806883199414208211028653399266475630880222957078625179422662221423155858769582317459277713367317481324925129998224791\
		h 12016012264891146079388821366740534204802954401251311822919615131047207289359704531102844802183906537786776\
		r 730750818665451621361119245571504901405976559617\
		exp2 159\
		exp1 107\
		sign1 1\
		sign0 1";

    void closeEvent(QCloseEvent* close);

    void clearLogged();//程序退出清除KDS服务器上的LoggedUser表

    QString encryAndVerify(Eigen::MatrixXd& APMatrix);//输入访问策略矩阵APMatrix,完成所选消息txt的外包加密与验证,返回CT

    QStringList computeThreeOfCT();//计算C、C_1、C_2,返回三者用分号隔开的QString

    void uploadToSS(QString& CTMUID);//将CT;文件描述;MUID格式的QString上传到存储服务器SS

    QString getAPMatrixMUID(QString& accessPolicy);//输入访问策略,格式为属性值的析取范式，","对应与";"对应或,返回访问策略矩阵;MUID;HXNUM表示此访问策略，一个MUID只对应一个访问策略，但是一个访问策略可以对应多个MUID，通常加密时同一个访问策略对应不同MUID，可以对外隐藏访问策略,HXNUM表示访问策略中的属性对应到U中的位置

    QString computeCiDi(Eigen::MatrixXd& APMatrix);//根据访问策略矩阵配合ES计算CiDi

    Eigen::MatrixXd toMatrix(QString);//将[1 0\n0 1]格式QString转为Eigen::MatrixXd格式的矩阵

    QString byteToHexStr(unsigned char byte_arr[], int arr_len);//将字节流转为QString

    QString elementToQString(element_t);//element类型转为QString类型

    bool hexStr2Byte(std::string hexStr, unsigned char byteArray[]);//输入16进制字符串，转为字节流数组存入byteArray

    QString outPow(element_t u, element_t a);//外包ES计算指数u^a,盲化隐藏u和a并验证ES计算结果的正确性，计算正确则将最终结果存入QString中，错误则停止运算并显示错误信息{指数在Zr中，底数在G1中}

    void blindPairGen4();//系统启动时随机生成四个盲化对，并以QString形式存储在blindPairIndex4和blindPairValue4中

    void rGen(QStringList& rList, int& rowAPM);//在Zr中随机选择rowAPM个元素r存入rList

    void computeLambda(QStringList& lambda, int& rowAPM, int& colAPM, Eigen::MatrixXd& APMatrix);//生成lambda分量并存入lambda

    QString sendToES(QString& allOutCiDi);//发送给ES需要外包计算CiDi的全部参数，返回所有计算结果

    bool verifyES(QString outResult, QString& CiDiQstr);//验证ES返回结果的正确性，正确返回true

    void displayESRet(QString& outResult);//显示返回结果

    void updateMsgCatalog(QString& msgCatalog);//更新解密栏中的SS端消息目录,msgCatalog格式[FileName;Owner;MsgDesc;MUID|...|...]

    void EDClient::DVCipher();//将从SS接受到的经过Base64解码后的QString[C;C_1;C_2;daw;C1;D1;...;Ci;Di]cipher，联合解密服务器DS解密并验证解密结果的正确性

    QString isAvail(QString& MUID);//输入要解密的MUID，询问KDS自己是否可以解密该MUID对应的密文，可以解密(用户属性集满足访问策略)则返回[1;KxOrder;subTAPM],不能解密则返回[0;错误提示],KxOrder对应用户集合中满足访问策略的属性对应的Kx,subTAPM对应APM矩阵相应子矩阵的转置矩阵

    QString subKxGen(QStringList& KxOrder); //根据order生成对应Kx组成的序列[K1; K2; ...; Kx]

    QString subAMPGen(QStringList& APMOrder);//根据APMOrder界定的行数截取APM矩阵为外包解密时发送给DS的子矩阵

    void verifyDS(QString& DSCompute);//验证DS计算结果DSCompute的正确性


private slots:
    void recvLogin();//显示主窗口的槽函数

    void getMsgInfo();//获取加密文件的文件名和内容并保存到fileName和fileContent中
    
    void processMsgFile();//加密页点击确认后处理加密的文件，包括访问策略矩阵和MUID的显示，配合ES完成消息加密，校验ES返回的数据

    void on_pushButton_clicked();//更新消息目录按钮调用的槽函数

    void downMsg();//下载选择的消息base64主体

    void enableDown();//点击SS文件目录表格时触发判断是否选中某行

    void on_pushButton_2_clicked();//解密方点击要解密的文件展示栏下的确定按钮时，联合DS进行解密

public slots:
    void showLoggedUserInfo(QString& loggedUserInfo);//显示接受到的登录用户信息到主程序的用户信息标签页

    void showSSMsgCatalog();//向SS服务器请求其消息目录

};
