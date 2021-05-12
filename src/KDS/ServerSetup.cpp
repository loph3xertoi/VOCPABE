#include "ServerSetup.h"
#include "RegisterLogin.h"
//#include "KDS.h"
//extern KDS* quoteKDS;


ServerSetup::ServerSetup()
{
    QNetworkProxyFactory::setUseSystemConfiguration(false); // ��̬����
    initServer();
    connect(tcpServer, SIGNAL(newConnection()), this, SLOT(detectConnect()));//EDClient����ע����¼��Ϣʱִ��readData����������ܵ�������
    //serverSocket = new QTcpSocket(this);
}

ServerSetup::~ServerSetup()
{

}

void ServerSetup::initServer()//����˳�ʼ��
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
    //QMessageBox::information(this, tr("server"), tr("The server is running on\n\nIP: %1\nport: %2\n\n").arg(ipAddress.toString()).arg(tcpServer->serverPort()));
}

void ServerSetup::processRecvMsg(QStringList& recvMsgList)
{
    RegisterLogin regLoginProcess;//regLoginProcess���������û�ע�����¼���߼�����
    //QMessageBox::information(this, "daw", "recv msg");
    if (recvMsgList.at(0) == "register")//����ע��
    {
        //QMessageBox::information(this, "register", "EDClient register");
        QString processResult = regLoginProcess.regProcess(recvMsgList);    //�������û�ע��
        serverSocket->write(processResult.toUtf8());                        //��EDClient����prompt
        serverSocket->flush();
    }
    else if (recvMsgList.at(0) == "login")//�����¼
    {
        //QMessageBox::information(this, "login", "EDClient login");
        recvMsgList.removeFirst();//��loginȥ��
        QStringList namePasswdList = recvMsgList.join(",").split("|");//��name��password�ֿ�
        qDebug() << "namePass = " << namePasswdList;
        QString processResult = regLoginProcess.loginProcess(namePasswdList);  //�����û���¼
        serverSocket->write(processResult.toUtf8());                        //��EDClient����prompt
        serverSocket->flush();                                              //��������ʾ��Ϣ�����ͻ���

        if(processResult.at(0) == '6')
            emit loginSignal(namePasswdList.at(0));                            //���û����е�¼����LoggedUser������Ӧ��¼
    }
    else if (recvMsgList.at(0) == "exit")//�����˳���������LoggedUser��
    {
        emit logOut(recvMsgList.at(1), recvMsgList.at(2));                  //�ֱ����û�����cookie
        serverSocket->close();                                              //��ɶ�ȡsocket��ر�socket
    }
    else if (recvMsgList.at(0) == "AP")//�����߷��͵ķ��ʲ���[��ȡ��ʽ]�����ܵ�����Ϣ��ʽ[AP,���ʲ�����ȡ��ʽ,cookie]
    {
        QString processResult = regLoginProcess.processAP(recvMsgList);
        serverSocket->write(processResult.toUtf8());
        serverSocket->flush();
    }
    else if (recvMsgList.at(0) == "Decry")//������Ϊ���ܷ�ѯ���Լ��Ƿ���Խ���MUID��Ӧ��Ϣ[Decry,cookie,MUID]
    {
        emit isAbleDecrySignal(recvMsgList.at(1), recvMsgList.at(2));
    }
    else
    {
        QString sendQstr = "0,����Ƿ�";
        serverSocket->write(sendQstr.toUtf8());                             //��EDClient����prompt
    }
}

void ServerSetup::readAndProcessData()
{
    QStringList &recvMsgList = readData();
    //qDebug() << "recvMsgList = " << recvMsgList;
    processRecvMsg(recvMsgList);
}

QStringList ServerSetup::readData()
{
    if (serverSocket != nullptr) //��ͻ������ӵ�socket������nullptr����˵���пͻ��˴���
    {
        QByteArray array = serverSocket->readAll();                 //������Ϣ
        //QHostAddress clientaddr = serverSocket->peerAddress();    //���IP
        //int port = serverSocket->peerPort();                      //��ö˿ں�
        QString recvMessage = array;
        QStringList recvMessageList = recvMessage.split(",");       //���ӿͻ����յ����ַ�����","�ָ�����QStringList��
        return recvMessageList;
    }
    else
        QMessageBox::critical(this, "what", "why you here ?");
    return QStringList("fail to connect to client");
}

void ServerSetup::detectConnect()
{
    serverSocket = tcpServer->nextPendingConnection();
    if (!serverSocket)
        QMessageBox::critical(this, tr("����ͨ��"), tr("δ��ȷ��ȡ�ͻ������ӣ�"));
    //else
        //QMessageBox::information(this, tr("QT����ͨ��"), tr("�ɹ����ܿͻ��˵�����"));

    connect(serverSocket, &QIODevice::readyRead, this, &ServerSetup::readAndProcessData);//�����ݵ���������ݲ���������
    //connect(serverSocket, &QAbstractSocket::errorOccurred, this, &ServerSetup::displayError);//�����ӡ
    connect(serverSocket, SIGNAL(disconnected()), this, SLOT(serverDisconnect()));//����˶Ͽ�����
}

void ServerSetup::displayError(QAbstractSocket::SocketError socketError)
{
    switch (socketError) {
    //case QAbstractSocket::RemoteHostClosedError:
    //    QMessageBox::information(this, tr("Fortune Client"),
    //        tr("RemoteHostClosedError"));
    //    break;
    case QAbstractSocket::HostNotFoundError:
        QMessageBox::information(this, tr("Fortune Client"),
            tr("The host was not found. Please check the "
                "host name and port settings."));
        break;
    case QAbstractSocket::ConnectionRefusedError:
        QMessageBox::information(this, tr("Fortune Client"),
            tr("The connection was refused by the peer. "
                "Make sure the fortune server is running, "
                "and check that the host name and port "
                "settings are correct."));
        break;
    default:
        QMessageBox::information(this, tr("Fortune Client"),
            tr("The following error occurred: %1.")
            .arg(serverSocket->errorString()));
    }
}

void ServerSetup::serverDisconnect()
{
    if (serverSocket != nullptr)
    {
        serverSocket->close(); //�رտͻ���
        serverSocket->deleteLater();
    }
}
