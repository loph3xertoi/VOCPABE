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
    if (connectMYSQL())//连接mysql成功则初始化数据库和表
        createKDSAndTable();
    else return;
    showServerIpPort();
    ui.tabWidget->setStyleSheet("QTabWidget { border-top-color: rgba(255, 255, 255, 0); }");//设置tab边框透明
    ui.pushButton_2->setDisabled(true);//初始NewUser表没有用户被选中，删除所选用户按钮不可用
    
    //showRawParam();
    showAccessPolicyMatrix();
    showUser();
    showLoggedUser();
    showNewUser();
    isExistU();

    //用户成功登录时发送loginSignal信号，执行userLogin函数
    connect(&Server, &ServerSetup::loginSignal, this, &KDS::userLogin);

    //用户退出时将用户信息从LoggedUser表中去除
    connect(&Server, &ServerSetup::logOut, this, &KDS::userLogOut);

    //解密方向KDS查询自己是否可以解密
    connect(&Server, &ServerSetup::isAbleDecrySignal, this, &KDS::isAbleDecry);

    //KDS管理员双击NewUser表中同意注册的用户所在行的任一个单元格，为该用户输入用户属性集S，并从NewUser表删除，并将其插入User表
    connect(
        ui.tableView_5,
        SIGNAL(doubleClicked(const QModelIndex&)),
        this, 
        SLOT(agreeClickedUser(const QModelIndex&))
    );

    //NewUser选中的单元格改变时调用enDeleteButton使删除所选行按钮可用
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
    if (QSqlDatabase::contains("KDS"))//判断KDS连接是否存在并连接
    {
        database = QSqlDatabase::database("KDS");
    }
    else //未连接则新建数据库连接
    {
        database = QSqlDatabase::addDatabase("QMYSQL", "KDS");  //创建数据库连接，并为其命名KDS
        database.setHostName("127.0.0.1");                      //连接数据库主机名，这里需要注意(若填的为"127.0.0.1", 出现不能连接，则改为localhost)
        database.setPort(3306);                                 //连接数据库端口号，与设置一致
        database.setUserName("KDS");                            //数据库用户名，与设置一致
        database.setPassword("KDS");                            //数据库密码，与设置一致
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

    //创建数据库
    database = QSqlDatabase::database("KDS");
    queryString = "CREATE DATABASE IF NOT EXISTS KDS";
    database.exec(queryString);
    if (database.lastError().isValid())
    {
        qDebug() << "Create database failed:" << database.lastError().text();
        return;
    }

    //依次创建5个数据表:RawParam、AccessPolicyMatrix、User、NewUser、LoggedUser
    database.setDatabaseName("KDS");
    if (!database.open())
    {
        qDebug() << "database open failed" << database.lastError().text();
        return;
    }

    //创建RawParam表,属性集最大长度500个字符；U中最多36个属性，对hx来说，最大长度为36*312+35=11267，312为群G1元素坐标对长度
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
    database.exec("alter table RawParam convert to character set utf8");//支持中文

    //创建AccessPolicyMatrix表,AP中最多40个属性
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
    database.exec("alter table AccessPolicyMatrix convert to character set utf8");//支持中文

    //创建User表,SK最大长度为(5*320+48+10=1658)SK={z, TK},z为Zr中的元素长度48，TK={K, L, Kx},其中K、L均为G1中的元素，Kx根据用户属性集确定(用户属性集S中有多少个属性(Demo中最大3个)Kx就有多少个，Kx为G1中的元素)
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
    database.exec("alter table User convert to character set utf8");//支持中文

    //创建NewUser表
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
    database.exec("alter table NewUser convert to character set utf8");//支持中文

    //创建LoggedUser表,cookie220个字符
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
    database.exec("alter table LoggedUser convert to character set utf8");//支持中文
    qDebug() << "init KDS and tables success";

    return;
}

