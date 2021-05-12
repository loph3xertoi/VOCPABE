#pragma once
#pragma execution_character_set("utf-8")//解决中文乱码

#include <QtWidgets/QWidget>
#include <iostream>
#include "ui_DS.h"
#include "DSServer.h"
#include "pbc.h"
#include <QInputDialog>
#include <Eigen/Dense>

class DS : public QWidget
{
    Q_OBJECT

public:
    DS(QWidget *parent = Q_NULLPTR);
    ~DS();

private:
    Ui::DSClass ui;

    pairing_t pairing;
    DSServer Server;//实例化ServerSetup类,初始化服务端实例，处理远程连接
    const char* aTypeStr = "type a\
		q 8780710799663312522437781984754049815806883199414208211028653399266475630880222957078625179422662221423155858769582317459277713367317481324925129998224791\
		h 12016012264891146079388821366740534204802954401251311822919615131047207289359704531102844802183906537786776\
		r 730750818665451621361119245571504901405976559617\
		exp2 159\
		exp1 107\
		sign1 1\
		sign0 1";
    QString retQstr;//存放发给解密方的计算结果

    void showServerIpPort();//显示本地监听的地址和端口

    QString elementToQString(element_t);//element类型转为QString类型

    //decryRawQstr的格式[K;L;subKx|C_1;C1;D1;C2;D2;...;Ci;Di|subTAPM|name]
    QString preDecry(QString& decryRawQstr);//对收到的字符串进行处理并作相应解密，返回解密后的字符串(GT中的元素)

    QStringList computeOmega(QString& subTAPM);//根据subTAPM计算相应的omega系数存入omega列表

    Eigen::MatrixXd toMatrix(QString matrixQstr);//将matrixQstr对应的矩阵还原

    QString MatrixToQString(Eigen::MatrixXd& APM);//将APM矩阵转为QString

    //计算最终结果并显示，输入attrNum(合法属性数量)，userList(用户转换私钥),cipherList(转换密文),omege(omege系数，即恢复共享消息的系数),firstPos(合取式在访问策略中的位置,标记Ci开始位置)
    QString actualComp(const int& attrNum, const QStringList& cipherList, const QStringList& userSKList, const QStringList& omega, const int& firstPos);


private slots:
    void on_pushButton_clicked();//改变计算结果按钮

public slots:
    void detectConnect();//检测到解密方连接后调用，进行外包解密计算

    void changeResult(QString& retQstr);//改变计算结果存入retQstr,然后将结果发给解密方
};
