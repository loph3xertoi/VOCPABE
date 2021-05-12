#pragma once
#pragma execution_character_set("utf-8")//�����������
#include <QTcpServer>
#include <QTcpSocket>
#include <QMessageBox>
#include <QNetworkInterface>
#include <QtNetwork/qnetworkproxy.h>

//��ʼ��SS������
class SSServer : public QWidget
{
	Q_OBJECT

public:
	SSServer();
	~SSServer();

	QTcpServer* tcpServer = nullptr;//����˶���
	QTcpSocket* serverSocket = nullptr;//�����socket
	QHostAddress ipAddress;//������ip��ַ

	QString readData();//��socket�ж�ȡ����

	void writeData(QString& qstrToSend);//��socket��д����

private:
	quint64 port = 65531;//�����˿�65531

	void initServer();//��ʼ�������

private slots:


};

