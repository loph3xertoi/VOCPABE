#pragma once
#include <QTcpServer>
#include <QTcpSocket>
#include <QMessageBox>
#include <QNetworkInterface>
#include <QtNetwork/qnetworkproxy.h>
//#include "KDS.h"

//��ʼ������ˣ�����IPC��صĲ���
class ServerSetup : public QWidget
{
	Q_OBJECT

public:
	ServerSetup();
	~ServerSetup();

	QTcpServer* tcpServer = nullptr;//����˶���
	QTcpSocket* serverSocket = nullptr;//�����socket
	QHostAddress ipAddress;//������ip��ַ


private:
	quint64 port = 65534;//�����˿�65534
	//QStringList recvMessageList;//����ESClient�յ�����Ϣ��","�ָ����������

	void initServer();//��ʼ�������
	
	void processRecvMsg(QStringList&);//���ݱ�ʶ�ַ���������Ӧ����

private slots:
	void readAndProcessData();//��socket�ж�����������

	QStringList readData();//��ȡ��EDClient���ܵ�������,���ذ�Ӣ�Ķ��ŷָ���QStringList

	void detectConnect();//��⵽�ͻ������ӵ��ô˺���

	void displayError(QAbstractSocket::SocketError socketError);//��ʾ������Ϣ

	void serverDisconnect();//�յ��ͻ���close�����

signals:
	//��¼�źţ����û���Ϣд��LoggedUser�������ظ��û�˽Կ��cookie����Ϣ
	void loginSignal(QString name);

	//�յ��ͻ����˳��������Ӧ�û���LoggedUer����ȥ��
	void logOut(const QString& name, const QString& cookie);

	//���ܷ�������������ʱ�ж�cookie��Ӧ���û����Լ��Ƿ�����MUID��Ӧ�ķ��ʲ���
	void isAbleDecrySignal(QString cookie, QString MUID);
};