void KDS::showRawParam()
{
    RawParamModel->setQuery("select * from RawParam", database);//一定要绑定database
    RawParamModel->setHeaderData(0, Qt::Horizontal, tr("uid"));
    RawParamModel->setHeaderData(1, Qt::Horizontal, tr("g"));
    RawParamModel->setHeaderData(2, Qt::Horizontal, tr("e(g,g)^alpha"));
    RawParamModel->setHeaderData(3, Qt::Horizontal, tr("g_a[g^a]"));
    RawParamModel->setHeaderData(4, Qt::Horizontal, tr("hx[属性全集U对应的G1中的元素]"));
    RawParamModel->setHeaderData(5, Qt::Horizontal, tr("U[属性全集]"));
    RawParamModel->setHeaderData(6, Qt::Horizontal, tr("MSK[系统主私钥]"));
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
    AccessPolicyMatrixModel->setQuery("select * from AccessPolicyMatrix", database);//一定要绑定database
    AccessPolicyMatrixModel->setHeaderData(0, Qt::Horizontal, tr("uid"));
    AccessPolicyMatrixModel->setHeaderData(1, Qt::Horizontal, tr("AccessPolicy[访问策略]"));
    AccessPolicyMatrixModel->setHeaderData(2, Qt::Horizontal, tr("APMatrix[访问策略矩阵]"));
    AccessPolicyMatrixModel->setHeaderData(3, Qt::Horizontal, tr("MUID[消息唯一标识码]"));
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
    UserModel->setQuery("select * from User", database);//一定要绑定database
    UserModel->setHeaderData(0, Qt::Horizontal, tr("uid"));
    UserModel->setHeaderData(1, Qt::Horizontal, tr("name"));
    UserModel->setHeaderData(2, Qt::Horizontal, tr("password"));
    UserModel->setHeaderData(3, Qt::Horizontal, tr("S[用户属性集]"));
    UserModel->setHeaderData(4, Qt::Horizontal, tr("SK[用户私钥]"));
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
    LoggedUserModel->setQuery("select * from LoggedUser", database);//一定要绑定database
    LoggedUserModel->setHeaderData(0, Qt::Horizontal, tr("uid"));
    LoggedUserModel->setHeaderData(1, Qt::Horizontal, tr("name"));
    LoggedUserModel->setHeaderData(2, Qt::Horizontal, tr("cookie[用于临时认证]"));
    ui.tableView_4->setModel(LoggedUserModel);
    ui.tableView_4->horizontalHeader()->setStyleSheet("QHeaderView { font-size: 12pt; }");
    //ui.tableView_4->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//设置列自动拉伸
    ui.tableView_4->setColumnWidth(0, 50);
    ui.tableView_4->setColumnWidth(1, 100);
    ui.tableView_4->setColumnWidth(2, 200);
    ui.tableView_4->show();
}

void KDS::showNewUser()
{
    NewUserModel->setQuery("select * from NewUser", database);//一定要绑定database
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
    //随机生成系统参数并生成QString类型的hx
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

    database.exec(sqlQueryString);//将系统参数插入RawParam

    return;
}

void KDS::insertUser(QString& userName, QString& passwd, QString& S, QString& SK)
{
    QSqlQuery query = QSqlQuery(database);//绑定已打开的database数据库对象
    query.exec(QString("insert into User (name, password, S, SK) values('%1', '%2', '%3', '%4')").arg(userName, passwd, S, SK));
    showUser();
}

void KDS::on_pushButton_clicked()//提交属性集U
{
    QString U = ui.plainTextEdit->toPlainText();//用QString保存输入的U，英文逗号隔开
    insertRawParam(U);//根据U生成系统参数PK，MSK等插入RawParam表中
    showRawParam();//显示RawParam表内容

    ui.pushButton->setDisabled(true);   //目前只能提交一次属性全集U
    ui.plainTextEdit->setReadOnly(true);    //设置只读

    return;
}

