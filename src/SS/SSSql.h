#pragma once
#pragma execution_character_set("utf-8")//解决中文乱码

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QMessageBox>

//数据库相关操作
class SSSql : public QWidget
{
	Q_OBJECT

public:
	SSSql();
	~SSSql();

	QSqlDatabase database;//数据库实例

	void SSSql::insertMsg(QString& fileName, QString& Owner, QString& MsgDesc, QString& MUID, QString& Msg);//将加密者上传的密文写入数据库


private:
	bool connect();//连接数据库127.0.0.1:3306,用户名SS密码SS数据库SS,连接成功返回true

	void SSSql::initSql();//初始化数据库:创建数据库SS和表MsgStorage字段[uid,(FileName)文件名(最多20字符),(Owner)消息发送者,(MsgDesc)消息描述(最多500字符),MUID,(Msg)消息(密文内容)text格式存储于数据库]


};

