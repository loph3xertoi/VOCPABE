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
	bool ret = false;//��ѯ��־λ��false����δ��ѯ����true�����Ѳ�ѯ����
	//�ж��û��Ƿ����User���У����Ƿ�KDS����Ա�Ѿ�ͬ���û���ע������
	emit querySignal(ret, "User", "name", regLoginQstr.at(1));
	if (ret == true)										//�û��Ѿ���User���У�����Ҫע�ᣬֱ�ӿ��Ե�¼
		return QString("1,�û����Ѿ����ڣ���ֱ�ӵ�¼��");	//1������ɫ��ʶ��������Ӣ�Ķ��ŷָ�����ʾ��Ϣ֮�������Ķ��Ÿ�����

	//�ж��û��Ƿ���NewUser���У����ڼ���ʾKDS����Ա��δ����ȷ��
	emit querySignal(ret, "NewUser", "name", regLoginQstr.at(1));
	if (ret == true)
		return QString("2,���Ѿ�ע����ˣ���ȴ�KDS����Աȷ�ϣ�");
	else//��ʾ���û�Ϊ���й�ע�ᣬ������ӵ�NewUser���У���ˢ�����û�չʾ���档
		emit insertSignal("NewUser", regLoginQstr.at(1), regLoginQstr.at(2));

	return QString("3,����ע������KDS�������Ѿ��յ�����ȴ�KDS����Աȷ�ϣ�");
}

QString RegisterLogin::loginProcess(QStringList& regLoginQstr)
{
	bool ret = false;
	emit querySignal(ret, "User", "name", regLoginQstr.at(0));
	if (ret == false)//�û�����User���У���ʾ��Ҫע��
		return QString("4,����δע�ᣬ��ע����¼��");

	emit isMatchSignal(ret, regLoginQstr.at(0), regLoginQstr.at(1));//��User���в�ѯ�û����������Ƿ�ƥ��

	if (ret == false)//�û��������벻ƥ��
		return QString("5,����������������룡");
	else	
		return QString("6,���ڵ�¼...");
}

QString RegisterLogin::processAP(QStringList& recvMsgList)//�����ʽ[AP,���ʲ�����ȡ��ʽ,cookie],�����ʽ[���ʲ��Ծ���;MUID;HXNUM](HXNUM����ÿ�����ʲ��Ե�������hx�ж�Ӧ��λ�ã����Ÿ���)
{
	if (recvMsgList.size() <= 2)//û�з��ʲ���
		return QString("�Ƿ�����");

	bool ret = false;
	emit isValidCookie(ret, recvMsgList.last());//cookie�Ϸ���retΪtrue������Ϊfalse
	if (!ret)//cookie����LoggedUser��¼�б���
		return QString("cookie�Ƿ��������µ�¼��");

	//��ȡ���ʲ��Դ���APList
	int MaxSize;
	QString HXNUM;//��ŷ��ʲ����е�������U�е�λ��
	QStringList APList = recvMsgList.mid(1, recvMsgList.size() - 2);//ȥ��AP��cookie
	MaxSize = (int)APList.size();
	QString APQstr = APList.join(",");//�ϲ��ɼ����������ԭʼ���ʲ��Ե���ʽ(��ȡ��ʽ)
	APList.clear();
	APList = APQstr.split(";");//�б���ÿ��Ԫ��Ϊһ��������ʲ��Ե����Լ�
	MaxSize += (int)APList.size();//�ֺ�����
	--MaxSize;
	QString APMatrix, MUID;//�ֱ��ŷ��ʲ��Ծ����MUID
	emit getAPMatrixSignal(APMatrix, APList, MaxSize);//���ݷ��ʲ����б�APList���ɷ��ʲ��Ծ���תΪQString����APMatrix
	emit getMUIDSignal(MUID, APList);//����APList����MUID���������MUID��
	emit insertAPMSignal(APQstr, APMatrix, MUID);//�����ʲ��ԡ����ʲ��Ծ���MUID����AccessPolicyMatrix����
	emit getOrderHxSignal(APQstr, HXNUM);//�����ʲ������Զ�Ӧ��hx����Ӧ˳�����HXNUM[1,2,3]
	return APMatrix + ";" + MUID + ";" + HXNUM;
}

