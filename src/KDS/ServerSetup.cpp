#include "ServerSetup.h"
#include "RegisterLogin.h"
//#include "KDS.h"
//extern KDS* quoteKDS;


ServerSetup::ServerSetup()
{
    QNetworkProxyFactory::setUseSystemConfiguration(false); // 静态函数
    initServer();
    connect(tcpServer, SIGNAL(newConnection()), this, SLOT(detectConnect()));//EDClient发送注册或登录信息时执行readData函数处理接受到的数据
    //serverSocket = new QTcpSocket(this);
}

ServerSetup::~ServerSetup()
{

}

void ServerSetup::initServer()//服务端初始化
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
    RegisterLogin regLoginProcess;//regLoginProcess用来处理用户注册与登录的逻辑部分
    //QMessageBox::information(this, "daw", "recv msg");
    if (recvMsgList.at(0) == "register")//请求注册
    {
        //QMessageBox::information(this, "register", "EDClient register");
        QString processResult = regLoginProcess.regProcess(recvMsgList);    //处理新用户注册
        serverSocket->write(processResult.toUtf8());                        //向EDClient发送prompt
        serverSocket->flush();
    }
    else if (recvMsgList.at(0) == "login")//请求登录
    {
        //QMessageBox::information(this, "login", "EDClient login");
        recvMsgList.removeFirst();//将login去掉
        QStringList namePasswdList = recvMsgList.join(",").split("|");//将name和password分开
        qDebug() << "namePass = " << namePasswdList;
        QString processResult = regLoginProcess.loginProcess(namePasswdList);  //处理用户登录
        serverSocket->write(processResult.toUtf8());                        //向EDClient发送prompt
        serverSocket->flush();                                              //立即将提示信息发给客户端

        if(processResult.at(0) == '6')
            emit loginSignal(namePasswdList.at(0));                            //对用户进行登录，向LoggedUser表插入对应记录
    }
    else if (recvMsgList.at(0) == "exit")//请求退出，即清理LoggedUser表
    {
        emit logOut(recvMsgList.at(1), recvMsgList.at(2));                  //分别传入用户名和cookie
        serverSocket->close();                                              //完成读取socket后关闭socket
    }
    else if (recvMsgList.at(0) == "AP")//加密者发送的访问策略[析取范式]，接受到的消息格式[AP,访问策略析取范式,cookie]
    {
        QString processResult = regLoginProcess.processAP(recvMsgList);
        serverSocket->write(processResult.toUtf8());
        serverSocket->flush();
    }
    else if (recvMsgList.at(0) == "Decry")//该请求为解密方询问自己是否可以解密MUID对应消息[Decry,cookie,MUID]
    {
        emit isAbleDecrySignal(recvMsgList.at(1), recvMsgList.at(2));
    }
    else
    {
        QString sendQstr = "0,请求非法";
        serverSocket->write(sendQstr.toUtf8());                             //向EDClient发送prompt
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
    if (serverSocket != nullptr) //与客户端连接的socket，不是nullptr，则说明有客户端存在
    {
        QByteArray array = serverSocket->readAll();                 //接收消息
        //QHostAddress clientaddr = serverSocket->peerAddress();    //获得IP
        //int port = serverSocket->peerPort();                      //获得端口号
        QString recvMessage = array;
        QStringList recvMessageList = recvMessage.split(",");       //将从客户端收到的字符串按","分隔存入QStringList中
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
        QMessageBox::critical(this, tr("网络通信"), tr("未正确获取客户端连接！"));
    //else
        //QMessageBox::information(this, tr("QT网络通信"), tr("成功接受客户端的连接"));

    connect(serverSocket, &QIODevice::readyRead, this, &ServerSetup::readAndProcessData);//有数据到达则读数据并处理数据
    //connect(serverSocket, &QAbstractSocket::errorOccurred, this, &ServerSetup::displayError);//错误打印
    connect(serverSocket, SIGNAL(disconnected()), this, SLOT(serverDisconnect()));//服务端断开连接
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
        serverSocket->close(); //关闭客户端
        serverSocket->deleteLater();
    }
}
