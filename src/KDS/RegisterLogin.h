#pragma once
#include <QStringList>
#include <QDebug>
//#include "KDS.h"
//�����û���ע�����¼

class RegisterLogin : public QObject
{
	Q_OBJECT

public:
	RegisterLogin();
	~RegisterLogin();

	QString regProcess(QStringList&);//�����û�ע������,������ʾ��Ϣ

	QString loginProcess(QStringList&);//�����û���¼����,������ʾ��Ϣ

	QString processAP(QStringList&);//������ܷ����͵ķ��ʲ���AP������[���ʲ��Ծ���APMatrix;MUID]�������Ϣ

signals:
	//������KDS���ݿ��ѯ���źţ�ret���ղ�ѯ���,���ڷ���true�������ڷ���false
	void querySignal(bool& ret, const QString& tableToQuery, const QString& field, const QString& queryQstr);
	//��tableToQuery������¼:name�û�����passwd����
	void insertSignal(const QString& tableToQuery, const QString& name, const QString& passwd);
	//��User���ѯ�û����������Ƿ�ƥ��
	void isMatchSignal(bool& ret, const QString& name, const QString& passwd);
	//��ѯcookie�Ƿ���LoggedUser����
	void isValidCookie(bool& ret, const QString& cookie);
	//���ݷ��ʲ����б�APList���ɷ��ʲ��Ծ���תΪQString����APMatrix
	void getAPMatrixSignal(QString& APMatrix, QStringList& APList, int& MaxSize);
	//����APList����MUID���������MUID��
	void getMUIDSignal(QString& MUID, QStringList& APList);
	//�����ʲ��ԡ����ʲ��Ծ���MUIDд��AccessPolicyMatrix����
	void insertAPMSignal(QString& AccessPolicy, QString& APMatrix, QString& MUID);
	//�����ʲ������Զ�Ӧ��hx����Ӧ˳�����HXNUM[1,2,3]������ԭʼQString���ʲ��ԣ�HXNUMΪQString����
	void getOrderHxSignal(QString& APQstr,QString& HXNUM);
};
