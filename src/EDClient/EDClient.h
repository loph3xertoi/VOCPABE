#pragma once
#pragma execution_character_set("utf-8")//�����������

#include <QtWidgets/QWidget>
#include "ui_EDClient.h"
#include <QMessageBox>
//#include <QDesktopServices>
#include <QFileDialog>

#include <pbc.h>
#include <cryptlib.h>
#include <sha.h>
#include <filters.h>
#include <hex.h>
#include <Eigen/Dense>

//����������
class EDClient : public QWidget
{
    Q_OBJECT

public:
    EDClient(QWidget *parent = Q_NULLPTR);
    ~EDClient();

private:
    Ui::EDClientClass ui;
    pairing_t pairing;//a���Ͷ�
    QString fileName;//���Ҫ������Ϣ���ļ���
    QString fileContent;//���Ҫ������Ϣ������
    QStringList PK;//�洢ϵͳ����PK[g,e(g,g)^alpha,g^a,hx]
    QStringList SK;//�洢�û�˽ԿSK[z,K((g^alpha)*g^(a*t*(1/z))),L(g^t),Kx(hx^t)],�û�S��ÿ�����Զ�Ӧһ��Kx
    QString sQstr;//�洢����ʱ�Ĺ������s
    QString rQstr;//�洢����ʱGT�е�Ԫ��r

    QStringList hxOrderList;//�洢���ʲ����е����Զ�Ӧ��hx��λ��
    QStringList blindPairIndex4;//��Ӧ�洢�ĸ�ä���Ե�ָ��
    QStringList blindPairValue4;//�洢blindPairIndex4�ж�Ӧָ��������ԪgΪ����ʱ��ֵ
    bool vSignal = false;
    QString cipher;//�洢����ʱ��SS���ص�base64���ܵ��ַ���[C;C_1;C_2;daw;C1;D1;...;Ci;Di]
    QString MUID;//���Ҫ�����ļ���MUID

    const char* aTypeStr = "type a\
		q 8780710799663312522437781984754049815806883199414208211028653399266475630880222957078625179422662221423155858769582317459277713367317481324925129998224791\
		h 12016012264891146079388821366740534204802954401251311822919615131047207289359704531102844802183906537786776\
		r 730750818665451621361119245571504901405976559617\
		exp2 159\
		exp1 107\
		sign1 1\
		sign0 1";

    void closeEvent(QCloseEvent* close);

    void clearLogged();//�����˳����KDS�������ϵ�LoggedUser��

    QString encryAndVerify(Eigen::MatrixXd& APMatrix);//������ʲ��Ծ���APMatrix,�����ѡ��Ϣtxt�������������֤,����CT

    QStringList computeThreeOfCT();//����C��C_1��C_2,���������÷ֺŸ�����QString

    void uploadToSS(QString& CTMUID);//��CT;�ļ�����;MUID��ʽ��QString�ϴ����洢������SS

    QString getAPMatrixMUID(QString& accessPolicy);//������ʲ���,��ʽΪ����ֵ����ȡ��ʽ��","��Ӧ��";"��Ӧ��,���ط��ʲ��Ծ���;MUID;HXNUM��ʾ�˷��ʲ��ԣ�һ��MUIDֻ��Ӧһ�����ʲ��ԣ�����һ�����ʲ��Կ��Զ�Ӧ���MUID��ͨ������ʱͬһ�����ʲ��Զ�Ӧ��ͬMUID�����Զ������ط��ʲ���,HXNUM��ʾ���ʲ����е����Զ�Ӧ��U�е�λ��

    QString computeCiDi(Eigen::MatrixXd& APMatrix);//���ݷ��ʲ��Ծ������ES����CiDi

    Eigen::MatrixXd toMatrix(QString);//��[1 0\n0 1]��ʽQStringתΪEigen::MatrixXd��ʽ�ľ���

    QString byteToHexStr(unsigned char byte_arr[], int arr_len);//���ֽ���תΪQString

    QString elementToQString(element_t);//element����תΪQString����

    bool hexStr2Byte(std::string hexStr, unsigned char byteArray[]);//����16�����ַ�����תΪ�ֽ����������byteArray

    QString outPow(element_t u, element_t a);//���ES����ָ��u^a,ä������u��a����֤ES����������ȷ�ԣ�������ȷ�����ս������QString�У�������ֹͣ���㲢��ʾ������Ϣ{ָ����Zr�У�������G1��}

    void blindPairGen4();//ϵͳ����ʱ��������ĸ�ä���ԣ�����QString��ʽ�洢��blindPairIndex4��blindPairValue4��

    void rGen(QStringList& rList, int& rowAPM);//��Zr�����ѡ��rowAPM��Ԫ��r����rList

    void computeLambda(QStringList& lambda, int& rowAPM, int& colAPM, Eigen::MatrixXd& APMatrix);//����lambda����������lambda

    QString sendToES(QString& allOutCiDi);//���͸�ES��Ҫ�������CiDi��ȫ���������������м�����

    bool verifyES(QString outResult, QString& CiDiQstr);//��֤ES���ؽ������ȷ�ԣ���ȷ����true

    void displayESRet(QString& outResult);//��ʾ���ؽ��

    void updateMsgCatalog(QString& msgCatalog);//���½������е�SS����ϢĿ¼,msgCatalog��ʽ[FileName;Owner;MsgDesc;MUID|...|...]

    void EDClient::DVCipher();//����SS���ܵ��ľ���Base64������QString[C;C_1;C_2;daw;C1;D1;...;Ci;Di]cipher�����Ͻ��ܷ�����DS���ܲ���֤���ܽ������ȷ��

    QString isAvail(QString& MUID);//����Ҫ���ܵ�MUID��ѯ��KDS�Լ��Ƿ���Խ��ܸ�MUID��Ӧ�����ģ����Խ���(�û����Լ�������ʲ���)�򷵻�[1;KxOrder;subTAPM],���ܽ����򷵻�[0;������ʾ],KxOrder��Ӧ�û�������������ʲ��Ե����Զ�Ӧ��Kx,subTAPM��ӦAPM������Ӧ�Ӿ����ת�þ���

    QString subKxGen(QStringList& KxOrder); //����order���ɶ�ӦKx��ɵ�����[K1; K2; ...; Kx]

    QString subAMPGen(QStringList& APMOrder);//����APMOrder�綨��������ȡAPM����Ϊ�������ʱ���͸�DS���Ӿ���

    void verifyDS(QString& DSCompute);//��֤DS������DSCompute����ȷ��


private slots:
    void recvLogin();//��ʾ�����ڵĲۺ���

    void getMsgInfo();//��ȡ�����ļ����ļ��������ݲ����浽fileName��fileContent��
    
    void processMsgFile();//����ҳ���ȷ�Ϻ�����ܵ��ļ����������ʲ��Ծ����MUID����ʾ�����ES�����Ϣ���ܣ�У��ES���ص�����

    void on_pushButton_clicked();//������ϢĿ¼��ť���õĲۺ���

    void downMsg();//����ѡ�����Ϣbase64����

    void enableDown();//���SS�ļ�Ŀ¼���ʱ�����ж��Ƿ�ѡ��ĳ��

    void on_pushButton_2_clicked();//���ܷ����Ҫ���ܵ��ļ�չʾ���µ�ȷ����ťʱ������DS���н���

public slots:
    void showLoggedUserInfo(QString& loggedUserInfo);//��ʾ���ܵ��ĵ�¼�û���Ϣ����������û���Ϣ��ǩҳ

    void showSSMsgCatalog();//��SS��������������ϢĿ¼

};
