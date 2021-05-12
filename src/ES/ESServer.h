#pragma once
#pragma execution_character_set("utf-8")//�����������
#include <QTcpServer>
#include <QTcpSocket>
#include <QMessageBox>
#include <QNetworkInterface>
#include <QtNetwork/qnetworkproxy.h>

//��ʼ��ES������
class ESServer : public QWidget
{
	Q_OBJECT

public: 
	ESServer();
	~ESServer();

	QTcpServer* tcpServer = nullptr;//����˶���
	QTcpSocket* serverSocket = nullptr;//�����socket
	QHostAddress ipAddress;//������ip��ַ

	QString readData();//��socket�ж�ȡ����

	void writeData(QString& qstrToSend);//��socket��д����

private:
	quint64 port = 65533;//�����˿�65533

	void initServer();//��ʼ�������

private slots:


};

