#include "RegisterLogin.h"
#include "KDS.h"
extern KDS* quoteKDS;

RegisterLogin::RegisterLogin()
{
	//qDebug() << quoteKDS;
	connect(this, &RegisterLogin::querySignal, quoteKDS, &KDS::isExisted);
	connect(this, &RegisterLogin::insertSignal, quoteKDS, &KDS::insertNewUser);
	connect(this, &RegisterLogin::isMatchSignal, quoteKDS, &KDS::matchNamePasswd);
	connect(this, &RegisterLogin::isValidCookie, quoteKDS, &KDS::matchCookie);
	connect(this, &RegisterLogin::getAPMatrixSignal, quoteKDS, &KDS::getAPMatrix);
	connect(this, &RegisterLogin::getMUIDSignal, quoteKDS, &KDS::getMUID);
	connect(this, &RegisterLogin::insertAPMSignal, quoteKDS, &KDS::insertAPM);
	connect(this, &RegisterLogin::getOrderHxSignal, quoteKDS, &KDS::getOrderHx);

}

RegisterLogin::~RegisterLogin()
{

}

QString RegisterLogin::regProcess(QStringList& regLoginQstr)
{
	//qDebug() << "query result = " << isExisted("NewUser", "name", "daw");
	//qDebug() << "emit querySignal";
	bool ret = false;//查询标志位，false代表未查询到，true代表已查询到。
	//判断用户是否存在User表中，即是否KDS管理员已经同意用户的注册请求
	emit querySignal(ret, "User", "name", regLoginQstr.at(1));
	if (ret == true)										//用户已经在User表中，不需要注册，直接可以登录
		return QString("1,用户名已经存在，请直接登录！");	//1代表颜色标识，后面用英文逗号分隔，提示消息之间用中文逗号隔开。

	//判断用户是否在NewUser表中，存在即表示KDS管理员还未进行确认
	emit querySignal(ret, "NewUser", "name", regLoginQstr.at(1));
	if (ret == true)
		return QString("2,您已经注册过了，请等待KDS管理员确认！");
	else//表示此用户为进行过注册，将其添加到NewUser表中，并刷新新用户展示界面。
		emit insertSignal("NewUser", regLoginQstr.at(1), regLoginQstr.at(2));

	return QString("3,您的注册请求KDS服务器已经收到，请等待KDS管理员确认！");
}

QString RegisterLogin::loginProcess(QStringList& regLoginQstr)
{
	bool ret = false;
	emit querySignal(ret, "User", "name", regLoginQstr.at(0));
	if (ret == false)//用户不在User表中，提示需要注册
		return QString("4,您还未注册，请注册后登录！");

	emit isMatchSignal(ret, regLoginQstr.at(0), regLoginQstr.at(1));//在User表中查询用户名和密码是否匹配

	if (ret == false)//用户名和密码不匹配
		return QString("5,密码错误，请重新输入！");
	else	
		return QString("6,正在登录...");
}

QString RegisterLogin::processAP(QStringList& recvMsgList)//输入格式[AP,访问策略析取范式,cookie],输出格式[访问策略矩阵;MUID;HXNUM](HXNUM代表每个访问策略的属性在hx中对应的位置，逗号隔开)
{
	if (recvMsgList.size() <= 2)//没有访问策略
		return QString("非法输入");

	bool ret = false;
	emit isValidCookie(ret, recvMsgList.last());//cookie合法，ret为true，否则为false
	if (!ret)//cookie不在LoggedUser登录列表中
		return QString("cookie非法，请重新登录！");

	//提取访问策略存入APList
	int MaxSize;
	QString HXNUM;//存放访问策略中的属性在U中的位置
	QStringList APList = recvMsgList.mid(1, recvMsgList.size() - 2);//去掉AP和cookie
	MaxSize = (int)APList.size();
	QString APQstr = APList.join(",");//合并成加密者输入的原始访问策略的形式(析取范式)
	APList.clear();
	APList = APQstr.split(";");//列表中每个元素为一个满足访问策略的属性集
	MaxSize += (int)APList.size();//分号数量
	--MaxSize;
	QString APMatrix, MUID;//分别存放访问策略矩阵和MUID
	emit getAPMatrixSignal(APMatrix, APList, MaxSize);//根据访问策略列表APList生成访问策略矩阵并转为QString存入APMatrix
	emit getMUIDSignal(MUID, APList);//根据APList生成MUID存入给定的MUID中
	emit insertAPMSignal(APQstr, APMatrix, MUID);//将访问策略、访问策略矩阵、MUID插入AccessPolicyMatrix表中
	emit getOrderHxSignal(APQstr, HXNUM);//将访问策略属性对应到hx，对应顺序存入HXNUM[1,2,3]
	return APMatrix + ";" + MUID + ";" + HXNUM;
}

