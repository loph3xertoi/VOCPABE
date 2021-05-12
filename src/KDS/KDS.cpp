#include "KDS.h"
//#include "ServerSetup.h"

//void KDS::DAW()
//{
//    QMessageBox::information(this, "Warn", "Please enter mininum!", QMessageBox::Ok);
//    return;
//}
// 
//model->setQuery("insert into rawparam (g, e_g_g_alpha, g_a, hx, U, MSK) values (\"2222\", \"ewew\", \"fefef\", \"ffdddd\", \"dsssssdd\", \"aaadddddda\")", database);

KDS::KDS(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    if (connectMYSQL())//����mysql�ɹ����ʼ�����ݿ�ͱ�
        createKDSAndTable();
    else return;
    showServerIpPort();
    ui.tabWidget->setStyleSheet("QTabWidget { border-top-color: rgba(255, 255, 255, 0); }");//����tab�߿�͸��
    ui.pushButton_2->setDisabled(true);//��ʼNewUser��û���û���ѡ�У�ɾ����ѡ�û���ť������
    
    //showRawParam();
    showAccessPolicyMatrix();
    showUser();
    showLoggedUser();
    showNewUser();
    isExistU();

    //�û��ɹ���¼ʱ����loginSignal�źţ�ִ��userLogin����
    connect(&Server, &ServerSetup::loginSignal, this, &KDS::userLogin);

    //�û��˳�ʱ���û���Ϣ��LoggedUser����ȥ��
    connect(&Server, &ServerSetup::logOut, this, &KDS::userLogOut);

    //���ܷ���KDS��ѯ�Լ��Ƿ���Խ���
    connect(&Server, &ServerSetup::isAbleDecrySignal, this, &KDS::isAbleDecry);

    //KDS����Ա˫��NewUser����ͬ��ע����û������е���һ����Ԫ��Ϊ���û������û����Լ�S������NewUser��ɾ�������������User��
    connect(
        ui.tableView_5,
        SIGNAL(doubleClicked(const QModelIndex&)),
        this, 
        SLOT(agreeClickedUser(const QModelIndex&))
    );

    //NewUserѡ�еĵ�Ԫ��ı�ʱ����enDeleteButtonʹɾ����ѡ�а�ť����
    connect(
        ui.tableView_5->selectionModel(),
        SIGNAL(selectionChanged(const QItemSelection&, const QItemSelection&)),
        this,
        SLOT(isEnableDeleteButton(const QItemSelection&, const QItemSelection&))
    );

}

KDS::~KDS()
{
}

int KDS::connectMYSQL()
{
    if (QSqlDatabase::contains("KDS"))//�ж�KDS�����Ƿ���ڲ�����
    {
        database = QSqlDatabase::database("KDS");
    }
    else //δ�������½����ݿ�����
    {
        database = QSqlDatabase::addDatabase("QMYSQL", "KDS");  //�������ݿ����ӣ���Ϊ������KDS
        database.setHostName("127.0.0.1");                      //�������ݿ���������������Ҫע��(�����Ϊ"127.0.0.1", ���ֲ������ӣ����Ϊlocalhost)
        database.setPort(3306);                                 //�������ݿ�˿ںţ�������һ��
        database.setUserName("KDS");                            //���ݿ��û�����������һ��
        database.setPassword("KDS");                            //���ݿ����룬������һ��
    }
    if (!database.open())
    {
        qDebug() << "fail to connect mysql:" << database.lastError().text();
        return 0;
    }
    qDebug() << "connect mysql success";

    return 1;
}

