#pragma once
#pragma execution_character_set("utf-8")//�����������
#include <QTcpServer>
#include <QTcpSocket>
#include <QMessageBox>
#include <QNetworkInterface>
#include <QtNetwork/qnetworkproxy.h>

//��ʼ��ES������
class DSServer : public QWidget
{
	Q_OBJECT

public:
	DSServer();
	~DSServer();

	QTcpServer* tcpServer = nullptr;//����˶���
	QTcpSocket* serverSocket = nullptr;//�����socket
	QHostAddress ipAddress;//������ip��ַ

	QString readData();//��socket�ж�ȡ����

	void writeData(QString& qstrToSend);//��socket��д����

private:
	quint64 port = 65532;//�����˿�655332

	void initServer();//��ʼ�������

private slots:


};

