#include "ClientSetup.h"

ClientSetup::ClientSetup(QString serverIPv4, QString serverPort)
{
	QNetworkProxyFactory::setUseSystemConfiguration(false); //禁用系统代理
	connectServer(serverIPv4, serverPort);
}

ClientSetup::~ClientSetup()
{
	//clientSocket->deleteLater();//清理客户端socket,会产生1到4分钟的time_wait占用端口
}

void ClientSetup::connectServer(const QString& serverIPv4, const QString& serverPort)
{
	clientSocket = new QTcpSocket(this);//分配初始内存
	clientSocket->connectToHost(serverIPv4, serverPort.toInt());//连接服务器
	if (!clientSocket->waitForConnected(30000))//连接失败
	{
		QMessageBox::critical(this, "网络通信失败", QString("连接服务器[%1:%2]失败: ").arg(serverIPv4, serverPort) + clientSocket->errorString());
		return;
	}
	isConnected = 1;//连接服务器成功isConnected变为1
}

QString ClientSetup::readData()
{
	QString prompt;//服务器返回的信息
	QByteArray array;//存储读取的所有信息
	while (clientSocket->bytesAvailable() == 8192)//可能没有全部读完数据
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
	QByteArray sendArray;//如果发送的字节数超过8192则分段发送
	//qDebug() << userInfo.size();
	if (rawArray.size() <= 8192)//如果发送的字节数小于接受端最大接受字节数(8192)，直接发送
		sendRe = clientSocket->write(rawArray);
	else 
	{
		//sendArray = rawArray.mid(0, 8192);//前8192字节
		while (rawArray.size() > 8192)//剩余字节数大于8192
		{
			sendArray = rawArray.mid(0, 8192);//取现有字节流前8192字节发送
			rawArray = rawArray.mid(8192);//去掉前8192字节
			clientSocket->write(sendArray);
			clientSocket->flush();
		}
		sendRe = clientSocket->write(rawArray);
		clientSocket->flush();
	}

	if (sendRe == -1)
	{
		QMessageBox::information(this, "QT网络通信", "向服务端发送数据失败:" + clientSocket->errorString());
		return;
	}
}
