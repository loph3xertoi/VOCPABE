#pragma once
#include <QTcpServer>
#include <QTcpSocket>
#include <QMessageBox>
#include <QNetworkInterface>
#include <QtNetwork/qnetworkproxy.h>
//#include "KDS.h"

//初始化服务端，处理IPC相关的操作
class ServerSetup : public QWidget
{
	Q_OBJECT

public:
	ServerSetup();
	~ServerSetup();

	QTcpServer* tcpServer = nullptr;//服务端对象
	QTcpSocket* serverSocket = nullptr;//服务端socket
	QHostAddress ipAddress;//监听的ip地址


private:
	quint64 port = 65534;//监听端口65534
	//QStringList recvMessageList;//将从ESClient收到的信息按","分隔存入此链表

	void initServer();//初始化服务端
	
	void processRecvMsg(QStringList&);//根据标识字符串进行相应处理

private slots:
	void readAndProcessData();//从socket中读并处理数据

	QStringList readData();//读取从EDClient接受到的数据,返回按英文逗号分隔的QStringList

	void detectConnect();//检测到客户端连接调用此函数

	void displayError(QAbstractSocket::SocketError socketError);//显示错误信息

	void serverDisconnect();//收到客户端close后调用

signals:
	//登录信号，将用户信息写入LoggedUser表，并返回给用户私钥，cookie等信息
	void loginSignal(QString name);

	//收到客户端退出请求后将相应用户从LoggedUer表中去除
	void logOut(const QString& name, const QString& cookie);

	//解密方发出解密请求时判断cookie对应的用户属性集是否满足MUID对应的访问策略
	void isAbleDecrySignal(QString cookie, QString MUID);
};

