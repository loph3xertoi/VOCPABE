#pragma once
#pragma execution_character_set("utf-8")//�����������

#include <QtWidgets/QWidget>
#include "ui_SS.h"
#include "SSServer.h"
#include "SSSql.h"



class SS : public QWidget
{
    Q_OBJECT

public:
    SS(QWidget *parent = Q_NULLPTR);
    ~SS();

private:
    Ui::SSClass ui;

    SSServer server;//��ʼ��������ʵ��
    SSSql sql;//����sql����
    QSqlQueryModel* MsgStorageModel = new QSqlQueryModel(this);

    void showServerIpPort();//��ʾ���ؼ����ĵ�ַ�Ͷ˿�

    QString storeMsg(QString cipher);//�����ܷ��ϴ������Ĵ������ݿ�

    void showMsgStorage();//��MsgStorage���ݿ��е�������ʾ��SS����

    void sendCatalog();//��MsgStorage����������Ϣ��[FileName;Owner;MsgDesc|...|...]���͸�������

    void sendMsg(QString MUID);//��MUID��Ӧ��Ϣmsg(base64)���͸����ܷ�

public slots:
    void detectConnect();//��⵽���ܻ���ܷ����Ӻ����

    void processUpDown();//�������ݲ������û������ж��ϴ���������
};
