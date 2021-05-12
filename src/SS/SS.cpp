#include "SS.h"

SS::SS(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    showServerIpPort();//��ʾ����ip�ͼ����˿�
    connect(server.tcpServer, SIGNAL(newConnection()), this, SLOT(detectConnect()));//���������ӵ���detectConnect
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
    QSqlQuery query = QSqlQuery(sql.database);//���Ѵ򿪵�database���ݿ����
    query.exec(QString("select MUID from MsgStorage"));
    while (query.next())
    {
        if (query.value(0).toString() == subCipher.last())//MUID�Ѿ�����
            return QString("0,MUID�ظ���");
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
    QString msgBase64 = msg.toUtf8().toBase64();//��ԭʼ��ϢתΪbase64�����Ա������ݿ���Ч�洢���������԰�����C_2�����ʽȫ��תΪBase64�������ݶ�ʧ
    qDebug() << "msgBase64 = " << msgBase64;
    qDebug() << "msgBase64Size = " << msgBase64.length();
    sql.insertMsg(fileName, owner, msgDesc, MUID, msgBase64);//FileName,Owner,MsgDesc,MUID,Msg(����base64����)
    return QString("1,�������ݿ�ɹ���");
}

void SS::detectConnect()
{
    //QMessageBox::information(this, "daw", "new connection!");

    server.serverSocket = server.tcpServer->nextPendingConnection();
    if (!server.serverSocket)
        QMessageBox::critical(this, tr("����ͨ��"), tr("δ��ȷ��ȡ�ͻ������ӣ�"));

    connect(server.serverSocket, &QIODevice::readyRead, this, &SS::processUpDown);//�����ݵ������processUpDown
    //connect(serverSocket, &QAbstractSocket::errorOccurred, this, &ServerSetup::displayError);//�����ӡ
    //connect(Server.serverSocket, SIGNAL(disconnected()), this, SLOT(serverDisconnect()));//����˶Ͽ�����

}

void SS::processUpDown()
{
    QString msgRecv = server.readData();//[up or down or catalog|name;fileName;CTMUID]up��Ӧ�������ϴ����ģ�down�����������������CTMUID[CT;�ļ�����;MUID],CT[C;C1;C2;daw;C1;D1;...;Ci;Di]
    QStringList recvList = msgRecv.split("|");
    if (recvList.at(0) == "up")//�������ϴ�����
    {
        recvList.removeFirst();
        qDebug() << storeMsg(recvList.join("|"));//�����ĵȴ���MsgStorage��
        showMsgStorage();//������ʾMsgStorage�������
        sendCatalog();//��SS��������Ϣ��Ŀ¼�������󷽣������Լ��ϴ�����Ϣ
    }
    else if (recvList.at(0) == "down")//[down|MUID]SS��MUID��Ӧ������Base64���ܵ�ֵ���͸����ܷ�[msg]
    {
        sendMsg(recvList.at(1));//��MUID��Ӧ��������Ϣ���͸����ܷ�[msg]
    }
    else if (recvList.at(0) == "catalog")//[catalog]�ͻ�������ʱ���ͣ����������ͣ�SS�����з���ÿ����Ϣ��[FileName;Owner;MsgDesc;MUID]
    {
        sendCatalog();//��SS��������Ϣ��Ŀ¼��������
    }
    else//����Ƿ�
        server.writeData(QString("����Ƿ���"));
}

void SS::showMsgStorage()
{
    MsgStorageModel->setQuery("select * from MsgStorage", sql.database);//һ��Ҫ��database
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
    QSqlQuery query = QSqlQuery(sql.database);//���Ѵ򿪵�database���ݿ����
    query.exec(QString("select FileName, Owner, MsgDesc, MUID from MsgStorage"));
    QString subMsgCatalog;//һ����Ϣ��ժҪ����ʽ[FileName;Owner;MsgDesc;MUID]
    QStringList subMsgCatalogList;//���ÿ����Ϣ��������Ϣ���ֺŸ���
    
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
        server.writeData(QString("0|SS��û�д洢�ļ�"));//0����SS�˻�û���û��ϴ���Ϣ
        return;
    }
    catalogSend = "1|" + catalogSend;//1����SS�����û��ϴ���Ϣ
    server.writeData(catalogSend);//����ϢժҪ��������

}

void SS::sendMsg(QString MUID)
{
    QSqlQuery query = QSqlQuery(sql.database);//���Ѵ򿪵�database���ݿ����
    query.exec(QString("select Msg from MsgStorage where MUID = '%1'").arg(MUID));
    query.next();

    QString reqMsgBase64 = query.value(0).toString();
    server.writeData(reqMsgBase64);
}
