#include "MyPBC.h"
#include <QMessageBox>
MyPBC::MyPBC()
{
	initRandom();//初始化实例
}

MyPBC::~MyPBC()
{
	//释放element_t类元素
	element_clear(g);
	element_clear(e_g_g_alpha);
	element_clear(g_a);
	element_clear(MSK);
	//释放pairing
	pairing_clear(pairing);
}

QString MyPBC::U2hx(QString& U)
{
	QStringList attributeQStringListU;//存储QString类型的属性
	QStringList hxQStringList;//存储h到此链表

	hxQStringList.clear();
	attributeQStringListU.clear();
	attributeQStringListU = U.split(',');
	//std::cout << std::endl << std::endl;
	//qDebug() << "attributeQStringListU:" << attributeQStringListU;
	//qDebug() << "attributeQStringListU.count():" << attributeQStringListU.count();
	
	//遍历attributeQStringListU所有元素，映射到G1中
	std::string attrHash;
	CryptoPP::SHA256 sha256;

	element_t attributePoint;//attributePoint为属性对应的G1上的元素
	element_init_G1(attributePoint, pairing);
	QString strAttribute;//存储单个属性
	QStringListIterator strIterator(attributeQStringListU);
	
	//qDebug() << "next:" << strIterator.next();
	//qDebug() << "new string:" << attributeQStringListU.join(",");
	char* attrPointCharStr = (char*)calloc(320, 1);//分配并初始化内存
	while(strIterator.hasNext())
	{
		strAttribute = strIterator.next();
		CryptoPP::StringSource ss(//将属性做sha256摘要 GbkToUtf8((*iter).c_str())
			strAttribute.toStdString(),
			true,
			new CryptoPP::HashFilter(sha256,
				new CryptoPP::HexEncoder(
					new CryptoPP::StringSink(attrHash)
				)
			)
		);
		
		element_from_hash(attributePoint, (void*)attrHash.c_str(), (int)attrHash.length());//16进制哈希对应到G1中的点
		element_snprint(attrPointCharStr, 320, attributePoint);//将G1中的点对应到[x,y]形式的字符串h
		
		hxQStringList << QString(attrPointCharStr);//将h存入链表
		attrHash = "";//清空attrHash字符串，避免和之后的哈希值连到一起
	}
	
	element_clear(attributePoint);//释放element_t

	return hxQStringList.join(";");
}

QString MyPBC::elementToQString(element_t point)
{
	char* ourQStr = (char*)calloc(350, 1);//初始化
	element_snprint(ourQStr, 350, point);//将point转为char*存入ourQStr
	return QString(ourQStr);
}

//SK结构:z;K;L;Kx;其中z属于Zr,K=(MSK*(g^(a*t)))^(1/z),L=g^t^(1/z),Kx=hx^t^(1/z),Kx的数量和S的属性数量一致
QString MyPBC::SToSK(QString& S, QStringList& U, QStringList& hxList)
{
	QString SK;//返回的私钥
	//首先生成随机z，用来隐藏K参数
	element_t z;
	element_init_Zr(z, pairing);
	element_random(z);

	SK = elementToQString(z) + ";";

	element_t z_invert;//z的逆元
	element_init_Zr(z_invert, pairing);
	element_invert(z_invert, z);

	//随机选择t属于Zr
	element_t t;
	element_init_Zr(t, pairing);
	element_random(t);

	//计算g^(at),即(g^a)^t
	element_t g_at;
	element_init_G1(g_at, pairing);
	element_pow_zn(g_at, g_a, t);

	//计算MSK*g_at
	element_t MSK_mul_g_at;
	element_init_G1(MSK_mul_g_at, pairing);
	element_mul(MSK_mul_g_at, MSK, g_at);

	//计算K
	element_t K;
	element_init_G1(K, pairing);
	element_pow_zn(K, MSK_mul_g_at, z_invert);

	SK += elementToQString(K) + ";";

	//计算L=g^t
	element_t L;
	element_init_G1(L, pairing);
	element_pow_zn(L, g, t);
	element_pow_zn(L, L, z_invert);

	SK += elementToQString(L) + ";";

	//计算Kx，S中每个属性都对应一个Kx
	QString allKxQstr = getKxQstr(S, U, hxList, t, z_invert);
	
	SK += allKxQstr;
	//qDebug() << "SK = " << SK;
	element_clear(z);
	element_clear(z_invert);
	element_clear(t);
	element_clear(g_at);
	element_clear(MSK_mul_g_at);
	element_clear(K);
	element_clear(L);

	return SK;
}

void MyPBC::initRandom()
{
	pairing_init_set_buf(pairing, aTypeStr, strnlen_s(aTypeStr, 400));//为pairing指定类型
	element_init_G1(g, pairing);//指定g为G1中的元素
	element_random(g);//随机指定g的值

	element_t a, alpha;//Zr中元素
	element_init_Zr(a, pairing);//指定a为Zr中的元素
	element_init_Zr(alpha, pairing);//指定alpha为Zr中的元素
	element_random(a);//随机指定a的值
	element_random(alpha);//随机指定alpha的值

	element_t e_g_g;//e(g,g),为GT中的元素
	element_init_GT(e_g_g, pairing);//指定e_g_g为GT中的元素
	pairing_apply(e_g_g, g, g, pairing);//计算e(g,g)并赋值给e_g_g

	element_init_GT(e_g_g_alpha, pairing);//初始化e_g_g_alpha为GT中的元素
	element_pow_zn(e_g_g_alpha, e_g_g, alpha);//计算e_g_g_alpha

	element_init_G1(g_a, pairing);//初始化g_a为G1中的元素
	element_pow_zn(g_a, g, a);//计算g_a

	element_init_G1(MSK, pairing);//初始化MSK为G1中的元素
	element_pow_zn(MSK, g, alpha);//计算主私钥MSK

	//释放内存
	element_clear(a);
	element_clear(alpha);
	element_clear(e_g_g);
}

QString MyPBC::getKxQstr(QString& S, QStringList& U, QStringList& hxList, element_t t, element_t z_invert)
{
	QStringList KxList;//存放S的所有Kx
	QStringList hxSList;
	QStringList SList = S.split(",");
	//将属性对应的hx写入hxSList
	for (QStringList::iterator iter = SList.begin(); iter != SList.end(); iter++)
		hxSList.append(hxList.at(U.indexOf(*iter)));
	
	//对每个属性计算对应的私钥分量Kx
	element_t hx;//存储S中每个属性对应的hx
	element_t Kx;//存储hx^t即每个私钥分量
	element_init_G1(hx, pairing);
	element_init_G1(Kx, pairing);

	//对hxSList遍历，计算Kx
	for (QStringList::iterator iter = hxSList.begin(); iter != hxSList.end(); iter++)
	{
		//将QString形式的G1元素值还原为element_t类型
		element_set_str(hx, (*iter).toStdString().c_str(), 10);
		//计算Kx
		element_pow_zn(Kx, hx, t);
		element_pow_zn(Kx, Kx, z_invert);
		//Kx转为QString存入KxList
		KxList.append(elementToQString(Kx));
	}
	//qDebug() << "\n\nKxList = " << KxList;

	element_clear(hx);
	element_clear(Kx);

	return KxList.join(",");
}