void KDS::createKDSAndTable()
{
    QString queryString;

    //�������ݿ�
    database = QSqlDatabase::database("KDS");
    queryString = "CREATE DATABASE IF NOT EXISTS KDS";
    database.exec(queryString);
    if (database.lastError().isValid())
    {
        qDebug() << "Create database failed:" << database.lastError().text();
        return;
    }

    //���δ���5�����ݱ�:RawParam��AccessPolicyMatrix��User��NewUser��LoggedUser
    database.setDatabaseName("KDS");
    if (!database.open())
    {
        qDebug() << "database open failed" << database.lastError().text();
        return;
    }

    //����RawParam��,���Լ���󳤶�500���ַ���U�����36�����ԣ���hx��˵����󳤶�Ϊ36*312+35=11267��312ΪȺG1Ԫ������Գ���
    //auto_increment
    queryString =
        "CREATE TABLE IF NOT EXISTS RawParam\
        (\
            uid int primary key not null auto_increment,\
            g varchar(320) not null,\
            e_g_g_alpha varchar(320) not null,\
            g_a varchar(320) not null,\
            hx varchar(11267) not null,\
            U varchar(500) not null unique,\
            MSK varchar(320) not null\
        )";
    database.exec(queryString);
    if (database.lastError().isValid())
    {
        qDebug() << "RawParam table creat failed:" << database.lastError().text();
        return;
    }
    database.exec("alter table RawParam convert to character set utf8");//֧������

    //����AccessPolicyMatrix��,AP�����40������
    queryString =
        "CREATE TABLE IF NOT EXISTS AccessPolicyMatrix\
        (\
            uid int primary key not null auto_increment,\
            AccessPolicy varchar(1000) not null,\
            APMatrix varchar(1700) not null,\
            MUID varchar(110) not null unique\
        )";
    database.exec(queryString);
    if (database.lastError().isValid())
    {
        qDebug() << "AccessPolicyMatrix table creat failed:" << database.lastError().text();
        return;
    }
    database.exec("alter table AccessPolicyMatrix convert to character set utf8");//֧������

    //����User��,SK��󳤶�Ϊ(5*320+48+10=1658)SK={z, TK},zΪZr�е�Ԫ�س���48��TK={K, L, Kx},����K��L��ΪG1�е�Ԫ�أ�Kx�����û����Լ�ȷ��(�û����Լ�S���ж��ٸ�����(Demo�����3��)Kx���ж��ٸ���KxΪG1�е�Ԫ��)
    queryString =
        "CREATE TABLE IF NOT EXISTS User\
        (\
            uid int primary key not null auto_increment,\
            name varchar(20) not null unique,\
            password varchar(20) not null,\
            S varchar(500) not null,\
            SK varchar(1658) not null\
        )";
    database.exec(queryString);
    if (database.lastError().isValid())
    {
        qDebug() << "User table creat failed:" << database.lastError().text();
        return;
    }
    database.exec("alter table User convert to character set utf8");//֧������

    //����NewUser��
    queryString =
        "CREATE TABLE IF NOT EXISTS NewUser\
        (\
            uid int primary key not null auto_increment,\
            name varchar(20) not null unique,\
            password varchar(20) not null\
        )";
    database.exec(queryString);
    if (database.lastError().isValid())
    {
        qDebug() << "NewUser table creat failed:" << database.lastError().text();
        return;
    }
    database.exec("alter table NewUser convert to character set utf8");//֧������

    //����LoggedUser��,cookie220���ַ�
    queryString =
        "CREATE TABLE IF NOT EXISTS LoggedUser\
        (\
            uid int primary key not null auto_increment,\
            name varchar(20) not null unique,\
            cookie varchar(230) not null\
        )";
    database.exec(queryString);
    if (database.lastError().isValid())
    {
        qDebug() << "LoggedUser table creat failed:" << database.lastError().text();
        return;
    }
    database.exec("alter table LoggedUser convert to character set utf8");//֧������
    qDebug() << "init KDS and tables success";

    return;
}

void KDS::showRawParam()
{
    RawParamModel->setQuery("select * from RawParam", database);//һ��Ҫ��database
    RawParamModel->setHeaderData(0, Qt::Horizontal, tr("uid"));
    RawParamModel->setHeaderData(1, Qt::Horizontal, tr("g"));
    RawParamModel->setHeaderData(2, Qt::Horizontal, tr("e(g,g)^alpha"));
    RawParamModel->setHeaderData(3, Qt::Horizontal, tr("g_a[g^a]"));
    RawParamModel->setHeaderData(4, Qt::Horizontal, tr("hx[����ȫ��U��Ӧ��G1�е�Ԫ��]"));
    RawParamModel->setHeaderData(5, Qt::Horizontal, tr("U[����ȫ��]"));
    RawParamModel->setHeaderData(6, Qt::Horizontal, tr("MSK[ϵͳ��˽Կ]"));
    ui.tableView->setModel(RawParamModel);
    ui.tableView->horizontalHeader()->setStyleSheet("QHeaderView { font-size: 12pt; }");
    //ui.tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //ui.tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
    ui.tableView->setColumnWidth(0, 50);
    ui.tableView->setColumnWidth(1, 50);
    ui.tableView->setColumnWidth(2, 120);
    ui.tableView->setColumnWidth(3, 100);
    ui.tableView->setColumnWidth(4, 250);
    ui.tableView->setColumnWidth(5, 100);
    ui.tableView->setColumnWidth(6, 150);
    ui.tableView->show();
}

