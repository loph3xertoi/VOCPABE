#pragma once
#pragma execution_character_set("utf-8")//�����������

#include <QtWidgets/QWidget>
#include "ui_LoginForm.h"
#include <QMessageBox>
//����ʼ��¼����
class LoginForm : public QWidget
{
    Q_OBJECT

public:
    LoginForm(QWidget* parent = Q_NULLPTR);
    ~LoginForm();

    //void closeEvent(QCloseEvent* event);

private:
    Ui::LoginFormClass ui;

    void showPrompt(QString&);//��QString��ʾ�ڵ�¼���label_prompt��
    

private slots:
    void on_pushButton_register_clicked();//ע�ᰴť

    void on_pushButton_login_clicked();//��¼��ť

signals:
    void showMain();//��ʾ�����ڵ��ź�

    void showLogged(QString& loggedUserInfo);//����¼���û���Ϣ��ʾ���û���Ϣ��

    void SSMsgCatalogSignal();//��ʾSS��ϢĿ¼
};
