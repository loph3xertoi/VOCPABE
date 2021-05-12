#pragma once
#pragma execution_character_set("utf-8")//�����������

//KDS����˵�ip��ַ
//constexpr auto KDS_IPv4 = "192.168.43.169";
//KDS����˵ļ����˿�
//constexpr auto KDS_PORT = 65534;

#include <QTcpServer>
#include <QTcpSocket>
#include <QMessageBox>
#include <QNetworkInterface>
#include <QNetworkProxyFactory>
#include <Windows.h>


//��ʼ���ͻ��ˣ�����IPC��صĲ���
class ClientSetup : public QWidget
{
	Q_OBJECT

public:
	ClientSetup(QString serverIPv4, QString serverPort);
	~ClientSetup();
	int isConnected = 0;//�ɹ�����KDS���������Ϊ1
	QTcpSocket* clientSocket = nullptr;//�ͻ��˽�����socket

	//���ӷ�����,��������ַ:serverIPv4���������˿�:serverPort.
	void connectServer(const QString& serverIPv4, const QString& serverPort);

	QString readData();//��socket�ж�����

	void writeData(QString&);//��socket��д����

private:


};

