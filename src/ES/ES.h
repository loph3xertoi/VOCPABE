#pragma once
#pragma execution_character_set("utf-8")//解决中文乱码

#include <QtWidgets/QWidget>
#include "ui_ES.h"
#include "ESServer.h"
#include "pbc.h"
#include <QInputDialog>

class ES : public QWidget
{
    Q_OBJECT

public:
    ES(QWidget *parent = Q_NULLPTR);
    ~ES();

private:
    Ui::ESClass ui;

    pairing_t pairing;
    ESServer Server;//实例化ServerSetup类,初始化服务端实例，处理远程连接
    const char* aTypeStr = "type a\
		q 8780710799663312522437781984754049815806883199414208211028653399266475630880222957078625179422662221423155858769582317459277713367317481324925129998224791\
		h 12016012264891146079388821366740534204802954401251311822919615131047207289359704531102844802183906537786776\
		r 730750818665451621361119245571504901405976559617\
		exp2 159\
		exp1 107\
		sign1 1\
		sign0 1";
    QString retQstr;//存放发给加密方的计算结果


    void showServerIpPort();//显示本地监听的地址和端口

    QString elementToQString(element_t);//element类型转为QString类型

private slots:
    void on_pushButton_clicked();//改变计算结果按钮

public slots:
    void detectConnect();//检测到加密方连接后调用，计算CiDi相关参数

    void computeCiDi();//socket有数据可读时调用此函数计算实际的CiDi相关幂运算

    void ES::changeResult(QString& retQstr);//改变计算结果存入retQstr,然后将结果发给加密方
};