void KDS::on_pushButton_2_clicked()
{
    QItemSelectionModel* select = ui.tableView_5->selectionModel();
    QModelIndexList indexList = select->selectedIndexes();
    QVector<int> rowVector;//存放选择的用户的行数，不重复
    for (QModelIndexList::iterator iter = indexList.begin(); iter != indexList.end(); iter++)
    {
        if (!rowVector.contains((*iter).row()))//如果row在rowVector中不存在
            rowVector.append((*iter).row());
    }

    for (QVector<int>::iterator iter = rowVector.begin(); iter != rowVector.end(); iter++)//遍历所选行数
    {
        QModelIndex index = NewUserModel->index(*iter, 1, QModelIndex());
        QString userName = index.data().toString();//保存*iter行代表的用户的用户名
        deleteUserFromNewUser(userName);
    }
    ui.pushButton_2->setDisabled(true);//禁用删除按钮
    //ui.pushButton_2->setEnabled(false);
}

void KDS::showServerIpPort()
{
    ui.label_7->setText(tr("The server is running on %1: %2").arg(Server.ipAddress.toString()).arg(QString::number(Server.tcpServer->serverPort())));
}

void KDS::isExisted(bool& ret, const QString& tableToQuery, const QString& field, const QString& queryQstr)
{
    //qDebug() << "here is isExisted";
    QSqlQuery query = QSqlQuery(database);//绑定已打开的database数据库对象
    //qDebug() << QString("isExisted sentence : select * from %1 where %2 = '%3'").arg(tableToQuery, field, queryQstr);
    
    query.exec(QString("select * from %1 where %2 = '%3'").arg(tableToQuery, field, queryQstr));//注意只有最后一个%3带有引号
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
    QSqlQuery query = QSqlQuery(database);//绑定已打开的database数据库对象
    //qDebug() << QString("insertNewUser sentence : insert into %1 (name,password) values('%2','%3')").arg(tableToQuery, name, passwd);
    //将新用户插入NewUser表中
    query.exec(QString("insert into %1 (name, password) values('%2','%3')").arg(tableToQuery, name, passwd));
    showNewUser();
}

void KDS::insertAPM(QString& AccessPolicy, QString& APMatrix, QString& MUID)
{
    QSqlQuery query = QSqlQuery(database);//绑定已打开的database数据库对象
    query.exec(QString("insert into AccessPolicyMatrix (AccessPolicy, APMatrix, MUID) values('%1','%2','%3')").arg(AccessPolicy, APMatrix, MUID));
    showAccessPolicyMatrix();
}

