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

    if (QSqlDatabase::contains("SS"))//�ж�SS�����Ƿ���ڲ�����
    {
        database = QSqlDatabase::database("SS");
    }
    else //δ�������½����ݿ�����
    {
        database = QSqlDatabase::addDatabase("QMYSQL", "SS");  //�������ݿ����ӣ���Ϊ������SS
        database.setHostName("127.0.0.1");                      //�������ݿ���������������Ҫע��(�����Ϊ"127.0.0.1", ���ֲ������ӣ����Ϊlocalhost)
        database.setPort(3306);                                 //�������ݿ�˿ںţ�������һ��
        database.setUserName("SS");                            //���ݿ��û�����������һ��
        database.setPassword("SS");                            //���ݿ����룬������һ��
    }
    if (!database.open())
    {
        qDebug() << "fail to connect mysql:" << database.lastError().text();
        QMessageBox::critical(this, "���ݿ�SS����ʧ��", QString("���ݿ�SS����ʧ��:%1").arg(database.lastError().text()));
        return false;
    }
    qDebug() << "connect mysql success";

    return true;
}

void SSSql::initSql()
{
    QString queryString;

    //�������ݿ�
    database = QSqlDatabase::database("SS");
    queryString = "CREATE DATABASE IF NOT EXISTS SS";
    database.exec(queryString);
    if (database.lastError().isValid())
    {
        qDebug() << "Create database failed:" << database.lastError().text();
        return;
    }

    //���ֶ�[uid, MUID, (MsgDesc)��Ϣ����, (Owner)��Ϣ������, (Msg)��Ϣ(��������)]
    database.setDatabaseName("SS");
    if (!database.open())
    {
        qDebug() << "database open failed" << database.lastError().text();
        return;
    }

    //����MsgStorage��
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
    database.exec("alter table MsgStorage convert to character set utf8");//֧������

    qDebug() << "init SSSql and tables success";

    return;
}

void SSSql::insertMsg(QString& fileName, QString& Owner, QString& MsgDesc, QString& MUID, QString& Msg)
{
    QSqlQuery query = QSqlQuery(database);//���Ѵ򿪵�database���ݿ����
    query.exec(QString("insert into MsgStorage (FileName, Owner, MsgDesc, MUID, Msg) values('%1', '%2', '%3', '%4', '%5')").arg(fileName, Owner, MsgDesc, MUID, Msg));
    qDebug() << "insert error:" << query.lastError().text();
}
