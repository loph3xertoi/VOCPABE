#include "ESServer.h"

ESServer::ESServer()
{
    QNetworkProxyFactory::setUseSystemConfiguration(false); // ��̬����
    initServer();

}

ESServer::~ESServer()
{
}

void ESServer::initServer()
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

QString ESServer::readData()
{
    QString prompt;//���������ص���Ϣ
    QByteArray array;//�洢��ȡ��������Ϣ
    while (serverSocket->bytesAvailable() == 8192)//����û��ȫ����������
    {
        array += serverSocket->readAll();
        serverSocket->waitForReadyRead(3000);
    }
    array += serverSocket->readAll();
    prompt = array;
    //qDebug() << prompt.size();

    return prompt;
}

void ESServer::writeData(QString& qstrToSend)
{
    int sendRe;
    QByteArray rawArray = qstrToSend.toUtf8();
    QByteArray sendArray;//������͵��ֽ�������8192��ֶη���
    //qDebug() << userInfo.size();
    if (rawArray.size() <= 8192)//������͵��ֽ���С�ڽ��ܶ��������ֽ���(8192)��ֱ�ӷ���
        sendRe = serverSocket->write(rawArray);
    else 
    {
        //sendArray = rawArray.mid(0, 8192);//ǰ8192�ֽ�
        while (rawArray.size() > 8192)//ʣ���ֽ�������8192
        {
            sendArray = rawArray.mid(0, 8192);//ȡ�����ֽ���ǰ8192�ֽڷ���
            rawArray = rawArray.mid(8192);//ȥ��ǰ8192�ֽ�
            serverSocket->write(sendArray);
            serverSocket->flush();
        }
        sendRe = serverSocket->write(rawArray);
        serverSocket->flush();
    }

    if (sendRe == -1)
    {
        QMessageBox::information(this, QString("����ͨ��"), QString("����ܷ���������ʧ��:") + serverSocket->errorString());
        return;
    }
}
