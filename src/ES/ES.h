#pragma once
#pragma execution_character_set("utf-8")//�����������

#include <QtWidgets/QWidget>
#include "ui_ES.h"
#include "ESServer.h"
#include "pbc.h"
#include <QInputDialog>

class ES : public QWidget
{
    Q_OBJECT

public:
    ES(QWidget *parent = Q_NULLPTR);
    ~ES();

private:
    Ui::ESClass ui;

    pairing_t pairing;
    ESServer Server;//ʵ����ServerSetup��,��ʼ�������ʵ��������Զ������
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

private slots:
    void on_pushButton_clicked();//�ı��������ť

public slots:
    void detectConnect();//��⵽���ܷ����Ӻ���ã�����CiDi��ز���

    void computeCiDi();//socket�����ݿɶ�ʱ���ô˺�������ʵ�ʵ�CiDi���������

    void ES::changeResult(QString& retQstr);//�ı����������retQstr,Ȼ�󽫽���������ܷ�
};
