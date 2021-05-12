#pragma once
#include <windows.h>
//#include <sstream>
#include <pbc.h>
#include <cryptlib.h>
#include <sha.h>
#include <filters.h>
#include <hex.h>
#include <Eigen/Dense>

#include <QDebug>
#include <QVector>

//��������PBC�����Ԫ�صĳ�ʼ���Ȳ���
class MyPBC
{
public:
	MyPBC();
	~MyPBC();

	pairing_t pairing;
	//ϵͳ����
	element_t g;//G1����Ԫ
	element_t e_g_g_alpha;//GT�е�Ԫ��e(g,g)^alpha
	element_t g_a;//G1�е�Ԫ��g^a
	element_t MSK;//G1�е�Ԫ��,g_alpha,ϵͳ��˽Կ,g^alpha

	QString U2hx(QString&);//����QString���͵�U������QString���͵�hx

	QString elementToQString(element_t);//element����תΪQString����

	QString SToSK(QString& S, QStringList& U, QStringList& hxList);//�����û����Լ���hx�б�����û�˽ԿSK

private:
	size_t MAX_ATTRIBUTE_COUNT = 36;//U�������36������
	//a���Ͷ�
	const char* aTypeStr = "type a\
		q 8780710799663312522437781984754049815806883199414208211028653399266475630880222957078625179422662221423155858769582317459277713367317481324925129998224791\
		h 12016012264891146079388821366740534204802954401251311822919615131047207289359704531102844802183906537786776\
		r 730750818665451621361119245571504901405976559617\
		exp2 159\
		exp1 107\
		sign1 1\
		sign0 1";

	void initRandom();//��ʼ������element_t��pairing

	QString getKxQstr(QString& S, QStringList& U, QStringList& hxList, element_t t, element_t z_invert);//�����û����Լ�S������ȫ��U��hxList�����G1Ԫ��t��ZrԪ��z����Ԫ,�����ӦKx��ɵ��ַ���
};