void KDS::showAccessPolicyMatrix()
{
    AccessPolicyMatrixModel->setQuery("select * from AccessPolicyMatrix", database);//һ��Ҫ��database
    AccessPolicyMatrixModel->setHeaderData(0, Qt::Horizontal, tr("uid"));
    AccessPolicyMatrixModel->setHeaderData(1, Qt::Horizontal, tr("AccessPolicy[���ʲ���]"));
    AccessPolicyMatrixModel->setHeaderData(2, Qt::Horizontal, tr("APMatrix[���ʲ��Ծ���]"));
    AccessPolicyMatrixModel->setHeaderData(3, Qt::Horizontal, tr("MUID[��ϢΨһ��ʶ��]"));
    ui.tableView_2->setModel(AccessPolicyMatrixModel);
    ui.tableView_2->horizontalHeader()->setStyleSheet("QHeaderView { font-size: 12pt; }");
    //ui.tableView_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui.tableView_2->setColumnWidth(0,50);
    ui.tableView_2->setColumnWidth(1,200);
    ui.tableView_2->setColumnWidth(2,200);
    ui.tableView_2->setColumnWidth(3,200);
    ui.tableView_2->show();
}

void KDS::showUser()
{
    UserModel->setQuery("select * from User", database);//һ��Ҫ��database
    UserModel->setHeaderData(0, Qt::Horizontal, tr("uid"));
    UserModel->setHeaderData(1, Qt::Horizontal, tr("name"));
    UserModel->setHeaderData(2, Qt::Horizontal, tr("password"));
    UserModel->setHeaderData(3, Qt::Horizontal, tr("S[�û����Լ�]"));
    UserModel->setHeaderData(4, Qt::Horizontal, tr("SK[�û�˽Կ]"));
    ui.tableView_3->setModel(UserModel);
    ui.tableView_3->horizontalHeader()->setStyleSheet("QHeaderView { font-size: 12pt; }");
    //ui.tableView_3->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui.tableView_3->setColumnWidth(0, 50);
    ui.tableView_3->setColumnWidth(1, 100);
    ui.tableView_3->setColumnWidth(2, 100);
    ui.tableView_3->setColumnWidth(3, 150);
    ui.tableView_3->setColumnWidth(4, 200);
    ui.tableView_3->show();
}

void KDS::showLoggedUser()
{
    LoggedUserModel->setQuery("select * from LoggedUser", database);//һ��Ҫ��database
    LoggedUserModel->setHeaderData(0, Qt::Horizontal, tr("uid"));
    LoggedUserModel->setHeaderData(1, Qt::Horizontal, tr("name"));
    LoggedUserModel->setHeaderData(2, Qt::Horizontal, tr("cookie[������ʱ��֤]"));
    ui.tableView_4->setModel(LoggedUserModel);
    ui.tableView_4->horizontalHeader()->setStyleSheet("QHeaderView { font-size: 12pt; }");
    //ui.tableView_4->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//�������Զ�����
    ui.tableView_4->setColumnWidth(0, 50);
    ui.tableView_4->setColumnWidth(1, 100);
    ui.tableView_4->setColumnWidth(2, 200);
    ui.tableView_4->show();
}

void KDS::showNewUser()
{
    NewUserModel->setQuery("select * from NewUser", database);//һ��Ҫ��database
    NewUserModel->setHeaderData(0, Qt::Horizontal, tr("uid"));
    NewUserModel->setHeaderData(1, Qt::Horizontal, tr("name"));
    NewUserModel->setHeaderData(2, Qt::Horizontal, tr("password"));
    ui.tableView_5->setModel(NewUserModel);
    ui.tableView_5->horizontalHeader()->setStyleSheet("QHeaderView { font-size: 12pt; }");
    //ui.tableView_5->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui.tableView_5->setColumnWidth(0, 50);
    ui.tableView_5->setColumnWidth(1, 100);
    ui.tableView_5->show();
}

