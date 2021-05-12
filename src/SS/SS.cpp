#include "SS.h"

SS::SS(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    showServerIpPort();//显示本地ip和监听端口
    connect(server.tcpServer, SIGNAL(newConnection()), this, SLOT(detectConnect()));//发现新连接调用detectConnect
    showMsgStorage();
}

SS::~SS()
{
}

void SS::showServerIpPort()
{
    ui.label_IP->setText(tr("The server is running on %1: %2").arg(server.ipAddress.toString()).arg(QString::number(server.tcpServer->serverPort())));
}

QString SS::storeMsg(QString cipher)
{
    QStringList subCipher = cipher.split(";"); //[name;fileName;C;C1;C2;daw;C1;D1;...;Ci;Di;msgDesc;MUID]
    QSqlQuery query = QSqlQuery(sql.database);//绑定已打开的database数据库对象
    query.exec(QString("select MUID from MsgStorage"));
    while (query.next())
    {
        if (query.value(0).toString() == subCipher.last())//MUID已经存在
            return QString("0,MUID重复！");
    }

    QString MUID = subCipher.last();
    subCipher.removeLast();

    QString msgDesc = subCipher.last();
    subCipher.removeLast();

    QString owner = subCipher.first();
    subCipher.removeFirst();
    qDebug() << "owner:" << owner;
    QString fileName = subCipher.first();
    subCipher.removeFirst();

    //[C;C1;C2;daw;C1;D1;...;Ci;Di]
    QString msg = subCipher.join(";");
    QString msgBase64 = msg.toUtf8().toBase64();//将原始消息转为base64编码以便在数据库有效存储，将来可以把密文C_2传输格式全部转为Base64以免数据丢失
    qDebug() << "msgBase64 = " << msgBase64;
    qDebug() << "msgBase64Size = " << msgBase64.length();
    sql.insertMsg(fileName, owner, msgDesc, MUID, msgBase64);//FileName,Owner,MsgDesc,MUID,Msg(经过base64编码)
    return QString("1,更新数据库成功！");
}

void SS::detectConnect()
{
    //QMessageBox::information(this, "daw", "new connection!");

    server.serverSocket = server.tcpServer->nextPendingConnection();
    if (!server.serverSocket)
        QMessageBox::critical(this, tr("网络通信"), tr("未正确获取客户端连接！"));

    connect(server.serverSocket, &QIODevice::readyRead, this, &SS::processUpDown);//有数据到达调用processUpDown
    //connect(serverSocket, &QAbstractSocket::errorOccurred, this, &ServerSetup::displayError);//错误打印
    //connect(Server.serverSocket, SIGNAL(disconnected()), this, SLOT(serverDisconnect()));//服务端断开连接

}

void SS::processUpDown()
{
    QString msgRecv = server.readData();//[up or down or catalog|name;fileName;CTMUID]up对应加密者上传密文，down代表解密者下载密文CTMUID[CT;文件描述;MUID],CT[C;C1;C2;daw;C1;D1;...;Ci;Di]
    QStringList recvList = msgRecv.split("|");
    if (recvList.at(0) == "up")//加密者上传密文
    {
        recvList.removeFirst();
        qDebug() << storeMsg(recvList.join("|"));//将密文等存入MsgStorage表
        showMsgStorage();//重新显示MsgStorage表的内容
        sendCatalog();//将SS上所有消息的目录发给请求方，更新自己上传的消息
    }
    else if (recvList.at(0) == "down")//[down|MUID]SS将MUID对应的密文Base64加密的值发送给解密方[msg]
    {
        sendMsg(recvList.at(1));//将MUID对应的密文消息发送给解密方[msg]
    }
    else if (recvList.at(0) == "catalog")//[catalog]客户端启动时发送，或主动发送，SS将所有发送每条消息的[FileName;Owner;MsgDesc;MUID]
    {
        sendCatalog();//将SS上所有消息的目录发给请求方
    }
    else//请求非法
        server.writeData(QString("请求非法！"));
}

void SS::showMsgStorage()
{
    MsgStorageModel->setQuery("select * from MsgStorage", sql.database);//一定要绑定database
    //MsgStorageModel->setHeaderData(0, Qt::Horizontal, tr("uid"));
    //MsgStorageModel->setHeaderData(1, Qt::Horizontal, tr("FileName"));
    //MsgStorageModel->setHeaderData(2, Qt::Horizontal, tr("Owner"));
    //MsgStorageModel->setHeaderData(3, Qt::Horizontal, tr("MsgDesc"));
    //MsgStorageModel->setHeaderData(4, Qt::Horizontal, tr("MUID"));
    //MsgStorageModel->setHeaderData(5, Qt::Horizontal, tr("Msg"));

    ui.tableView->setModel(MsgStorageModel);
    //ui.tableView->horizontalHeader()->setStyleSheet("QHeaderView { font-size: 12pt; }");
    //ui.tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //ui.tableView->setColumnWidth(0, 50);
    //ui.tableView->setColumnWidth(1, 100);
    ui.tableView->show();
}

void SS::sendCatalog()//[FileName;Owner;MsgDesc;MUID|...|...]
{
    QSqlQuery query = QSqlQuery(sql.database);//绑定已打开的database数据库对象
    query.exec(QString("select FileName, Owner, MsgDesc, MUID from MsgStorage"));
    QString subMsgCatalog;//一条消息的摘要，格式[FileName;Owner;MsgDesc;MUID]
    QStringList subMsgCatalogList;//存放每条消息的三个信息，分号隔开
    
    while (query.next())
    {
        subMsgCatalog.clear();
        subMsgCatalog += query.value(0).toString();//FileName
        subMsgCatalog += ";";

        subMsgCatalog += query.value(1).toString();//Owner
        subMsgCatalog += ";";

        subMsgCatalog += query.value(2).toString();//MsgDesc
        subMsgCatalog += ";";

        subMsgCatalog += query.value(3).toString();//MUID
        subMsgCatalogList.append(subMsgCatalog);
    }

    QString catalogSend = subMsgCatalogList.join("|");//[FileName;Owner;MsgDesc;MUID|...|...]
    if (catalogSend.length() == 0)
    {
        server.writeData(QString("0|SS端没有存储文件"));//0代表SS端还没有用户上传消息
        return;
    }
    catalogSend = "1|" + catalogSend;//1代表SS端有用户上传消息
    server.writeData(catalogSend);//将消息摘要发给请求方

}

void SS::sendMsg(QString MUID)
{
    QSqlQuery query = QSqlQuery(sql.database);//绑定已打开的database数据库对象
    query.exec(QString("select Msg from MsgStorage where MUID = '%1'").arg(MUID));
    query.next();

    QString reqMsgBase64 = query.value(0).toString();
    server.writeData(reqMsgBase64);
}
