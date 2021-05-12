#include "ClientSetup.h"

ClientSetup::ClientSetup(QString serverIPv4, QString serverPort)
{
	QNetworkProxyFactory::setUseSystemConfiguration(false); //����ϵͳ����
	connectServer(serverIPv4, serverPort);
}

ClientSetup::~ClientSetup()
{
	//clientSocket->deleteLater();//����ͻ���socket,�����1��4���ӵ�time_waitռ�ö˿�
}

void ClientSetup::connectServer(const QString& serverIPv4, const QString& serverPort)
{
	clientSocket = new QTcpSocket(this);//�����ʼ�ڴ�
	clientSocket->connectToHost(serverIPv4, serverPort.toInt());//���ӷ�����
	if (!clientSocket->waitForConnected(30000))//����ʧ��
	{
		QMessageBox::critical(this, "����ͨ��ʧ��", QString("���ӷ�����[%1:%2]ʧ��: ").arg(serverIPv4, serverPort) + clientSocket->errorString());
		return;
	}
	isConnected = 1;//���ӷ������ɹ�isConnected��Ϊ1
}

QString ClientSetup::readData()
{
	QString prompt;//���������ص���Ϣ
	QByteArray array;//�洢��ȡ��������Ϣ
	while (clientSocket->bytesAvailable() == 8192)//����û��ȫ����������
	{
		array += clientSocket->readAll();
		clientSocket->waitForReadyRead(3000);
	}
	array += clientSocket->readAll();
	prompt = array;
	//qDebug() << prompt.size();

	return prompt;
}

void ClientSetup::writeData(QString& qstrToSend)
{
	int sendRe;
	QByteArray rawArray = qstrToSend.toUtf8();
	QByteArray sendArray;//������͵��ֽ�������8192��ֶη���
	//qDebug() << userInfo.size();
	if (rawArray.size() <= 8192)//������͵��ֽ���С�ڽ��ܶ��������ֽ���(8192)��ֱ�ӷ���
		sendRe = clientSocket->write(rawArray);
	else 
	{
		//sendArray = rawArray.mid(0, 8192);//ǰ8192�ֽ�
		while (rawArray.size() > 8192)//ʣ���ֽ�������8192
		{
			sendArray = rawArray.mid(0, 8192);//ȡ�����ֽ���ǰ8192�ֽڷ���
			rawArray = rawArray.mid(8192);//ȥ��ǰ8192�ֽ�
			clientSocket->write(sendArray);
			clientSocket->flush();
		}
		sendRe = clientSocket->write(rawArray);
		clientSocket->flush();
	}

	if (sendRe == -1)
	{
		QMessageBox::information(this, "QT����ͨ��", "�����˷�������ʧ��:" + clientSocket->errorString());
		return;
	}
}