void KDS::insertRawParam(QString& U)
{
    //�������ϵͳ����������QString���͵�hx
    //database = QSqlDatabase::database("KDS");
    QString sqlQueryString = "insert into RawParam (g, e_g_g_alpha, g_a, hx, U, MSK) values (\"";
    qDebug() << "g =" << KDSPBC.elementToQString(KDSPBC.g);
    qDebug() << "e_g_g_alpha =" << KDSPBC.elementToQString(KDSPBC.e_g_g_alpha);
    qDebug() << "g_a =" << KDSPBC.elementToQString(KDSPBC.g_a);
    qDebug() << "hx =" << KDSPBC.U2hx(U);
    qDebug() << "MSK =" << KDSPBC.elementToQString(KDSPBC.MSK);
    
    sqlQueryString += KDSPBC.elementToQString(KDSPBC.g);
    sqlQueryString += "\", \"";
    sqlQueryString += KDSPBC.elementToQString(KDSPBC.e_g_g_alpha);
    sqlQueryString += "\", \"";
    sqlQueryString += KDSPBC.elementToQString(KDSPBC.g_a);
    sqlQueryString += "\", \"";
    sqlQueryString += KDSPBC.U2hx(U);
    sqlQueryString += "\", \"";
    sqlQueryString += U;
    sqlQueryString += "\", \"";
    sqlQueryString += KDSPBC.elementToQString(KDSPBC.MSK);
    sqlQueryString += "\")";

    database.exec(sqlQueryString);//��ϵͳ��������RawParam

    return;
}

void KDS::insertUser(QString& userName, QString& passwd, QString& S, QString& SK)
{
    QSqlQuery query = QSqlQuery(database);//���Ѵ򿪵�database���ݿ����
    query.exec(QString("insert into User (name, password, S, SK) values('%1', '%2', '%3', '%4')").arg(userName, passwd, S, SK));
    showUser();
}

void KDS::on_pushButton_clicked()//�ύ���Լ�U
{
    QString U = ui.plainTextEdit->toPlainText();//��QString���������U��Ӣ�Ķ��Ÿ���
    insertRawParam(U);//����U����ϵͳ����PK��MSK�Ȳ���RawParam����
    showRawParam();//��ʾRawParam������

    ui.pushButton->setDisabled(true);   //Ŀǰֻ���ύһ������ȫ��U
    ui.plainTextEdit->setReadOnly(true);    //����ֻ��

    return;
}

void KDS::on_pushButton_2_clicked()
{
    QItemSelectionModel* select = ui.tableView_5->selectionModel();
    QModelIndexList indexList = select->selectedIndexes();
    QVector<int> rowVector;//���ѡ����û������������ظ�
    for (QModelIndexList::iterator iter = indexList.begin(); iter != indexList.end(); iter++)
    {
        if (!rowVector.contains((*iter).row()))//���row��rowVector�в�����
            rowVector.append((*iter).row());
    }

    for (QVector<int>::iterator iter = rowVector.begin(); iter != rowVector.end(); iter++)//������ѡ����
    {
        QModelIndex index = NewUserModel->index(*iter, 1, QModelIndex());
        QString userName = index.data().toString();//����*iter�д�����û����û���
        deleteUserFromNewUser(userName);
    }
    ui.pushButton_2->setDisabled(true);//����ɾ����ť
    //ui.pushButton_2->setEnabled(false);
}

void KDS::showServerIpPort()
{
    ui.label_7->setText(tr("The server is running on %1: %2").arg(Server.ipAddress.toString()).arg(QString::number(Server.tcpServer->serverPort())));
}

void KDS::isExisted(bool& ret, const QString& tableToQuery, const QString& field, const QString& queryQstr)
{
    //qDebug() << "here is isExisted";
    QSqlQuery query = QSqlQuery(database);//���Ѵ򿪵�database���ݿ����
    //qDebug() << QString("isExisted sentence : select * from %1 where %2 = '%3'").arg(tableToQuery, field, queryQstr);
    
    query.exec(QString("select * from %1 where %2 = '%3'").arg(tableToQuery, field, queryQstr));//ע��ֻ�����һ��%3��������
    if (!query.next())
    {
        //qDebug() << "Not exist.";
        ret = false;
    }
    else
    {
        //qDebug() << "Exists.";
        ret = true;
    }
}

void KDS::insertNewUser(const QString& tableToQuery, const QString& name, const QString& passwd)
{
    QSqlQuery query = QSqlQuery(database);//���Ѵ򿪵�database���ݿ����
    //qDebug() << QString("insertNewUser sentence : insert into %1 (name,password) values('%2','%3')").arg(tableToQuery, name, passwd);
    //�����û�����NewUser����
    query.exec(QString("insert into %1 (name, password) values('%2','%3')").arg(tableToQuery, name, passwd));
    showNewUser();
}

void KDS::insertAPM(QString& AccessPolicy, QString& APMatrix, QString& MUID)
{
    QSqlQuery query = QSqlQuery(database);//���Ѵ򿪵�database���ݿ����
    query.exec(QString("insert into AccessPolicyMatrix (AccessPolicy, APMatrix, MUID) values('%1','%2','%3')").arg(AccessPolicy, APMatrix, MUID));
    showAccessPolicyMatrix();
}