void KDS::matchNamePasswd(bool& ret, const QString& name, const QString& passwd)
{
    QSqlQuery query = QSqlQuery(database);//绑定已打开的database数据库对象
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
    //首先为用户生成临时220位随机临时cookie
    QString cookie = getRandomString(220);
    
    //然后将用户名和cookie写入LoggedUser表中
    QSqlQuery query = QSqlQuery(database);//绑定已打开的database数据库对象
    //qDebug() << QString("LoggedUser sentence : insert into LoggedUser (name,cookie) values('%1','%2')").arg(name, cookie);
    query.exec(QString("insert into LoggedUser (name,cookie) values('%1','%2')").arg(name, cookie));
    showLoggedUser();

    //查询User表获取用户信息
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
    query.exec(QString("select g, e_g_g_alpha, g_a, hx from RawParam"));//获取公钥(系统参数)PK
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
    Server.serverSocket->waitForReadyRead();//等待客户端完成上次信息的处理，然后第二次向客户端发送 用户登录信息[用户名;密码;SK;cookie;S;g;e(g,g)^alpha;g^a;hx]
    
    QByteArray rawArray = userInfo.toUtf8();
    QByteArray sendArray;//如果发送的字节数超过8192则分段发送
    //qDebug() << userInfo.size();
    if (rawArray.size() <= 8192)//如果发送的字节数小于接受端最大接受字节数(8192)，直接发送
        Server.serverSocket->write(rawArray);
    else 
    {
        //sendArray = rawArray.mid(0, 8192);//前8192字节
        while (rawArray.size() > 8192)//剩余字节数大于8192
        {
            sendArray = rawArray.mid(0, 8192);//取现有字节流前8192字节发送
            rawArray = rawArray.mid(8192);//去掉前8192字节
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
    QSqlQuery query = QSqlQuery(database);//绑定已打开的database数据库对象
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

    QSqlQuery query = QSqlQuery(database);//绑定已打开的database数据库对象
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
    QSqlQuery query = QSqlQuery(database);//绑定已打开的database数据库对象
    query.exec(QString("delete from NewUser where name = '%1'").arg(userName));
    showNewUser();
}

QString KDS::getUserSK(QString& S)
{
    //首先获取hx存入QStringList
    QSqlQuery query = QSqlQuery(database);//绑定已打开的database数据库对象
    query.exec(QString("select hx from RawParam"));
    QStringList hxList;//存放hx
    if (query.next())
        hxList = query.value(0).toString().split(";");

    //然后获取属性全集U
    QStringList U;
    query.exec(QString("select U from RawParam"));
    if (query.next())
        U = query.value(0).toString().split(",");

    return KDSPBC.SToSK(S, U, hxList);
}

void KDS::isExistU()
{
    QSqlQuery query = QSqlQuery(database);//绑定已打开的database数据库对象
    query.exec(QString("select U from RawParam"));
    if (query.next())//如果数据库中已经存在一条U,则禁用输入U的控件
    {
        ui.pushButton->setDisabled(true);
        ui.plainTextEdit->setReadOnly(true);
        ui.plainTextEdit->setPlainText(query.value(0).toString());
        showRawParam();
    }
}

void KDS::agreeClickedUser(const QModelIndex&)
{
    //设置index为当前双击行的name列
    QModelIndex indexName = NewUserModel->index(ui.tableView_5->currentIndex().row(), 1, QModelIndex());
    QModelIndex indexPasswd = NewUserModel->index(ui.tableView_5->currentIndex().row(), 2, QModelIndex());

    if (indexName.isValid())
    {
        QString userName = indexName.data().toString();//保存双击的行代表的用户的用户名
        QString userPasswd = indexPasswd.data().toString();//保存用户密码
        //首先弹出输入框为用户指定属性集
        bool ok;
        QString attributeS = QInputDialog::getMultiLineText(this, "输入属性集S", QString("请为用户 %1 在全集U中指定属性集S(按顺序输入,属性之间用\",\"隔开)").arg(userName), "属性1,属性2,...,属性n", &ok);
        if (ok && !attributeS.isEmpty())
        {
            //判断输入的属性集是否在属性全集U里面
            if (isSvalid(attributeS))
            {
                QString SK = getUserSK(attributeS);//获取用户私钥SK
                insertUser(userName, userPasswd, attributeS, SK);
                deleteUserFromNewUser(userName);
            }
            else//输入的属性集非法，即不为属性全集U的子集合，将来可以做更多细分，如S限定数量为3、属性不能重复等
                QMessageBox::critical(this, "warn", "属性必须包含在属性全集U中！");
        }
    }
    else
        QMessageBox::critical(this, "warn", "invalid clicked");
}

void KDS::isEnableDeleteButton(const QItemSelection& selected, const QItemSelection& deselected)
{
    QItemSelectionModel* select = ui.tableView_5->selectionModel();
    if (select->selectedIndexes().isEmpty())//没有用户被选中
        ui.pushButton_2->setDisabled(true);
    else                                    //有用户被选中
        ui.pushButton_2->setDisabled(false);
        
}

void KDS::matchCookie(bool& ret, const QString& cookie)
{
    QSqlQuery query = QSqlQuery(database);//绑定已打开的database数据库对象
    query.exec(QString("select cookie from LoggedUser"));
    while (query.next())//遍历所有cookie
        if (cookie == query.value(0).toString())//cookie合法ret为true，否则默认(false)
            ret = true;
}

void KDS::getAPMatrix(QString& APMatrix, QStringList& APList, int MaxSize)
{
    Eigen::MatrixXd APM = Eigen::MatrixXd::Zero(MaxSize, MaxSize);//最终输出的访问策略矩阵
    Eigen::MatrixXd ANDM = Eigen::MatrixXd::Zero(MaxSize, MaxSize);//APList的每个元素对应的访问策略矩阵
    Eigen::MatrixXd m1 = Eigen::MatrixXd::Ones(1, 1);//单位矩阵[1]

    for (QStringList::iterator iterA = APList.begin(); iterA != APList.end(); iterA++)//遍历或
    {
        QStringList subS = (*iterA).split(",");
        //处理与
        ANDM = m1;//初始为[1]
        for (QStringList::iterator iterB = subS.begin(); iterB != subS.end() - 1; iterB++)//遍历与
            ANDM = M_AND(ANDM, m1);
        //std::cout << "ANDM = " << std::endl << ANDM << std::endl;
        //处理或
        if (iterA == APList.begin())     //第一次遍历时执行
            APM = ANDM;                 //初始化为第一个属性子集合的访问策略矩阵
        else                            //存在或结构并且第二次遍历时执行
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
    MUID = getRandomString(110);//MUID长度为110
}

Eigen::MatrixXd KDS::M_AND(Eigen::MatrixXd& m1, Eigen::MatrixXd& m2)//返回m1&m2对应的访问策略矩阵
{
    Eigen::MatrixXd m_and = Eigen::MatrixXd::Zero(m1.rows() + m2.rows(), m1.cols() + m2.cols());//与访问策略矩阵
    m_and.block(0, 0, m1.rows(), 1) = m1.col(0);
    m_and.block(0, 1, m1.rows(), 1) = m1.col(0);
    m_and.block(m1.rows(), 1, m2.rows(), 1) = m2.col(0);
    m_and.block(0, 2, m1.rows(), m1.cols() - 1) = m1.rightCols(m1.cols() - 1);
    m_and.block(m1.rows(), m1.cols() + 1, m2.rows(), m2.cols() - 1) = m2.rightCols(m2.cols() - 1);

    return m_and;
}

Eigen::MatrixXd KDS::M_OR(Eigen::MatrixXd& m1, Eigen::MatrixXd& m2)//返回m1|m2对应的访问策略矩阵
{
    Eigen::MatrixXd m_or = Eigen::MatrixXd::Zero(m1.rows() + m2.rows(), m1.cols() + m2.cols() - 1);//或访问策略矩阵
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
        QStringList metaItemList = (*iterRow).split(" ");//每行的元素组成列表
        if (iterRow == rowList.begin())//第一次循环指定destMatrix的大小，为其分配内存
        {
            int colNum = (int)metaItemList.size();
            destMatrix.resize(rowNum, colNum);//指定大小
        }
        for (QStringList::iterator iterCol = metaItemList.begin(); iterCol != metaItemList.end(); iterCol++)
            destMatrix(std::distance(rowList.begin(), iterRow), std::distance(metaItemList.begin(), iterCol)) = (*iterCol).toInt();
    }
    //std::cout << destMatrix << std::endl;
    return destMatrix;
}

void KDS::getOrderHx(QString& APQstr, QString& HXNUM)
{
    QSqlQuery query = QSqlQuery(database);//绑定已打开的database数据库对象
    query.exec(QString("select U from RawParam"));
    query.next();
    QStringList numHx;//存放访问策略位置的列表
    QStringList U = query.value(0).toString().split(",");
    QStringList subAttr = APQstr.split(";");//将访问策略按分号分开
    for (QStringList::iterator iter = subAttr.begin(); iter != subAttr.end(); iter++)
    {
        QStringList Attr = (*iter).split(",");//Attr中的元素为访问策略中的属性
        for (QStringList::iterator iterAttr = Attr.begin(); iterAttr != Attr.end(); iterAttr++)
            numHx.append(QString::number((quint32)U.indexOf(*iterAttr), 10));
    }

    HXNUM = numHx.join(",");
}

void KDS::isAbleDecry(QString cookie, QString MUID)
{
    QSqlQuery query = QSqlQuery(database);//绑定已打开的database数据库对象

    //查询cookie对应的用户名
    query.exec(QString("select name from LoggedUser where cookie = '%1'").arg(cookie));
    query.next();
    QString userName = query.value(0).toString();
    //查询用户名对应的属性集S
    query.exec(QString("select S from User where name = '%1'").arg(userName));
    query.next();
    QStringList userSList = query.value(0).toString().split(",");
    //查询MUID对应的访问策略
    query.exec(QString("select AccessPolicy from AccessPolicyMatrix where MUID = '%1'").arg(MUID));
    query.next();
    QStringList APList = query.value(0).toString().split(";");

    int firstRow = 0;//分别对应S满足访问策略的子集合在访问策略所有属性中的位置，两者之间连续
    int lastRow = 0;

    QStringList accessAPSetList;//满足访问策略的用户属性集中的一个子集列表
    for (QStringList::iterator iter = APList.begin(); iter != APList.end(); iter++)//遍历所有满足访问策略的子集合
    {
        QStringList subSet = (*iter).split(",");
        //qDebug() << "subSet = " << subSet;
        bool access = true;

        for (QStringList::iterator iterSubSet = subSet.begin(); iterSubSet != subSet.end(); iterSubSet++)//遍历每个子集合元素(属性)
        {
            if (!userSList.contains(*iterSubSet))//用户属性集不满足当前访问策略子集合
            {
                access = false;
                break;
            }
        }
        if (access == true)//上一个子集合就是用户属性集中满足访问策略的一个子集合
        {
            accessAPSetList = subSet;
            break;
        }
        firstRow += subSet.size();
    }

    if (accessAPSetList.isEmpty())//用户属性集不满足访问策略
    {
        Server.serverSocket->write(QString("0;您无权解密该文件!").toUtf8());
        return;
    }

    lastRow =  firstRow + accessAPSetList.size() - 1;

    QStringList KxOrderList;
    for (QStringList::iterator iter = accessAPSetList.begin(); iter != accessAPSetList.end(); iter++)//遍历用户满足访问策略的属性子集accessAPSetList
        KxOrderList.append(QString::number(userSList.indexOf(*iter)));

    QString subTAPMQstr = getSubTMatrix(MUID, firstRow, lastRow);//返回MUID对应的APM中的firstRow和lastRow之间(包括firstRow和lastRow)的子矩阵的转置矩阵

    QString retQstr = "1;" + KxOrderList.join(",") + ";" + subTAPMQstr + ";" + QString::number(firstRow);
    Server.serverSocket->write(retQstr.toUtf8());

}

QString KDS::getSubTMatrix(QString& MUID, int& firstRow, int& lastRow)
{
    QSqlQuery query = QSqlQuery(database);//绑定已打开的database数据库对象
    query.exec(QString("select APMatrix from AccessPolicyMatrix where MUID = '%1'").arg(MUID));
    query.next();
    QString APMQstr = query.value(0).toString();
    Eigen::MatrixXd APM = toMatrix(APMQstr);

    Eigen::Index col = APM.cols();
    Eigen::Index row = lastRow - firstRow + 1;
    Eigen::MatrixXd SubAPM(row, col);
    SubAPM = APM.block(firstRow, 0, row, col);

    Eigen::MatrixXd SubTAPM(col, row);//SubAPM的转置矩阵
    SubTAPM = SubAPM.transpose();

    return MatrixToQString(SubTAPM);
}