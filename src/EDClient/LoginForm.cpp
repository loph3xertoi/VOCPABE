#include "LoginForm.h"
#include "ClientSetup.h"
#include <Windows.h>
#include "EDClient.h"
LoginForm::LoginForm(QWidget* parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    //connect(this, &LoginForm::close, this, &EDClient::close);
}

LoginForm::~LoginForm()
{
}

//void LoginForm::closeEvent(QCloseEvent* event)
//{
//    QMessageBox::warning(this, "ddd", "aaaa");
//    return;
//}

void LoginForm::showPrompt(QString& prompt)
{
    //QMessageBox::information(this, "daw", prompt);
    QStringList promptQstrList = prompt.split(",");                         //将返回的提示消息按","分割并存入promptQstrList
    ui.label_prompt->setText(promptQstrList.at(1));                         //将实际消息显示在登录框的提示处
    ui.label_prompt->setWordWrap(true);                                     //设置label自动换行
    if (promptQstrList.at(0).toInt() == 0)                                  //标识请求非法，即发给KDS服务器的第一个标识串不是register或login(0,请求非法)
        ui.label_prompt->setStyleSheet("QLabel{color:red;}");
    else if(promptQstrList.at(0).toInt() == 1)                              //1,用户名已经存在，请直接登录！
        ui.label_prompt->setStyleSheet("QLabel{color:red;}");
    else if(promptQstrList.at(0).toInt() == 2)                              //2,您已经注册过了，请等待KDS管理员确认！
        ui.label_prompt->setStyleSheet("QLabel{color:red;}");
    else if (promptQstrList.at(0).toInt() == 3)                             //3,您的注册请求KDS服务器已经收到，请等待KDS管理员确认！
        ui.label_prompt->setStyleSheet("QLabel{color:green;}");
    else if (promptQstrList.at(0).toInt() == 4)                             //4,您还未注册，请注册后登录！
        ui.label_prompt->setStyleSheet("QLabel{color:red;}");
    else if (promptQstrList.at(0).toInt() == 5)                             //5,密码错误，请重新输入！
        ui.label_prompt->setStyleSheet("QLabel{color:red;}");
    else if (promptQstrList.at(0).toInt() == 6)                             //6,正在登录...
        ui.label_prompt->setStyleSheet("QLabel{color:green;}");

}

void LoginForm::on_pushButton_register_clicked()//注册
{
    if ((ui.lineEdit_user->text() == "") || (ui.lineEdit_pwd->text() == ""))//用户名或密码为空
    {
        QMessageBox::critical(this, tr("提示"), tr("用户名或密码不能为空"));
        return;
    }
    ClientSetup clientSetup("192.168.43.169", "65534");//连接KDS服务器

    /*sendOrRecvQstr存放发送给KDS服务端的QString,或者从KDS服务端接受的提示信息
      格式为[识别字符串,用户名,密码]
      KDS服务端根据识别字符串判定对此用户名和密码进行何种处理
      识别字符串包括register代表新用户注册、login代表用户登录
    */
    QString sendOrRecvQstr = "register,";//KDS服务端判定标志，register代表KDS收到注册请求，使用","进行分隔
    sendOrRecvQstr += ui.lineEdit_user->text();
    sendOrRecvQstr += ",";
    sendOrRecvQstr += ui.lineEdit_pwd->text();
    
    clientSetup.writeData(sendOrRecvQstr);//发送sendOrRecvQstr给KDS服务器
    clientSetup.clientSocket->waitForReadyRead();//等待服务端将提示信息写入socket
    sendOrRecvQstr = clientSetup.readData();//读取KDS服务器返回的提示信息
    
    showPrompt(sendOrRecvQstr);//在登录框展示KDS服务器返回的消息
    //QCoreApplication::processEvents(QEventLoop::AllEvents, 100);//处理发送事件,100ms内返回
    //clientSetup.clientSocket->close();
}

void LoginForm::on_pushButton_login_clicked()//登录
{    
    if ((ui.lineEdit_user->text() == "") || (ui.lineEdit_pwd->text() == ""))//用户名或密码为空
    {
        QMessageBox::critical(this, tr("提示"), tr("用户名或密码不能为空"));
        return;
    }
    ClientSetup clientSetup("192.168.43.169", "65534");//连接KDS服务器

    /*sendOrRecvQstr存放发送给KDS服务端的QString,或者从KDS服务端接受的提示信息
      格式为[识别字符串,用户名,密码]
      KDS服务端根据识别字符串判定对此用户名和密码进行何种处理
      识别字符串包括register代表新用户注册、login代表用户登录
    */
    QString sendOrRecvQstr = "login,";//KDS服务端判定标志，register代表KDS收到注册请求，使用"|"进行分隔用户名和密码[login,name|password]
    sendOrRecvQstr += ui.lineEdit_user->text();
    sendOrRecvQstr += "|";
    sendOrRecvQstr += ui.lineEdit_pwd->text();

    clientSetup.writeData(sendOrRecvQstr);//发送sendOrRecvQstr给KDS服务器
    clientSetup.clientSocket->waitForReadyRead();//等待KDS服务器将提示消息写入socket
    sendOrRecvQstr = clientSetup.readData();//读取KDS服务器返回的提示信息

    showPrompt(sendOrRecvQstr);
    if (sendOrRecvQstr.at(0) == '6')//如果接受到的QString第一个字符为'6',代表登录成功，KDS服务端正在准备发送给EDClient——用户名，密码，S，SK，cookie
    {
        //QMessageBox::information(this, "client wait for KDS", "wait");
        clientSetup.writeData(QString("ok"));//告诉KDS客户端准备接受第二次信息
        clientSetup.clientSocket->waitForReadyRead();//继续等待KDS发送用户信息
        //QMessageBox::information(this, "daw", "second KDS msg recvd");
        
        sendOrRecvQstr = clientSetup.readData();//格式:用户名;密码;SK;cookie;S;g;e(g,g)^alpha;g^a
        //qDebug() << sendOrRecvQstr;
        emit showLogged(sendOrRecvQstr);//将接受到的用户信息显示到程序主界面的用户信息栏
        this->close();//关闭登录窗口
        emit showMain();//显示客户端主窗口
        emit SSMsgCatalogSignal();//显示SS消息目录
    }
    //clientSetup.clientSocket->waitForDisconnected();//等待服务端断开连接
}