void KDS::matchNamePasswd(bool& ret, const QString& name, const QString& passwd)
{
    QSqlQuery query = QSqlQuery(database);//���Ѵ򿪵�database���ݿ����
    //qDebug() << QString("matchNamePasswd sentence : select * from User where name = '%1' and password = '%2'").arg(name, passwd);
    query.exec(QString("select * from User where name = '%1' and password = '%2'").arg(name, passwd));
    if (!query.next())
    {
        qDebug() << "Name and Password not match.";
        ret = false;
    }
    else
    {
        qDebug() << "Name and Password matched.";
        ret = true;
    }
}

void KDS::userLogin(QString name)
{
    //����Ϊ�û�������ʱ220λ�����ʱcookie
    QString cookie = getRandomString(220);
    
    //Ȼ���û�����cookieд��LoggedUser����
    QSqlQuery query = QSqlQuery(database);//���Ѵ򿪵�database���ݿ����
    //qDebug() << QString("LoggedUser sentence : insert into LoggedUser (name,cookie) values('%1','%2')").arg(name, cookie);
    query.exec(QString("insert into LoggedUser (name,cookie) values('%1','%2')").arg(name, cookie));
    showLoggedUser();

    //��ѯUser���ȡ�û���Ϣ
    query.exec(QString("select name, password, S, SK from User where name = '%1'").arg(name));
    QString userInfo;
    while (query.next())
    {
        userInfo = query.value(0).toString();//name
        userInfo += ";";
        userInfo += query.value(1).toString();//password
        userInfo += ";";
        userInfo += query.value(3).toString();//SK
        userInfo += ";";
        userInfo += cookie;                   //cookie
        userInfo += ";";
        userInfo += query.value(2).toString();//S
    }
    query.exec(QString("select g, e_g_g_alpha, g_a, hx from RawParam"));//��ȡ��Կ(ϵͳ����)PK
    while (query.next())
    {
        userInfo += ";";
        userInfo += query.value(0).toString();//g
        userInfo += ";";
        userInfo += query.value(1).toString();//e(g,g)^alpha
        userInfo += ";";
        userInfo += query.value(2).toString();//g^a
        userInfo += ";";
        userInfo += query.value(3).toString();//hx
    }
    Server.serverSocket->waitForReadyRead();//�ȴ��ͻ�������ϴ���Ϣ�Ĵ���Ȼ��ڶ�����ͻ��˷��� �û���¼��Ϣ[�û���;����;SK;cookie;S;g;e(g,g)^alpha;g^a;hx]
    
    QByteArray rawArray = userInfo.toUtf8();
    QByteArray sendArray;//������͵��ֽ�������8192��ֶη���
    //qDebug() << userInfo.size();
    if (rawArray.size() <= 8192)//������͵��ֽ���С�ڽ��ܶ��������ֽ���(8192)��ֱ�ӷ���
        Server.serverSocket->write(rawArray);
    else 
    {
        //sendArray = rawArray.mid(0, 8192);//ǰ8192�ֽ�
        while (rawArray.size() > 8192)//ʣ���ֽ�������8192
        {
            sendArray = rawArray.mid(0, 8192);//ȡ�����ֽ���ǰ8192�ֽڷ���
            rawArray = rawArray.mid(8192);//ȥ��ǰ8192�ֽ�
            Server.serverSocket->write(sendArray);
            Server.serverSocket->flush();
        }
        Server.serverSocket->write(rawArray);
        Server.serverSocket->flush();
    }
}

void KDS::userLogOut(const QString& name, const QString& cookie)
{
    //QMessageBox::information(this, "exit", "user log out");
    QSqlQuery query = QSqlQuery(database);//���Ѵ򿪵�database���ݿ����
    query.exec(QString("delete from LoggedUser where name = '%1' and cookie = '%2'").arg(name, cookie));
    //qDebug() << QString("delete from LoggedUser where name = '%1' and cookie = '%2'").arg(name, cookie);
    showLoggedUser();
}

QString KDS::getRandomString(int length)
{
    QString symbols = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    QRandomGenerator* rng = QRandomGenerator::global();
    QString randomQstr;
    for (int i = 0; i < length; ++i) {
        int index = rng->bounded(symbols.length());
        randomQstr += symbols.at(index);
    }
    return randomQstr;
}

