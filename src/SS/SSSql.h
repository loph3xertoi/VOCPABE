#pragma once
#pragma execution_character_set("utf-8")//�����������

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QMessageBox>

//���ݿ���ز���
class SSSql : public QWidget
{
	Q_OBJECT

public:
	SSSql();
	~SSSql();

	QSqlDatabase database;//���ݿ�ʵ��

	void SSSql::insertMsg(QString& fileName, QString& Owner, QString& MsgDesc, QString& MUID, QString& Msg);//���������ϴ�������д�����ݿ�


private:
	bool connect();//�������ݿ�127.0.0.1:3306,�û���SS����SS���ݿ�SS,���ӳɹ�����true

	void SSSql::initSql();//��ʼ�����ݿ�:�������ݿ�SS�ͱ�MsgStorage�ֶ�[uid,(FileName)�ļ���(���20�ַ�),(Owner)��Ϣ������,(MsgDesc)��Ϣ����(���500�ַ�),MUID,(Msg)��Ϣ(��������)text��ʽ�洢�����ݿ�]


};

