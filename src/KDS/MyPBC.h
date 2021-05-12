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

//用来处理PBC库相关元素的初始化等操作
class MyPBC
{
public:
	MyPBC();
	~MyPBC();

	pairing_t pairing;
	//系统参数
	element_t g;//G1生成元
	element_t e_g_g_alpha;//GT中的元素e(g,g)^alpha
	element_t g_a;//G1中的元素g^a
	element_t MSK;//G1中的元素,g_alpha,系统主私钥,g^alpha

	QString U2hx(QString&);//输入QString类型的U，返回QString类型的hx

	QString elementToQString(element_t);//element类型转为QString类型

	QString SToSK(QString& S, QStringList& U, QStringList& hxList);//输入用户属性集和hx列表输出用户私钥SK

private:
	size_t MAX_ATTRIBUTE_COUNT = 36;//U中最多存放36个属性
	//a类型对
	const char* aTypeStr = "type a\
		q 8780710799663312522437781984754049815806883199414208211028653399266475630880222957078625179422662221423155858769582317459277713367317481324925129998224791\
		h 12016012264891146079388821366740534204802954401251311822919615131047207289359704531102844802183906537786776\
		r 730750818665451621361119245571504901405976559617\
		exp2 159\
		exp1 107\
		sign1 1\
		sign0 1";

	void initRandom();//初始化上述element_t和pairing

	QString getKxQstr(QString& S, QStringList& U, QStringList& hxList, element_t t, element_t z_invert);//输入用户属性集S、属性全集U、hxList、随机G1元素t、Zr元素z的逆元,输出对应Kx组成的字符串
};