bool KDS::isSvalid(QString& S)
{
    QStringList qstrListS = S.split(",");
    QStringList U;

    QSqlQuery query = QSqlQuery(database);//���Ѵ򿪵�database���ݿ����
    query.exec(QString("select U from RawParam"));
    if (query.next())
        U = query.value(0).toString().split(",");

    for (QList<QString>::Iterator iter = qstrListS.begin(); iter != qstrListS.end(); iter++)
    {
        if (!U.contains(*iter))
            return false;
    }
    return true;
}

void KDS::deleteUserFromNewUser(QString& userName)
{
    QSqlQuery query = QSqlQuery(database);//���Ѵ򿪵�database���ݿ����
    query.exec(QString("delete from NewUser where name = '%1'").arg(userName));
    showNewUser();
}

QString KDS::getUserSK(QString& S)
{
    //���Ȼ�ȡhx����QStringList
    QSqlQuery query = QSqlQuery(database);//���Ѵ򿪵�database���ݿ����
    query.exec(QString("select hx from RawParam"));
    QStringList hxList;//���hx
    if (query.next())
        hxList = query.value(0).toString().split(";");

    //Ȼ���ȡ����ȫ��U
    QStringList U;
    query.exec(QString("select U from RawParam"));
    if (query.next())
        U = query.value(0).toString().split(",");

    return KDSPBC.SToSK(S, U, hxList);
}

void KDS::isExistU()
{
    QSqlQuery query = QSqlQuery(database);//���Ѵ򿪵�database���ݿ����
    query.exec(QString("select U from RawParam"));
    if (query.next())//������ݿ����Ѿ�����һ��U,���������U�Ŀؼ�
    {
        ui.pushButton->setDisabled(true);
        ui.plainTextEdit->setReadOnly(true);
        ui.plainTextEdit->setPlainText(query.value(0).toString());
        showRawParam();
    }
}

void KDS::agreeClickedUser(const QModelIndex&)
{
    //����indexΪ��ǰ˫���е�name��
    QModelIndex indexName = NewUserModel->index(ui.tableView_5->currentIndex().row(), 1, QModelIndex());
    QModelIndex indexPasswd = NewUserModel->index(ui.tableView_5->currentIndex().row(), 2, QModelIndex());

    if (indexName.isValid())
    {
        QString userName = indexName.data().toString();//����˫�����д�����û����û���
        QString userPasswd = indexPasswd.data().toString();//�����û�����
        //���ȵ��������Ϊ�û�ָ�����Լ�
        bool ok;
        QString attributeS = QInputDialog::getMultiLineText(this, "�������Լ�S", QString("��Ϊ�û� %1 ��ȫ��U��ָ�����Լ�S(��˳������,����֮����\",\"����)").arg(userName), "����1,����2,...,����n", &ok);
        if (ok && !attributeS.isEmpty())
        {
            //�ж���������Լ��Ƿ�������ȫ��U����
            if (isSvalid(attributeS))
            {
                QString SK = getUserSK(attributeS);//��ȡ�û�˽ԿSK
                insertUser(userName, userPasswd, attributeS, SK);
                deleteUserFromNewUser(userName);
            }
            else//��������Լ��Ƿ�������Ϊ����ȫ��U���Ӽ��ϣ���������������ϸ�֣���S�޶�����Ϊ3�����Բ����ظ���
                QMessageBox::critical(this, "warn", "���Ա������������ȫ��U�У�");
        }
    }
    else
        QMessageBox::critical(this, "warn", "invalid clicked");
}

void KDS::isEnableDeleteButton(const QItemSelection& selected, const QItemSelection& deselected)
{
    QItemSelectionModel* select = ui.tableView_5->selectionModel();
    if (select->selectedIndexes().isEmpty())//û���û���ѡ��
        ui.pushButton_2->setDisabled(true);
    else                                    //���û���ѡ��
        ui.pushButton_2->setDisabled(false);
        
}

void KDS::matchCookie(bool& ret, const QString& cookie)
{
    QSqlQuery query = QSqlQuery(database);//���Ѵ򿪵�database���ݿ����
    query.exec(QString("select cookie from LoggedUser"));
    while (query.next())//��������cookie
        if (cookie == query.value(0).toString())//cookie�Ϸ�retΪtrue������Ĭ��(false)
            ret = true;
}

