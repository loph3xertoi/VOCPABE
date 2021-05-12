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
    QStringList promptQstrList = prompt.split(",");                         //�����ص���ʾ��Ϣ��","�ָ����promptQstrList
    ui.label_prompt->setText(promptQstrList.at(1));                         //��ʵ����Ϣ��ʾ�ڵ�¼�����ʾ��
    ui.label_prompt->setWordWrap(true);                                     //����label�Զ�����
    if (promptQstrList.at(0).toInt() == 0)                                  //��ʶ����Ƿ���������KDS�������ĵ�һ����ʶ������register��login(0,����Ƿ�)
        ui.label_prompt->setStyleSheet("QLabel{color:red;}");
    else if(promptQstrList.at(0).toInt() == 1)                              //1,�û����Ѿ����ڣ���ֱ�ӵ�¼��
        ui.label_prompt->setStyleSheet("QLabel{color:red;}");
    else if(promptQstrList.at(0).toInt() == 2)                              //2,���Ѿ�ע����ˣ���ȴ�KDS����Աȷ�ϣ�
        ui.label_prompt->setStyleSheet("QLabel{color:red;}");
    else if (promptQstrList.at(0).toInt() == 3)                             //3,����ע������KDS�������Ѿ��յ�����ȴ�KDS����Աȷ�ϣ�
        ui.label_prompt->setStyleSheet("QLabel{color:green;}");
    else if (promptQstrList.at(0).toInt() == 4)                             //4,����δע�ᣬ��ע����¼��
        ui.label_prompt->setStyleSheet("QLabel{color:red;}");
    else if (promptQstrList.at(0).toInt() == 5)                             //5,����������������룡
        ui.label_prompt->setStyleSheet("QLabel{color:red;}");
    else if (promptQstrList.at(0).toInt() == 6)                             //6,���ڵ�¼...
        ui.label_prompt->setStyleSheet("QLabel{color:green;}");

}

void LoginForm::on_pushButton_register_clicked()//ע��
{
    if ((ui.lineEdit_user->text() == "") || (ui.lineEdit_pwd->text() == ""))//�û���������Ϊ��
    {
        QMessageBox::critical(this, tr("��ʾ"), tr("�û��������벻��Ϊ��"));
        return;
    }
    ClientSetup clientSetup("192.168.43.169", "65534");//����KDS������

    /*sendOrRecvQstr��ŷ��͸�KDS����˵�QString,���ߴ�KDS����˽��ܵ���ʾ��Ϣ
      ��ʽΪ[ʶ���ַ���,�û���,����]
      KDS����˸���ʶ���ַ����ж��Դ��û�����������к��ִ���
      ʶ���ַ�������register�������û�ע�ᡢlogin�����û���¼
    */
    QString sendOrRecvQstr = "register,";//KDS������ж���־��register����KDS�յ�ע������ʹ��","���зָ�
    sendOrRecvQstr += ui.lineEdit_user->text();
    sendOrRecvQstr += ",";
    sendOrRecvQstr += ui.lineEdit_pwd->text();
    
    clientSetup.writeData(sendOrRecvQstr);//����sendOrRecvQstr��KDS������
    clientSetup.clientSocket->waitForReadyRead();//�ȴ�����˽���ʾ��Ϣд��socket
    sendOrRecvQstr = clientSetup.readData();//��ȡKDS���������ص���ʾ��Ϣ
    
    showPrompt(sendOrRecvQstr);//�ڵ�¼��չʾKDS���������ص���Ϣ
    //QCoreApplication::processEvents(QEventLoop::AllEvents, 100);//�������¼�,100ms�ڷ���
    //clientSetup.clientSocket->close();
}

void LoginForm::on_pushButton_login_clicked()//��¼
{    
    if ((ui.lineEdit_user->text() == "") || (ui.lineEdit_pwd->text() == ""))//�û���������Ϊ��
    {
        QMessageBox::critical(this, tr("��ʾ"), tr("�û��������벻��Ϊ��"));
        return;
    }
    ClientSetup clientSetup("192.168.43.169", "65534");//����KDS������

    /*sendOrRecvQstr��ŷ��͸�KDS����˵�QString,���ߴ�KDS����˽��ܵ���ʾ��Ϣ
      ��ʽΪ[ʶ���ַ���,�û���,����]
      KDS����˸���ʶ���ַ����ж��Դ��û�����������к��ִ���
      ʶ���ַ�������register�������û�ע�ᡢlogin�����û���¼
    */
    QString sendOrRecvQstr = "login,";//KDS������ж���־��register����KDS�յ�ע������ʹ��"|"���зָ��û���������[login,name|password]
    sendOrRecvQstr += ui.lineEdit_user->text();
    sendOrRecvQstr += "|";
    sendOrRecvQstr += ui.lineEdit_pwd->text();

    clientSetup.writeData(sendOrRecvQstr);//����sendOrRecvQstr��KDS������
    clientSetup.clientSocket->waitForReadyRead();//�ȴ�KDS����������ʾ��Ϣд��socket
    sendOrRecvQstr = clientSetup.readData();//��ȡKDS���������ص���ʾ��Ϣ

    showPrompt(sendOrRecvQstr);
    if (sendOrRecvQstr.at(0) == '6')//������ܵ���QString��һ���ַ�Ϊ'6',�����¼�ɹ���KDS���������׼�����͸�EDClient�����û��������룬S��SK��cookie
    {
        //QMessageBox::information(this, "client wait for KDS", "wait");
        clientSetup.writeData(QString("ok"));//����KDS�ͻ���׼�����ܵڶ�����Ϣ
        clientSetup.clientSocket->waitForReadyRead();//�����ȴ�KDS�����û���Ϣ
        //QMessageBox::information(this, "daw", "second KDS msg recvd");
        
        sendOrRecvQstr = clientSetup.readData();//��ʽ:�û���;����;SK;cookie;S;g;e(g,g)^alpha;g^a
        //qDebug() << sendOrRecvQstr;
        emit showLogged(sendOrRecvQstr);//�����ܵ����û���Ϣ��ʾ��������������û���Ϣ��
        this->close();//�رյ�¼����
        emit showMain();//��ʾ�ͻ���������
        emit SSMsgCatalogSignal();//��ʾSS��ϢĿ¼
    }
    //clientSetup.clientSocket->waitForDisconnected();//�ȴ�����˶Ͽ�����
}
