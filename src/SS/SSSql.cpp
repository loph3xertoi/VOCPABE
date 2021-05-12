#include "SSSql.h"


SSSql::SSSql()
{
    connect();
    initSql();
}

SSSql::~SSSql()
{
}

bool SSSql::connect()
{

    if (QSqlDatabase::contains("SS"))//判断SS连接是否存在并连接
    {
        database = QSqlDatabase::database("SS");
    }
    else //未连接则新建数据库连接
    {
        database = QSqlDatabase::addDatabase("QMYSQL", "SS");  //创建数据库连接，并为其命名SS
        database.setHostName("127.0.0.1");                      //连接数据库主机名，这里需要注意(若填的为"127.0.0.1", 出现不能连接，则改为localhost)
        database.setPort(3306);                                 //连接数据库端口号，与设置一致
        database.setUserName("SS");                            //数据库用户名，与设置一致
        database.setPassword("SS");                            //数据库密码，与设置一致
    }
    if (!database.open())
    {
        qDebug() << "fail to connect mysql:" << database.lastError().text();
        QMessageBox::critical(this, "数据库SS连接失败", QString("数据库SS连接失败:%1").arg(database.lastError().text()));
        return false;
    }
    qDebug() << "connect mysql success";

    return true;
}

void SSSql::initSql()
{
    QString queryString;

    //创建数据库
    database = QSqlDatabase::database("SS");
    queryString = "CREATE DATABASE IF NOT EXISTS SS";
    database.exec(queryString);
    if (database.lastError().isValid())
    {
        qDebug() << "Create database failed:" << database.lastError().text();
        return;
    }

    //表字段[uid, MUID, (MsgDesc)消息描述, (Owner)消息发送者, (Msg)消息(密文内容)]
    database.setDatabaseName("SS");
    if (!database.open())
    {
        qDebug() << "database open failed" << database.lastError().text();
        return;
    }

    //创建MsgStorage表
    queryString =
        "CREATE TABLE IF NOT EXISTS MsgStorage\
        (\
            uid int primary key not null auto_increment,\
            FileName varchar(20) not null,\
            Owner varchar(20) not null,\
            MsgDesc varchar(500) not null, \
            MUID varchar(110) not null unique, \
            Msg text not null\
        )";
    database.exec(queryString);
    if (database.lastError().isValid())
    {
        qDebug() << "MsgStorage table creat failed:" << database.lastError().text();
        return;
    }
    database.exec("alter table MsgStorage convert to character set utf8");//支持中文

    qDebug() << "init SSSql and tables success";

    return;
}

void SSSql::insertMsg(QString& fileName, QString& Owner, QString& MsgDesc, QString& MUID, QString& Msg)
{
    QSqlQuery query = QSqlQuery(database);//绑定已打开的database数据库对象
    query.exec(QString("insert into MsgStorage (FileName, Owner, MsgDesc, MUID, Msg) values('%1', '%2', '%3', '%4', '%5')").arg(fileName, Owner, MsgDesc, MUID, Msg));
    qDebug() << "insert error:" << query.lastError().text();
}