void KDS::getAPMatrix(QString& APMatrix, QStringList& APList, int MaxSize)
{
    Eigen::MatrixXd APM = Eigen::MatrixXd::Zero(MaxSize, MaxSize);//��������ķ��ʲ��Ծ���
    Eigen::MatrixXd ANDM = Eigen::MatrixXd::Zero(MaxSize, MaxSize);//APList��ÿ��Ԫ�ض�Ӧ�ķ��ʲ��Ծ���
    Eigen::MatrixXd m1 = Eigen::MatrixXd::Ones(1, 1);//��λ����[1]

    for (QStringList::iterator iterA = APList.begin(); iterA != APList.end(); iterA++)//������
    {
        QStringList subS = (*iterA).split(",");
        //������
        ANDM = m1;//��ʼΪ[1]
        for (QStringList::iterator iterB = subS.begin(); iterB != subS.end() - 1; iterB++)//������
            ANDM = M_AND(ANDM, m1);
        //std::cout << "ANDM = " << std::endl << ANDM << std::endl;
        //�����
        if (iterA == APList.begin())     //��һ�α���ʱִ��
            APM = ANDM;                 //��ʼ��Ϊ��һ�������Ӽ��ϵķ��ʲ��Ծ���
        else                            //���ڻ�ṹ���ҵڶ��α���ʱִ��
            APM = M_OR(APM, ANDM);
        //std::cout << "APM = " << std::endl << APM << std::endl;
    }
    //std::cout << "APM = " << std::endl << APM << std::endl;
    
    APMatrix = MatrixToQString(APM);

}

QString KDS::MatrixToQString(Eigen::MatrixXd& APM)
{
    std::stringstream ssAPM;
    ssAPM << APM;
    QString APMatrix = QString::fromStdString(ssAPM.str());
    ssAPM.str("");

    return APMatrix;
}

void KDS::getMUID(QString& MUID, QStringList& APList)
{
    MUID = getRandomString(110);//MUID����Ϊ110
}

Eigen::MatrixXd KDS::M_AND(Eigen::MatrixXd& m1, Eigen::MatrixXd& m2)//����m1&m2��Ӧ�ķ��ʲ��Ծ���
{
    Eigen::MatrixXd m_and = Eigen::MatrixXd::Zero(m1.rows() + m2.rows(), m1.cols() + m2.cols());//����ʲ��Ծ���
    m_and.block(0, 0, m1.rows(), 1) = m1.col(0);
    m_and.block(0, 1, m1.rows(), 1) = m1.col(0);
    m_and.block(m1.rows(), 1, m2.rows(), 1) = m2.col(0);
    m_and.block(0, 2, m1.rows(), m1.cols() - 1) = m1.rightCols(m1.cols() - 1);
    m_and.block(m1.rows(), m1.cols() + 1, m2.rows(), m2.cols() - 1) = m2.rightCols(m2.cols() - 1);

    return m_and;
}

Eigen::MatrixXd KDS::M_OR(Eigen::MatrixXd& m1, Eigen::MatrixXd& m2)//����m1|m2��Ӧ�ķ��ʲ��Ծ���
{
    Eigen::MatrixXd m_or = Eigen::MatrixXd::Zero(m1.rows() + m2.rows(), m1.cols() + m2.cols() - 1);//����ʲ��Ծ���
    m_or.block(0, 0, m1.rows(), 1) = m1.col(0);
    m_or.block(m1.rows(), 0, m2.rows(), 1) = m2.col(0);
    m_or.block(0, 1, m1.rows(), m1.cols() - 1) = m1.rightCols(m1.cols() - 1);
    m_or.block(m1.rows(), m1.cols(), m2.rows(), m2.cols() - 1) = m2.rightCols(m2.cols() - 1);

    return m_or;
}

Eigen::MatrixXd KDS::toMatrix(QString matrixQstr)
{
    Eigen::MatrixXd destMatrix;
    QStringList rowList = matrixQstr.split("\n");
    int rowNum = (int)rowList.size();

    for (QStringList::iterator iterRow = rowList.begin(); iterRow != rowList.end(); iterRow++) {
        QStringList metaItemList = (*iterRow).split(" ");//ÿ�е�Ԫ������б�
        if (iterRow == rowList.begin())//��һ��ѭ��ָ��destMatrix�Ĵ�С��Ϊ������ڴ�
        {
            int colNum = (int)metaItemList.size();
            destMatrix.resize(rowNum, colNum);//ָ����С
        }
        for (QStringList::iterator iterCol = metaItemList.begin(); iterCol != metaItemList.end(); iterCol++)
            destMatrix(std::distance(rowList.begin(), iterRow), std::distance(metaItemList.begin(), iterCol)) = (*iterCol).toInt();
    }
    //std::cout << destMatrix << std::endl;
    return destMatrix;
}

