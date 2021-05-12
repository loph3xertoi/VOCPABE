#include "SSServer.h"

SSServer::SSServer()
{
    QNetworkProxyFactory::setUseSystemConfiguration(false); // 静态函数
    initServer();

}

SSServer::~SSServer()
{
}

void SSServer::initServer()
{
    tcpServer = new QTcpServer();
    if (!tcpServer->listen(QHostAddress::Any, port)) {
        QMessageBox::critical(this, tr("Title"), tr("Unable to start the server : % 1.").arg(tcpServer->errorString()));//qobject_cast<QWidget*> (parent())
        close();
        return;
    }
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    // use the first non-localhost IPv4 address
    for (int i = 0; i < ipAddressesList.size(); ++i) {
        if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
            ipAddressesList.at(i).toIPv4Address()) {
            ipAddress = ipAddressesList.at(i);
            break;
        }
    }
    // if we did not find one, use IPv4 localhost
    if (ipAddress.isNull())
        ipAddress = QHostAddress(QHostAddress::LocalHost);
}

QString SSServer::readData()
{
    QString prompt;//服务器返回的信息
    QByteArray array;//存储读取的所有信息
    while (serverSocket->bytesAvailable() == 8192)//可能没有全部读完数据
    {
        array += serverSocket->readAll();
        serverSocket->waitForReadyRead(3000);
    }
    array += serverSocket->readAll();
    prompt = array;
    //qDebug() << prompt.size();

    return prompt;
}

void SSServer::writeData(QString& qstrToSend)
{
    int sendRe;
    QByteArray rawArray = qstrToSend.toUtf8();
    QByteArray sendArray;//如果发送的字节数超过8192则分段发送
    //qDebug() << userInfo.size();
    if (rawArray.size() <= 8192)//如果发送的字节数小于接受端最大接受字节数(8192)，直接发送
        sendRe = serverSocket->write(rawArray);
    else
    {
        //sendArray = rawArray.mid(0, 8192);//前8192字节
        while (rawArray.size() > 8192)//剩余字节数大于8192
        {
            sendArray = rawArray.mid(0, 8192);//取现有字节流前8192字节发送
            rawArray = rawArray.mid(8192);//去掉前8192字节
            serverSocket->write(sendArray);
            serverSocket->flush();
        }
        sendRe = serverSocket->write(rawArray);
        serverSocket->flush();
    }

    if (sendRe == -1)
    {
        QMessageBox::information(this, QString("网络通信"), QString("发送数据失败:") + serverSocket->errorString());
        return;
    }
}
