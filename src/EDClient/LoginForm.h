#pragma once
#pragma execution_character_set("utf-8")//解决中文乱码

#include <QtWidgets/QWidget>
#include "ui_LoginForm.h"
#include <QMessageBox>
//程序开始登录界面
class LoginForm : public QWidget
{
    Q_OBJECT

public:
    LoginForm(QWidget* parent = Q_NULLPTR);
    ~LoginForm();

    //void closeEvent(QCloseEvent* event);

private:
    Ui::LoginFormClass ui;

    void showPrompt(QString&);//将QString显示在登录框的label_prompt处
    

private slots:
    void on_pushButton_register_clicked();//注册按钮

    void on_pushButton_login_clicked();//登录按钮

signals:
    void showMain();//显示主窗口的信号

    void showLogged(QString& loggedUserInfo);//将登录的用户信息显示到用户信息栏

    void SSMsgCatalogSignal();//显示SS消息目录
};
