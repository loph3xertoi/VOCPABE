#pragma once
#pragma execution_character_set("utf-8")//解决中文乱码
#include <QTcpServer>
#include <QTcpSocket>
#include <QMessageBox>
#include <QNetworkInterface>
#include <QtNetwork/qnetworkproxy.h>

//初始化ES服务器
class DSServer : public QWidget
{
	Q_OBJECT

public:
	DSServer();
	~DSServer();

	QTcpServer* tcpServer = nullptr;//服务端对象
	QTcpSocket* serverSocket = nullptr;//服务端socket
	QHostAddress ipAddress;//监听的ip地址

	QString readData();//从socket中读取数据

	void writeData(QString& qstrToSend);//向socket中写数据

private:
	quint64 port = 65532;//监听端口655332

	void initServer();//初始化服务端

private slots:


};

