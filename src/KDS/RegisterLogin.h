#pragma once
#include <QStringList>
#include <QDebug>
//#include "KDS.h"
//处理用户的注册与登录

class RegisterLogin : public QObject
{
	Q_OBJECT

public:
	RegisterLogin();
	~RegisterLogin();

	QString regProcess(QStringList&);//处理用户注册请求,返回提示信息

	QString loginProcess(QStringList&);//处理用户登录请求,返回提示信息

	QString processAP(QStringList&);//处理加密方发送的访问策略AP，返回[访问策略矩阵APMatrix;MUID]或错误信息

signals:
	//定义向KDS数据库查询的信号，ret接收查询结果,存在返回true，不存在返回false
	void querySignal(bool& ret, const QString& tableToQuery, const QString& field, const QString& queryQstr);
	//向tableToQuery表插入记录:name用户名，passwd密码
	void insertSignal(const QString& tableToQuery, const QString& name, const QString& passwd);
	//向User表查询用户名和密码是否匹配
	void isMatchSignal(bool& ret, const QString& name, const QString& passwd);
	//查询cookie是否在LoggedUser表中
	void isValidCookie(bool& ret, const QString& cookie);
	//根据访问策略列表APList生成访问策略矩阵并转为QString存入APMatrix
	void getAPMatrixSignal(QString& APMatrix, QStringList& APList, int& MaxSize);
	//根据APList生成MUID存入给定的MUID中
	void getMUIDSignal(QString& MUID, QStringList& APList);
	//将访问策略、访问策略矩阵、MUID写入AccessPolicyMatrix表中
	void insertAPMSignal(QString& AccessPolicy, QString& APMatrix, QString& MUID);
	//将访问策略属性对应到hx，对应顺序存入HXNUM[1,2,3]，输入原始QString访问策略，HXNUM为QString类型
	void getOrderHxSignal(QString& APQstr,QString& HXNUM);
};
