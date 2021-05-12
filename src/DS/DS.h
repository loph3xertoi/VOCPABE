#pragma once
#pragma execution_character_set("utf-8")//�����������

#include <QtWidgets/QWidget>
#include <iostream>
#include "ui_DS.h"
#include "DSServer.h"
#include "pbc.h"
#include <QInputDialog>
#include <Eigen/Dense>

class DS : public QWidget
{
    Q_OBJECT

public:
    DS(QWidget *parent = Q_NULLPTR);
    ~DS();

private:
    Ui::DSClass ui;

    pairing_t pairing;
    DSServer Server;//ʵ����ServerSetup��,��ʼ�������ʵ��������Զ������
    const char* aTypeStr = "type a\
		q 8780710799663312522437781984754049815806883199414208211028653399266475630880222957078625179422662221423155858769582317459277713367317481324925129998224791\
		h 12016012264891146079388821366740534204802954401251311822919615131047207289359704531102844802183906537786776\
		r 730750818665451621361119245571504901405976559617\
		exp2 159\
		exp1 107\
		sign1 1\
		sign0 1";
    QString retQstr;//��ŷ������ܷ��ļ�����

    void showServerIpPort();//��ʾ���ؼ����ĵ�ַ�Ͷ˿�

    QString elementToQString(element_t);//element����תΪQString����

    //decryRawQstr�ĸ�ʽ[K;L;subKx|C_1;C1;D1;C2;D2;...;Ci;Di|subTAPM|name]
    QString preDecry(QString& decryRawQstr);//���յ����ַ������д�������Ӧ���ܣ����ؽ��ܺ���ַ���(GT�е�Ԫ��)

    QStringList computeOmega(QString& subTAPM);//����subTAPM������Ӧ��omegaϵ������omega�б�

    Eigen::MatrixXd toMatrix(QString matrixQstr);//��matrixQstr��Ӧ�ľ���ԭ

    QString MatrixToQString(Eigen::MatrixXd& APM);//��APM����תΪQString

    //�������ս������ʾ������attrNum(�Ϸ���������)��userList(�û�ת��˽Կ),cipherList(ת������),omege(omegeϵ�������ָ�������Ϣ��ϵ��),firstPos(��ȡʽ�ڷ��ʲ����е�λ��,���Ci��ʼλ��)
    QString actualComp(const int& attrNum, const QStringList& cipherList, const QStringList& userSKList, const QStringList& omega, const int& firstPos);


private slots:
    void on_pushButton_clicked();//�ı��������ť

public slots:
    void detectConnect();//��⵽���ܷ����Ӻ���ã�����������ܼ���

    void changeResult(QString& retQstr);//�ı����������retQstr,Ȼ�󽫽���������ܷ�
};