void KDS::getOrderHx(QString& APQstr, QString& HXNUM)
{
    QSqlQuery query = QSqlQuery(database);//���Ѵ򿪵�database���ݿ����
    query.exec(QString("select U from RawParam"));
    query.next();
    QStringList numHx;//��ŷ��ʲ���λ�õ��б�
    QStringList U = query.value(0).toString().split(",");
    QStringList subAttr = APQstr.split(";");//�����ʲ��԰��ֺŷֿ�
    for (QStringList::iterator iter = subAttr.begin(); iter != subAttr.end(); iter++)
    {
        QStringList Attr = (*iter).split(",");//Attr�е�Ԫ��Ϊ���ʲ����е�����
        for (QStringList::iterator iterAttr = Attr.begin(); iterAttr != Attr.end(); iterAttr++)
            numHx.append(QString::number((quint32)U.indexOf(*iterAttr), 10));
    }

    HXNUM = numHx.join(",");
}

void KDS::isAbleDecry(QString cookie, QString MUID)
{
    QSqlQuery query = QSqlQuery(database);//���Ѵ򿪵�database���ݿ����

    //��ѯcookie��Ӧ���û���
    query.exec(QString("select name from LoggedUser where cookie = '%1'").arg(cookie));
    query.next();
    QString userName = query.value(0).toString();
    //��ѯ�û�����Ӧ�����Լ�S
    query.exec(QString("select S from User where name = '%1'").arg(userName));
    query.next();
    QStringList userSList = query.value(0).toString().split(",");
    //��ѯMUID��Ӧ�ķ��ʲ���
    query.exec(QString("select AccessPolicy from AccessPolicyMatrix where MUID = '%1'").arg(MUID));
    query.next();
    QStringList APList = query.value(0).toString().split(";");

    int firstRow = 0;//�ֱ��ӦS������ʲ��Ե��Ӽ����ڷ��ʲ������������е�λ�ã�����֮������
    int lastRow = 0;

    QStringList accessAPSetList;//������ʲ��Ե��û����Լ��е�һ���Ӽ��б�
    for (QStringList::iterator iter = APList.begin(); iter != APList.end(); iter++)//��������������ʲ��Ե��Ӽ���
    {
        QStringList subSet = (*iter).split(",");
        //qDebug() << "subSet = " << subSet;
        bool access = true;

        for (QStringList::iterator iterSubSet = subSet.begin(); iterSubSet != subSet.end(); iterSubSet++)//����ÿ���Ӽ���Ԫ��(����)
        {
            if (!userSList.contains(*iterSubSet))//�û����Լ������㵱ǰ���ʲ����Ӽ���
            {
                access = false;
                break;
            }
        }
        if (access == true)//��һ���Ӽ��Ͼ����û����Լ���������ʲ��Ե�һ���Ӽ���
        {
            accessAPSetList = subSet;
            break;
        }
        firstRow += subSet.size();
    }

    if (accessAPSetList.isEmpty())//�û����Լ���������ʲ���
    {
        Server.serverSocket->write(QString("0;����Ȩ���ܸ��ļ�!").toUtf8());
        return;
    }

    lastRow =  firstRow + accessAPSetList.size() - 1;

    QStringList KxOrderList;
    for (QStringList::iterator iter = accessAPSetList.begin(); iter != accessAPSetList.end(); iter++)//�����û�������ʲ��Ե������Ӽ�accessAPSetList
        KxOrderList.append(QString::number(userSList.indexOf(*iter)));

    QString subTAPMQstr = getSubTMatrix(MUID, firstRow, lastRow);//����MUID��Ӧ��APM�е�firstRow��lastRow֮��(����firstRow��lastRow)���Ӿ����ת�þ���

    QString retQstr = "1;" + KxOrderList.join(",") + ";" + subTAPMQstr + ";" + QString::number(firstRow);
    Server.serverSocket->write(retQstr.toUtf8());

}

QString KDS::getSubTMatrix(QString& MUID, int& firstRow, int& lastRow)
{
    QSqlQuery query = QSqlQuery(database);//���Ѵ򿪵�database���ݿ����
    query.exec(QString("select APMatrix from AccessPolicyMatrix where MUID = '%1'").arg(MUID));
    query.next();
    QString APMQstr = query.value(0).toString();
    Eigen::MatrixXd APM = toMatrix(APMQstr);

    Eigen::Index col = APM.cols();
    Eigen::Index row = lastRow - firstRow + 1;
    Eigen::MatrixXd SubAPM(row, col);
    SubAPM = APM.block(firstRow, 0, row, col);

    Eigen::MatrixXd SubTAPM(col, row);//SubAPM��ת�þ���
    SubTAPM = SubAPM.transpose();

    return MatrixToQString(SubTAPM);
}