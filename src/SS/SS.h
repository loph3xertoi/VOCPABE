#pragma once
#pragma execution_character_set("utf-8")//解决中文乱码

#include <QtWidgets/QWidget>
#include "ui_SS.h"
#include "SSServer.h"
#include "SSSql.h"



class SS : public QWidget
{
    Q_OBJECT

public:
    SS(QWidget *parent = Q_NULLPTR);
    ~SS();

private:
    Ui::SSClass ui;

    SSServer server;//初始化服务器实例
    SSSql sql;//建立sql对象
    QSqlQueryModel* MsgStorageModel = new QSqlQueryModel(this);

    void showServerIpPort();//显示本地监听的地址和端口

    QString storeMsg(QString cipher);//将加密方上传的密文存入数据库

    void showMsgStorage();//将MsgStorage数据库中的数据显示到SS界面

    void sendCatalog();//将MsgStorage表中所有消息的[FileName;Owner;MsgDesc|...|...]发送给请求者

    void sendMsg(QString MUID);//将MUID对应消息msg(base64)发送给解密方

public slots:
    void detectConnect();//检测到加密或解密方连接后调用

    void processUpDown();//接收数据并处理用户请求，判断上传还是下载
};
