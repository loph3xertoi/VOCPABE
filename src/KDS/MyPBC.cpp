#include "MyPBC.h"
#include <QMessageBox>
MyPBC::MyPBC()
{
	initRandom();//��ʼ��ʵ��
}

MyPBC::~MyPBC()
{
	//�ͷ�element_t��Ԫ��
	element_clear(g);
	element_clear(e_g_g_alpha);
	element_clear(g_a);
	element_clear(MSK);
	//�ͷ�pairing
	pairing_clear(pairing);
}

QString MyPBC::U2hx(QString& U)
{
	QStringList attributeQStringListU;//�洢QString���͵�����
	QStringList hxQStringList;//�洢h��������

	hxQStringList.clear();
	attributeQStringListU.clear();
	attributeQStringListU = U.split(',');
	//std::cout << std::endl << std::endl;
	//qDebug() << "attributeQStringListU:" << attributeQStringListU;
	//qDebug() << "attributeQStringListU.count():" << attributeQStringListU.count();
	
	//����attributeQStringListU����Ԫ�أ�ӳ�䵽G1��
	std::string attrHash;
	CryptoPP::SHA256 sha256;

	element_t attributePoint;//attributePointΪ���Զ�Ӧ��G1�ϵ�Ԫ��
	element_init_G1(attributePoint, pairing);
	QString strAttribute;//�洢��������
	QStringListIterator strIterator(attributeQStringListU);
	
	//qDebug() << "next:" << strIterator.next();
	//qDebug() << "new string:" << attributeQStringListU.join(",");
	char* attrPointCharStr = (char*)calloc(320, 1);//���䲢��ʼ���ڴ�
	while(strIterator.hasNext())
	{
		strAttribute = strIterator.next();
		CryptoPP::StringSource ss(//��������sha256ժҪ GbkToUtf8((*iter).c_str())
			strAttribute.toStdString(),
			true,
			new CryptoPP::HashFilter(sha256,
				new CryptoPP::HexEncoder(
					new CryptoPP::StringSink(attrHash)
				)
			)
		);
		
		element_from_hash(attributePoint, (void*)attrHash.c_str(), (int)attrHash.length());//16���ƹ�ϣ��Ӧ��G1�еĵ�
		element_snprint(attrPointCharStr, 320, attributePoint);//��G1�еĵ��Ӧ��[x,y]��ʽ���ַ���h
		
		hxQStringList << QString(attrPointCharStr);//��h��������
		attrHash = "";//���attrHash�ַ����������֮��Ĺ�ϣֵ����һ��
	}
	
	element_clear(attributePoint);//�ͷ�element_t

	return hxQStringList.join(";");
}

QString MyPBC::elementToQString(element_t point)
{
	char* ourQStr = (char*)calloc(350, 1);//��ʼ��
	element_snprint(ourQStr, 350, point);//��pointתΪchar*����ourQStr
	return QString(ourQStr);
}

//SK�ṹ:z;K;L;Kx;����z����Zr,K=(MSK*(g^(a*t)))^(1/z),L=g^t^(1/z),Kx=hx^t^(1/z),Kx��������S����������һ��
QString MyPBC::SToSK(QString& S, QStringList& U, QStringList& hxList)
{
	QString SK;//���ص�˽Կ
	//�����������z����������K����
	element_t z;
	element_init_Zr(z, pairing);
	element_random(z);

	SK = elementToQString(z) + ";";

	element_t z_invert;//z����Ԫ
	element_init_Zr(z_invert, pairing);
	element_invert(z_invert, z);

	//���ѡ��t����Zr
	element_t t;
	element_init_Zr(t, pairing);
	element_random(t);

	//����g^(at),��(g^a)^t
	element_t g_at;
	element_init_G1(g_at, pairing);
	element_pow_zn(g_at, g_a, t);

	//����MSK*g_at
	element_t MSK_mul_g_at;
	element_init_G1(MSK_mul_g_at, pairing);
	element_mul(MSK_mul_g_at, MSK, g_at);

	//����K
	element_t K;
	element_init_G1(K, pairing);
	element_pow_zn(K, MSK_mul_g_at, z_invert);

	SK += elementToQString(K) + ";";

	//����L=g^t
	element_t L;
	element_init_G1(L, pairing);
	element_pow_zn(L, g, t);
	element_pow_zn(L, L, z_invert);

	SK += elementToQString(L) + ";";

	//����Kx��S��ÿ�����Զ���Ӧһ��Kx
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
	pairing_init_set_buf(pairing, aTypeStr, strnlen_s(aTypeStr, 400));//Ϊpairingָ������
	element_init_G1(g, pairing);//ָ��gΪG1�е�Ԫ��
	element_random(g);//���ָ��g��ֵ

	element_t a, alpha;//Zr��Ԫ��
	element_init_Zr(a, pairing);//ָ��aΪZr�е�Ԫ��
	element_init_Zr(alpha, pairing);//ָ��alphaΪZr�е�Ԫ��
	element_random(a);//���ָ��a��ֵ
	element_random(alpha);//���ָ��alpha��ֵ

	element_t e_g_g;//e(g,g),ΪGT�е�Ԫ��
	element_init_GT(e_g_g, pairing);//ָ��e_g_gΪGT�е�Ԫ��
	pairing_apply(e_g_g, g, g, pairing);//����e(g,g)����ֵ��e_g_g

	element_init_GT(e_g_g_alpha, pairing);//��ʼ��e_g_g_alphaΪGT�е�Ԫ��
	element_pow_zn(e_g_g_alpha, e_g_g, alpha);//����e_g_g_alpha

	element_init_G1(g_a, pairing);//��ʼ��g_aΪG1�е�Ԫ��
	element_pow_zn(g_a, g, a);//����g_a

	element_init_G1(MSK, pairing);//��ʼ��MSKΪG1�е�Ԫ��
	element_pow_zn(MSK, g, alpha);//������˽ԿMSK

	//�ͷ��ڴ�
	element_clear(a);
	element_clear(alpha);
	element_clear(e_g_g);
}

QString MyPBC::getKxQstr(QString& S, QStringList& U, QStringList& hxList, element_t t, element_t z_invert)
{
	QStringList KxList;//���S������Kx
	QStringList hxSList;
	QStringList SList = S.split(",");
	//�����Զ�Ӧ��hxд��hxSList
	for (QStringList::iterator iter = SList.begin(); iter != SList.end(); iter++)
		hxSList.append(hxList.at(U.indexOf(*iter)));
	
	//��ÿ�����Լ����Ӧ��˽Կ����Kx
	element_t hx;//�洢S��ÿ�����Զ�Ӧ��hx
	element_t Kx;//�洢hx^t��ÿ��˽Կ����
	element_init_G1(hx, pairing);
	element_init_G1(Kx, pairing);

	//��hxSList����������Kx
	for (QStringList::iterator iter = hxSList.begin(); iter != hxSList.end(); iter++)
	{
		//��QString��ʽ��G1Ԫ��ֵ��ԭΪelement_t����
		element_set_str(hx, (*iter).toStdString().c_str(), 10);
		//����Kx
		element_pow_zn(Kx, hx, t);
		element_pow_zn(Kx, Kx, z_invert);
		//KxתΪQString����KxList
		KxList.append(elementToQString(Kx));
	}
	//qDebug() << "\n\nKxList = " << KxList;

	element_clear(hx);
	element_clear(Kx);

	return KxList.join(",");
}
