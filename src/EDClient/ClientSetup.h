#pragma once
#pragma execution_character_set("utf-8")//解决中文乱码

//KDS服务端的ip地址
//constexpr auto KDS_IPv4 = "192.168.43.169";
//KDS服务端的监听端口
//constexpr auto KDS_PORT = 65534;

#include <QTcpServer>
#include <QTcpSocket>
#include <QMessageBox>
#include <QNetworkInterface>
#include <QNetworkProxyFactory>
#include <Windows.h>


//初始化客户端，处理IPC相关的操作
class ClientSetup : public QWidget
{
	Q_OBJECT

public:
	ClientSetup(QString serverIPv4, QString serverPort);
	~ClientSetup();
	int isConnected = 0;//成功连接KDS服务器则变为1
	QTcpSocket* clientSocket = nullptr;//客户端建立的socket

	//连接服务器,服务器地址:serverIPv4，服务器端口:serverPort.
	void connectServer(const QString& serverIPv4, const QString& serverPort);

	QString readData();//从socket中读数据

	void writeData(QString&);//向socket中写数据

private:


};

