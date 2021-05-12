#include "EDClient.h"
#include "ClientSetup.h"

EDClient::EDClient(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    pairing_init_set_buf(pairing, aTypeStr, strnlen_s(aTypeStr, 400));//Ϊpairingָ������

    QFont font = ui.tableWidget->horizontalHeader()->font(); //��ȡ��ͷԭ��������
    font.setBold(true);//�������ô���
    ui.tableWidget->horizontalHeader()->setFont(font);
    ui.tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers); //���ò��ɱ༭
    ui.tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}");

    ui.tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);//����ֻ��ѡ��һ��
    ui.tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);//����ѡ��һ��

    ui.pushButton_down->setDisabled(true);//δѡ��������Ϣʱ����

    //connect(this, &EDClient::closeEvent, this, &EDClient::clearLogged);//�ͻ����˳�ʱ����������������¼��Ϣ
    connect(ui.pushButton_browse, SIGNAL(clicked()), this, SLOT(getMsgInfo()));
    connect(ui.pushButton_submitE, SIGNAL(clicked()), this, SLOT(processMsgFile()));
    connect(ui.pushButton_down, SIGNAL(clicked()), this, SLOT(downMsg()));//������ذ�ť��SS���������ض�Ӧ�ļ�(MUID)��Msg��base64��������
    connect(ui.tableWidget,SIGNAL(itemSelectionChanged()),this,SLOT(enableDown()));//���SS�ļ�Ŀ¼���ʱ�����ж��Ƿ�ѡ��ĳ��

}

EDClient::~EDClient()
{
}

void EDClient::closeEvent(QCloseEvent* close)//�رտͻ���������ʱ����
{
    clearLogged();
}

void EDClient::recvLogin()
{
    this->show();
}

QString EDClient::isAvail(QString& MUID)
{
    ClientSetup clientSetup("192.168.43.169", "65534");
    QString sendKDS = "Decry," + ui.textBrowser_cookie->toPlainText() + "," + MUID;//���͸�KDS�ĸ�ʽ[Decry,cookie,MUID]
    
    clientSetup.writeData(sendKDS);
    clientSetup.clientSocket->waitForReadyRead();
    QString askResult = clientSetup.readData();

    return askResult;
}

void EDClient::displayESRet(QString& outResult)//[6���ӽṹ�ֺŷֿ�|...|...]
{
    QStringList resultList = outResult.split("|");
    for (QStringList::iterator iter = resultList.begin(); iter != resultList.end(); iter++)
    {
        int index = std::distance(resultList.begin(), iter);
        if (index % 3 == 0)//Ci��һ����
            ui.textBrowser_show->append("<font color=\"#008000\"><b>" + QString("C%1��һ����:").arg(QString::number((index / 3) + 1)) + "</b></font>");
        else if (index % 3 == 1)//Ci�ڶ�����
            ui.textBrowser_show->append("<font color=\"#008000\"><b>" + QString("C%1�ڶ�����:").arg(QString::number((index / 3) + 1)) + "</b></font>");
        else
            ui.textBrowser_show->append("<font color=\"#008000\"><b>" + QString("D%1:").arg(QString::number((index / 3) + 1)) + "</b></font>");
        QStringList subRet = (*iter).split(";");

        ui.textBrowser_show->append("<b>w1^c1:</b>");
        ui.textBrowser_show->append(subRet.at(0));

        ui.textBrowser_show->append("<b>u^(d1*x1):</b>");
        ui.textBrowser_show->append(subRet.at(1));

        ui.textBrowser_show->append("<b>w2^c2:</b>");
        ui.textBrowser_show->append(subRet.at(2));

        ui.textBrowser_show->append("<b>u^(d2*x2):</b>");
        ui.textBrowser_show->append(subRet.at(3));

        ui.textBrowser_show->append("<b>g^(A*c1-B):</b>");
        ui.textBrowser_show->append(subRet.at(4));

        ui.textBrowser_show->append("<b>g^(C*c2-D):</b>");
        ui.textBrowser_show->append(subRet.at(5));

    }
}

void EDClient::getMsgInfo()
{
    fileName.clear();
    fileContent.clear();
    //QDesktopServices::openUrl(QUrl("file:C:\\work\\campus\\Graduation_Project\\Graduation-Project\\code\\", QUrl::TolerantMode));
    //ѡ���ļ��Ի���/
    QFileDialog* f = new QFileDialog(this);
    f->setWindowTitle("ѡ����Ҫ���ܵ��ļ�*.txt");
    f->setNameFilter("*.txt");
    f->setViewMode(QFileDialog::Detail);
    f->setDirectoryUrl(QUrl("file:C:\\work\\campus\\Graduation_Project\\Graduation-Project\\code\\"));
    QString filePath;
    if (f->exec() == QDialog::Accepted)
        filePath = f->selectedFiles()[0];

    ui.lineEdit->setText(filePath);
    QFileInfo info(filePath);

    fileName = info.fileName();//�ļ���

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::warning(this, "ʧ��", "�ļ���ʧ��");
        return;
    }
    //��ȡ�ļ�����
    QTextStream readStream(&file);
    while (!readStream.atEnd())
        fileContent += readStream.readLine();
    //qDebug() << "fileContent = " << fileContent;

    ui.textBrowser->clear();
    ui.textBrowser->append("<b>�ļ���:</b>");
    ui.textBrowser->append(fileName);
    ui.textBrowser->append("<b>�ļ�����:</b>");
    ui.textBrowser->append(fileContent);
}

void EDClient::processMsgFile()
{
    //��KDS�������ύ���ʲ���,KDS����������APMatrix;MUID
    if (ui.textBrowser->toPlainText().isEmpty())//û��ѡ����Ҫ���ܵ��ļ�
    {
        QMessageBox::warning(this, "warn", "��ѡ����Ҫ���ܵ��ļ���");
        return;
    }
    else if (ui.plainTextEdit_2->toPlainText().isEmpty())//û��д�ļ�����
    {
        QMessageBox::warning(this, "warn", "��Ϊ���ܵ��ļ����������");
        return;
    }
    else if (ui.plainTextEdit->toPlainText().isEmpty())//û��������ʲ���
    {
        QMessageBox::warning(this, "warn", "������ʲ��ԣ�");
        return;
    }
    ui.textBrowser_show->clear();
    //ui.textBrowser_show->clearHistory();
    ui.textBrowser_show->append("<font color=\"#008000\"><b>������KDS�������ύ���ʲ���...</b></font>");
    //ui.textBrowser_show->repaint();
    QString retQstr = getAPMatrixMUID(ui.plainTextEdit->toPlainText());
    QStringList retList = retQstr.split(";");

    ui.textBrowser_show->append("<b>���ʲ��Ծ���:</b>");
    ui.textBrowser_show->append(retList.at(0));
    ui.textBrowser_show->append("<b>MUID:</b>");
    ui.textBrowser_show->append(retList.at(1));
    ui.textBrowser_show->append("<b>HXNUM:</b>");
    ui.textBrowser_show->append(retList.at(2));
    ui.textBrowser_show->repaint();

    hxOrderList = retList.at(2).split(",");//��hx�Ķ�Ӧ˳�����hxOrderList
    Eigen::MatrixXd APMatrix = toMatrix(retList.at(0));//��QString���͵ķ��ʲ��Ծ���[1 1\n1 0]��ʽתΪEigen::MatrixXd���͵ľ���
    
    QString CTMUID = encryAndVerify(APMatrix);//����APMatrix������������CT
    CTMUID += ";" + ui.plainTextEdit_2->toPlainText();//�ļ�����
    CTMUID += ";" + retList.at(1);//MUID
    //��ʱCTMUID���:CT;�ļ�����;MUID
    ui.textBrowser_show->append("<font color=\"#008000\"><b>���ڽ������ϴ����洢������...</b></font>");
    ui.textBrowser_show->repaint();
    if(vSignal == true)
        uploadToSS(CTMUID);
    else
        QMessageBox::critical(this, "��֤����", "ES��������֤����!");
}

QString EDClient::getAPMatrixMUID(QString& accessPolicy)
{
    ClientSetup clientSetup("192.168.43.169", "65534");//����KDS������
    QString sendOrRecvQstr = "AP";//�������ݸ�ʽAP�����͵�Ϊ���ʲ���,���շ��͸�ʽΪ[AP,accessPolicy,cookie]
    sendOrRecvQstr += ",";
    sendOrRecvQstr += accessPolicy;
    sendOrRecvQstr += ",";
    sendOrRecvQstr += ui.textBrowser_cookie->toPlainText();

    clientSetup.writeData(sendOrRecvQstr);
    clientSetup.clientSocket->waitForReadyRead();//�ȴ�KDS��ȡ���ʲ���
    QString recvQstr = clientSetup.readData();//���ظ�ʽ:APMatrix;MUID;HXNUM
    return recvQstr;
}

QString EDClient::computeCiDi(Eigen::MatrixXd& APMatrix)
{
    //QMessageBox::warning(this, "warn", "computeCiDi");    
    int rowAPM = APMatrix.rows();
    int colAPM = APMatrix.cols();

    ui.textBrowser_show->append("<font color=\"#008000\"><b>��������s:</b></font>");
    ui.textBrowser_show->append(sQstr);
    ui.textBrowser_show->append("<font color=\"#008000\"><b>���ڼ��㹲�����ܷݶ�lambda...</b></font>");
    ui.textBrowser_show->repaint();

    QStringList rList;//���rowAPM��r
    QStringList lambda;//���lambda����

    rGen(rList,rowAPM);//��Zr�����ѡ��rowAPM��Ԫ��r����rList
    computeLambda(lambda, rowAPM, colAPM, APMatrix);//����lambda����������lambda

    //qDebug() << "lambda = " << lambda;
    for (QStringList::iterator iter = lambda.begin(); iter != lambda.end(); iter++)
    {
        ui.textBrowser_show->append(QString("<b>lambda[%1]:</b>").arg(QString::number(std::distance(lambda.begin(), iter + 1))));
        ui.textBrowser_show->append(*iter);
        ui.textBrowser_show->repaint();
    }

    element_t uBase, aIndex;
    element_init_G1(uBase, pairing);
    element_init_Zr(aIndex, pairing);

    //��������CiDi��Ҫ�Ĳ���[w1;c1;uBase^x1;A*c1-B;d1;w2;c2;uBase^x2;C*c2-D;d2;2��ǰ���ʽ|�ظ�rowAPM-1��|g]
    QString allOutCiDi;

    ////����
    //QStringList CiList, DiList;
    //element_t Ci, Di;
    //element_t A1, B1, C1, D1;
    //element_init_G1(Ci, pairing);
    //element_init_G1(Di, pairing);
    //element_init_G1(A1, pairing);
    //element_init_Zr(B1, pairing);
    //element_init_G1(C1, pairing);
    //element_init_Zr(D1, pairing);
    ////����


    for (int i = 0; i < rowAPM; i++)//����rowAPM��CiDi��
    {

        ui.textBrowser_show->append("<font color=\"#008000\"><b>" + QString("���ڼ������C%1��Ҫ�Ĳ���...").arg(QString::number(i + 1)) + "</b></font>");
        ui.textBrowser_show->append("<b>�����һ����[g^(a*lambda)]...</b>");
        ui.textBrowser_show->repaint();

        element_set_str(uBase, PK.at(2).toStdString().c_str(), 10);
        element_set_str(aIndex, lambda.at(i).toStdString().c_str(), 10);
        allOutCiDi += outPow(uBase, aIndex);
        allOutCiDi += ";";

        ////����
        //element_set(A1, uBase);
        //element_set(B1, aIndex);
        ////����

        ui.textBrowser_show->append("<b>����ڶ�����[hx^(-r)]...</b>");
        ui.textBrowser_show->repaint();

        element_set_str(uBase, PK.at(3 + hxOrderList.at(i).toInt()).toStdString().c_str(), 10);
        element_set_str(aIndex, rList.at(i).toStdString().c_str(), 10);
        element_neg(aIndex, aIndex);
        allOutCiDi += outPow(uBase, aIndex);
        allOutCiDi += ";";

        ////����
        //element_set(C1, uBase);
        //element_set(D1, aIndex);
        //element_pow2_zn(Ci, A1, B1, C1, D1);
        //CiList.append(elementToQString(Ci));
        ////����

        ui.textBrowser_show->append("<font color=\"#008000\"><b>" + QString("���ڼ������D%1��Ҫ�Ĳ���...").arg(QString::number(i + 1)) + "</b></font>");
        ui.textBrowser_show->repaint();

        element_set_str(uBase, PK.at(0).toStdString().c_str(), 10);
        element_set_str(aIndex, rList.at(i).toStdString().c_str(), 10);
        allOutCiDi += outPow(uBase, aIndex);
        allOutCiDi += "|";
        ui.textBrowser_show->repaint();

        ////����
        //element_set(A1, uBase);
        //element_set(B1, aIndex);
        //element_pow_zn(Di, A1, B1);
        //DiList.append(elementToQString(Di));
        ////����
    }

    allOutCiDi += PK.at(0);//������������Ԫg
    allOutCiDi += "|";
    allOutCiDi += ui.label_name->text();//�����Ӽ���������

    ////����
    //qDebug() << "CiList = ";
    //qDebug() << CiList;
    //qDebug() << "DiList = ";
    //qDebug() << DiList
    //qDebug() << "allOutCiDi" << allOutCiDi;
    ////����

    element_clear(uBase);
    element_clear(aIndex);

    return allOutCiDi;
}

Eigen::MatrixXd EDClient::toMatrix(QString matrixQstr)
{
    Eigen::MatrixXd destMatrix;
    QStringList rowList = matrixQstr.split("\n");
    int rowNum = (int)rowList.size();

    for (QStringList::iterator iterRow = rowList.begin(); iterRow != rowList.end(); iterRow++) {
        QStringList metaItemList = (*iterRow).split(" ");//ÿ�е�Ԫ������б�
        if (iterRow == rowList.begin())//��һ��ѭ��ָ��destMatrix�Ĵ�С��Ϊ������ڴ�
        {
            int colNum = (int)metaItemList.size();
            destMatrix.resize(rowNum, colNum);//ָ����С
        }
        for (QStringList::iterator iterCol = metaItemList.begin(); iterCol != metaItemList.end(); iterCol++)
            destMatrix(std::distance(rowList.begin(), iterRow), std::distance(metaItemList.begin(), iterCol)) = (*iterCol).toInt();
    }
    //std::cout << destMatrix << std::endl;
    return destMatrix;
}

QString EDClient::encryAndVerify(Eigen::MatrixXd& APMatrix)
{

    //���ȼ���C��C_1��C_2����������CT��ǰ�����ȫ�ɼ��ܷ���ɼ���
    ui.textBrowser_show->append("<font color=\"#008000\"><b>���ڼ���C��C_1��C_2...</b></font>");
    ui.textBrowser_show->repaint();
    QStringList CTList = computeThreeOfCT();//����CT:C;C_1;C_2
    QString CT;//��������
    ui.textBrowser_show->append("<b>C:</b>");
    ui.textBrowser_show->append(CTList.at(0));
    ui.textBrowser_show->append("<b>C_1:</b>");
    ui.textBrowser_show->append(CTList.at(1));
    ui.textBrowser_show->append("<b>C_2:</b>");
    ui.textBrowser_show->append(CTList.at(2));
    ui.textBrowser_show->append("<font color=\"#008000\"><b>���ڼ����������Ci��Di��Ҫ�Ĳ���...</b></font>");
    ui.textBrowser_show->repaint();

    //Ȼ�����Ci��Di
    CT = CTList.join(";");//�ϲ���QString,";"����

    QString allOutCiDi = computeCiDi(APMatrix);//allOutCiDi��ż���CiDi��Ҫ�Ĳ���

    ui.textBrowser_show->append("<font color=\"#008000\"><b>���ڽ��������[����CiDi��Ҫ]���͸�ES...</b></font>");
    ui.textBrowser_show->repaint();

    //������CiDi��Ҫ�Ĳ����ϴ���������ܷ�����ES������6*3*rowAPM���ӽṹ��3ָÿ��Ci����2�������ÿ��Di����1���������Ϊ3��ÿ���������6���ӽṹ
    QString outResult = sendToES(allOutCiDi);//[w1^c1;u^(d1*x1);w2^c2;u^(d2*x2);g^(A*c1-B);g^(C*c2-D);.;.|...]


    ui.textBrowser_show->append("<font color=\"#008000\"><b><br>ES���ؽ��:</b></font>");
    ui.textBrowser_show->append(outResult);

    displayESRet(outResult);//��ʾ���ؽ��

    ui.textBrowser_show->append("<font color=\"#008000\"><b>������֤ES���ؽ������ȷ��...</b></font>");
    ui.textBrowser_show->repaint();

    QString CiDiQstr;//��֤��ȷ�������CiDi���,[C1;D1;C2;D2;...;Ci;Di]
    vSignal = verifyES(outResult, CiDiQstr);//��֤��ȷ����true
    ui.textBrowser_show->append("<font color=\"#008000\"><b><br>��֤��ɣ�</b></font>");
    ui.textBrowser_show->repaint();

    QStringList CiDiQstrList = CiDiQstr.split(";"); //[C1;D1;C2;D2;...;Ci;Di]
    ui.textBrowser_show->append("<font color=\"#008000\"><b>CiDi��ֵ����:</b></font>");

    for (QStringList::iterator iter = CiDiQstrList.begin(); iter != CiDiQstrList.end(); iter++)
    {
        int index = std::distance(CiDiQstrList.begin(), iter);
        if (index % 2 == 0)//Ci
        {
            ui.textBrowser_show->append("<b>" + QString("C%1:").arg(QString::number((index / 2) + 1)) + "</b>");
            ui.textBrowser_show->append(*iter);
        }
        else//Di
        {
            ui.textBrowser_show->append("<b>" + QString("D%1:").arg(QString::number((index / 2) + 1)) + "</b>");
            ui.textBrowser_show->append(*iter);
        }

    }
    CT += ";daw;";//��λ���ţ���ʾ��Ϣ�Ľ�β
    CT += CiDiQstr;//��ʱ����CT:C;C_1;C_2;daw;Ci;Di

    ui.textBrowser_show->append("<b>��������CT:</b>");
    ui.textBrowser_show->append(CT);
    ui.textBrowser_show->repaint();
    qDebug() << CT.length();
    return CT;
}

QStringList EDClient::computeThreeOfCT()
{
    //QMessageBox::warning(this, "warn", "computeThreeOfCT");
    element_t C, C_1;
    element_init_GT(C, pairing);
    element_init_G1(C_1, pairing);
    //��ȡ����Ԫg
    element_t g;
    element_init_G1(g, pairing);
    element_set_str(g, PK.at(0).toStdString().c_str(), 10);

    //����C
    
    //�����GT��ѡ��r
    element_t r;
    element_init_GT(r, pairing);
    element_random(r);
    rQstr = elementToQString(r);

    //��ȡe(g,g)^alpha
    element_t e_g_g_alpha;
    element_init_GT(e_g_g_alpha, pairing);
    element_set_str(e_g_g_alpha, PK.at(1).toStdString().c_str(), 10);

    //��ȡR����r��Ӧ��sha256��16�����ַ���
    std::string Rstr;//R���SHA256(r)��Ӧ��16���ƹ�ϣ�ַ���
    CryptoPP::SHA256 sha256;
    CryptoPP::StringSource ssA(//��r�еõ���Ӧ�Ĺ�ϣ�ַ�������R
        rQstr.toStdString(),
        true,
        new CryptoPP::HashFilter(sha256,
            new CryptoPP::HexEncoder(
                new CryptoPP::StringSink(Rstr)
            )
        )
    );
    QString R = QString::fromStdString(Rstr);

    ui.textBrowser_show->append("<b>R:</b>");
    ui.textBrowser_show->append(R);
    ui.textBrowser_show->repaint();

    //���㹲������s[SHA256(R|m)]
    element_t s;
    element_init_Zr(s, pairing);
    std::string R_M = (R + fileContent).toStdString();
    //qDebug() << R + fileContent;
    std::string RMHash;//���R��ԭʼ��Ϣƴ�ӵ�SHA256��16�����ַ���
    CryptoPP::StringSource ssB(
        R_M,
        true,
        new CryptoPP::HashFilter(sha256,
            new CryptoPP::HexEncoder(
                new CryptoPP::StringSink(RMHash)
            )
        )
    );
    //��RMHashӳ�䵽Zr�е�s
    element_from_hash(s, (void*)RMHash.c_str(), RMHash.length());
    //����s
    sQstr = elementToQString(s);

    //����e(g,g)^(alpha*s)
    element_t e_g_g_alpha_s;
    element_init_GT(e_g_g_alpha_s, pairing);
    element_pow_zn(e_g_g_alpha_s, e_g_g_alpha, s);

    //����C[r*e(g,g)^(alpha*s)]
    element_mul(C, r, e_g_g_alpha_s);
    
    //element_printf("e(g,g)^(s*alpha) = %B\n", e_g_g_alpha_s);
    //����C_1[g^s]
    element_pow_zn(C_1, g, s);

    //����C_2[С��fileContent��R���]
    unsigned char byteArrayR[32];//SHA256��32���ֽ�
    //const char* ptrR = (const char*)byteArrayR;
    if (!hexStr2Byte(Rstr, byteArrayR))//�����ϣֵ�Ƿ�
    {
        QMessageBox::critical(this, "error", "�����ϣֵ�Ƿ���");
        return QStringList();
    }
    //qDebug() << R;
    //qDebug() << QString::fromUtf8(ptrR,32);
    std::cout << Rstr << std::endl;
    QByteArray msgByteArray = fileContent.toUtf8();//��ԭʼ��ϢתΪutf�����µ��ֽ���
    QByteArray cipherByteArray;//���ܺ������
    cipherByteArray.resize(msgByteArray.size());//�����ڴ�
    //��ÿ���ֽ���ѭ����byteArrayR���ֽ����
    for (QByteArray::iterator iter = msgByteArray.begin(); iter != msgByteArray.end(); iter++)
    {
        int index = std::distance(msgByteArray.begin(), iter);
        cipherByteArray[index] = (*iter) ^ byteArrayR[index % 32];
    }

    QByteArray base64C_2 = cipherByteArray.toBase64();

    QString C_2 = QString::fromUtf8(base64C_2);//����Base64���ܺ������

    QStringList retList;
    retList.append(elementToQString(C));
    retList.append(elementToQString(C_1));
    retList.append(C_2);

    element_clear(C);
    element_clear(C_1);
    element_clear(g);
    element_clear(r);
    element_clear(e_g_g_alpha);
    element_clear(s);
    element_clear(e_g_g_alpha_s);

    return retList;
}

void EDClient::uploadToSS(QString& CTMUID)
{
    ClientSetup clientSetup("192.168.43.169", "65531");
    if (!clientSetup.isConnected)//����SS������ʧ��
        return;
    QString sentSS = "up|" + ui.label_name->text() + ";" + fileName + ";" + CTMUID;//��ʽ��
    clientSetup.writeData(sentSS);//�����ϴ���Ϣ��SS

    clientSetup.clientSocket->waitForReadyRead();//�ȴ�SS��socket
    QString recvQstr = clientSetup.readData();//�յ�SS��������ϢĿ¼[1|FileName;Owner;MsgDesc;MUID|...|...]
    ui.textBrowser_show->append("<font color=\"#008000\"><b>�ɹ��������ϴ����洢������,���ڸ���SS��ϢĿ¼...</b></font>");
    //qDebug() << "recvQstr = " << recvQstr;
    updateMsgCatalog(recvQstr);//����SS�洢����ϢĿ¼
}

void EDClient::clearLogged()
{
    //QMessageBox::information(this, "clear Logged", "exit");
    ClientSetup clientSetup("192.168.43.169", "65534");         //�˳�ʱ����KDS                          //����KDS������
    QString sendOrRecvQstr = "exit,";                           //exit��ʾ�û��˳�
    sendOrRecvQstr += ui.label_name->text();                    //�û���
    sendOrRecvQstr += ",";
    sendOrRecvQstr += ui.textBrowser_cookie->toPlainText();     //�û���ʱcookie
    //qDebug() << sendOrRecvQstr;
    clientSetup.clientSocket->waitForConnected();               //�ȴ���KDS��������
    //QMessageBox::information(this, "success", "connect to KDS");
    clientSetup.writeData(sendOrRecvQstr);                      //����sendOrRecvQstr��KDS������
    clientSetup.clientSocket->waitForDisconnected();            //�ȴ�KDSȫ��������socket��Ϣ
}

//��ʽ:�û���;����;z;K;L;Kx;cookie;S;g;e(g,g)^alpha;g^a;hx
void EDClient::showLoggedUserInfo(QString& recvUserLoggedInfo)
{
    QStringList userInfo = recvUserLoggedInfo.split(";");
    QString subShow;//����ʾ�ַ���
    //qDebug() << userInfo;

    //��ʾ�û���
    ui.label_name->setText(userInfo.at(0));
    ui.label_name->setWordWrap(true);
    
    //��ʾ����
    ui.label_passwd->setText(userInfo.at(1));
    ui.label_passwd->setWordWrap(true);
    
    //��ʾϵͳ����PK
    subShow = "<b>g:</b>" + userInfo.at(8);
    ui.textBrowser_PK->append(subShow);
    subShow = "<b>e(g,g)^alpha:</b>" + userInfo.at(9);
    ui.textBrowser_PK->append(subShow);
    subShow = "<b>g^a:</b>" + userInfo.at(10);
    ui.textBrowser_PK->append(subShow);
    subShow = "<b>hx:</b>";
    ui.textBrowser_PK->append(subShow);
    //��PK����QStringList����PK��
    PK.append(userInfo.at(8));
    PK.append(userInfo.at(9));
    PK.append(userInfo.at(10));
    for (QStringList::iterator iter = userInfo.begin() + 11; iter != userInfo.end(); iter++)//��ÿ��hxƴ��PK����
    {
        PK.append(*iter);
        ui.textBrowser_PK->append(*iter);
    }
    //QMessageBox::information(this, "daw", "ready to show user info");

    //��ʾ�û�˽Կ[z;K;L;Kx]
    subShow = "<b>z:</b>" + userInfo.at(2);
    ui.textBrowser_SK->append(subShow);
    subShow = "<b>K[g^((alpha+at)/z)]:</b>" + userInfo.at(3);
    ui.textBrowser_SK->append(subShow);
    subShow = "<b>L[g^(t/z)]:</b>" + userInfo.at(4);
    ui.textBrowser_SK->append(subShow);
    subShow = "<b>Kx[hx^(t/z)]:</b>" + userInfo.at(5);
    ui.textBrowser_SK->append(subShow);
    
    SK.append(userInfo.at(2));
    SK.append(userInfo.at(3));
    SK.append(userInfo.at(4));
    SK.append(userInfo.at(5));

    //��ʾ�û���ʱcookie
    ui.textBrowser_cookie->setText(userInfo.at(6));
    
    //��ʾ�û����Լ�S
    ui.label_S->setText(userInfo.at(7));
    ui.label_S->setWordWrap(true);

    blindPairGen4();//�������4��ä����blindPairIndex4

    //��ʾ�ĸ����ä����
    subShow = blindPairIndex4.at(0) + ":" + blindPairValue4.at(0) + "\n";
    ui.textBrowser_blind->append(subShow);
    subShow = blindPairIndex4.at(1) + ":" + blindPairValue4.at(1) + "\n";
    ui.textBrowser_blind->append(subShow);
    subShow = blindPairIndex4.at(2) + ":" + blindPairValue4.at(2) + "\n";
    ui.textBrowser_blind->append(subShow);
    subShow = blindPairIndex4.at(3) + ":" + blindPairValue4.at(3) + "\n";
    ui.textBrowser_blind->append(subShow);

    //ui.textBrowser_cookie->setFixedHeight(ui.textBrowser_cookie->document()->size().height()+2);//����cookie��ʾҳ��С
}

QString EDClient::byteToHexStr(unsigned char byte_arr[], int arr_len)
{
    //std::string* hexstr = new std::string();
    QString hexstr;
    for (int i = 0; i < arr_len; i++)
    {
        char hex1;
        char hex2;
        /*����C++֧�ֵ�unsigned��int��ǿ��ת������unsigned char��ֵ��int��ֵ����ôϵͳ�ͻ��Զ����ǿ��ת��*/
        int value = byte_arr[i];
        int S = value / 16;
        int Y = value % 16;
        //��C++��unsigned char��int��ǿ��ת���õ�����ת����ĸ
        if (S >= 0 && S <= 9)
            hex1 = (char)(48 + S);
        else
            hex1 = (char)(55 + S);
        //��C++��unsigned char��int��ǿ��ת���õ�������ת����ĸ
        if (Y >= 0 && Y <= 9)
            hex2 = (char)(48 + Y);
        else
            hex2 = (char)(55 + Y);
        //���һ���Ĵ���ʵ�֣������õ���������ĸ���ӳ��ַ����ﵽĿ��
        hexstr = hexstr + hex1 + hex2;
    }
    return hexstr;
}

QString EDClient::elementToQString(element_t point)
{
    char* ourQStr = (char*)calloc(350, 1);//��ʼ��
    element_snprint(ourQStr, 350, point);//��pointתΪchar*����ourQStr
    return QString(ourQStr);
}

bool EDClient::hexStr2Byte(std::string hexStr, unsigned char byteArray[])//��64���ȵ�hex�ַ���תΪ32�ֽڵ����飬����false��ʾ�����hex�ַ������Ϸ�
{
    for (int i = 0; i < 32; i++)
    {
        int j = 2 * i;//�ֽڸ�λ
        int firstValue = 0;
        int secondValue = 0;
        if (hexStr[j] >= '0' && hexStr[j] <= '9')//�����λֵ
            firstValue = 16 * (hexStr[j] - '0');
        else if (hexStr[j] >= 'A' && hexStr[j] <= 'F')
            firstValue = 16 * (hexStr[j] - 'A' + 10);
        else if (hexStr[j] >= 'a' && hexStr[j] <= 'f')
            firstValue = 16 * (hexStr[j] - 'a' + 10);
        else
            return false;//���Ϸ�

        if (hexStr[j + 1] >= '0' && hexStr[j + 1] <= '9') // �����λֵ
            secondValue = hexStr[j + 1] - '0';
        else if (hexStr[j + 1] >= 'A' && hexStr[j + 1] <= 'F')
            secondValue = hexStr[j + 1] - 'A' + 10;
        else if (hexStr[j + 1] >= 'a' && hexStr[j + 1] <= 'f')
            secondValue = hexStr[j + 1] - 'a' + 10;
        else
            return false;//���Ϸ�
        byteArray[i] = firstValue + secondValue;
    }

    return true;//�ɹ�
}

QString EDClient::outPow(element_t uBase, element_t aIndex)//����uָ��a�����ä������u^a
{
    QString resultQstr;//���صĽ������QString��[w1;c1;uBase^x1;A*c1-B;d1;w2;c2;uBase^x2;C*c2-D;d2],�˽��ֱ�ӷ���ES�������һ�����ָ������
    QString showQstr;//��ʾ��������ַ���
    element_t g;//����Ԫ
    element_init_G1(g, pairing);
    element_set_str(g, PK.at(0).toStdString().c_str(), 10);

    //��ԭ���ä����
    element_t A, B, C, D, AV, BV, CV, DV;//ABCD���ζ�Ӧ���ä����ָ����AV��Ӧg^A,�Դ�����
    element_init_Zr(A, pairing);
    element_init_Zr(B, pairing);
    element_init_Zr(C, pairing);
    element_init_Zr(D, pairing);
    element_init_G1(AV, pairing);
    element_init_G1(BV, pairing);
    element_init_G1(CV, pairing);
    element_init_G1(DV, pairing);

    element_set_str(A, blindPairIndex4.at(0).toStdString().c_str(), 10);
    element_set_str(B, blindPairIndex4.at(1).toStdString().c_str(), 10);
    element_set_str(C, blindPairIndex4.at(2).toStdString().c_str(), 10);
    element_set_str(D, blindPairIndex4.at(3).toStdString().c_str(), 10);
    element_set_str(AV, blindPairValue4.at(0).toStdString().c_str(), 10);
    element_set_str(BV, blindPairValue4.at(1).toStdString().c_str(), 10);
    element_set_str(CV, blindPairValue4.at(2).toStdString().c_str(), 10);
    element_set_str(DV, blindPairValue4.at(3).toStdString().c_str(), 10);


    //����w1(uBase/g^A),Aָ��һ��ä���Ե�ָ��[ä������uBase]
    element_t w1;
    element_init_G1(w1, pairing);
    element_div(w1, uBase, AV);
    showQstr = elementToQString(w1);
    resultQstr = showQstr + ";";
    ui.textBrowser_show->append("<b>w1:</b>" + showQstr);
    //ui.textBrowser_show->repaint();

    //����c1(aIndex-d1*x1)[ä��ָ��aIndex]
    element_t d1, x1;//���ѡ��Zr�е�Ԫ��
    element_init_Zr(d1, pairing);
    element_init_Zr(x1, pairing);
    element_random(d1);
    element_random(x1);
    element_t d1_x1;//d1*x1
    element_init_Zr(d1_x1, pairing);
    element_mul(d1_x1, d1, x1);
    element_t c1;
    element_init_Zr(c1, pairing);
    element_sub(c1, aIndex, d1_x1);
    showQstr = elementToQString(c1);
    resultQstr += showQstr + ";";
    ui.textBrowser_show->append("<b>c1:</b>" + showQstr);
    //ui.textBrowser_show->repaint();

    //����uBase^x1
    element_t u_x1;
    element_init_G1(u_x1, pairing);
    element_pow_zn(u_x1, uBase, x1);
    showQstr = elementToQString(u_x1);
    resultQstr += showQstr + ";";
    ui.textBrowser_show->append("<b>u_x1:</b>" + showQstr);
    //ui.textBrowser_show->repaint();

    //����A*c1-B��A��B�ֱ�Ϊǰ�������ä���Ե�ָ��
    element_t A_c1_B;
    element_init_Zr(A_c1_B, pairing);
    element_t A_c1;
    element_init_Zr(A_c1, pairing);
    element_mul(A_c1, A, c1);
    element_sub(A_c1_B, A_c1, B);
    showQstr = elementToQString(A_c1_B);
    resultQstr += showQstr + ";";
    ui.textBrowser_show->append("<b>A_c1_B:</b>" + showQstr);
    //ui.textBrowser_show->repaint();

    //d1��ӵ�resultQstr
    showQstr = elementToQString(d1);
    resultQstr += showQstr + ";";
    ui.textBrowser_show->append("<b>d1:</b>" + showQstr);


    //����w2(uBase/g^C),Cָ������ä���Ե�ָ��[ä������uBase]
    element_t w2;
    element_init_G1(w2, pairing);
    element_div(w2, uBase, CV);
    showQstr = elementToQString(w2);
    resultQstr += showQstr + ";";
    ui.textBrowser_show->append("<b>w2:</b>" + showQstr);
    //ui.textBrowser_show->repaint();

    //����c2(aIndex-d2*x2)[ä��ָ��aIndex]
    element_t d2, x2;//���ѡ��Zr�е�Ԫ��
    element_init_Zr(d2, pairing);
    element_init_Zr(x2, pairing);
    element_random(d2);
    element_random(x2);
    element_t d2_x2;//d2*x2
    element_init_Zr(d2_x2, pairing);
    element_mul(d2_x2, d2, x2);
    element_t c2;
    element_init_Zr(c2, pairing);
    element_sub(c2, aIndex, d2_x2);
    showQstr = elementToQString(c2);
    resultQstr += showQstr + ";";
    ui.textBrowser_show->append("<b>c2:</b>" + showQstr);
    //ui.textBrowser_show->repaint();

    //����uBase^x2
    element_t u_x2;
    element_init_G1(u_x2, pairing);
    element_pow_zn(u_x2, uBase, x2);
    showQstr = elementToQString(u_x2);
    resultQstr += showQstr + ";";
    ui.textBrowser_show->append("<b>u_x2:</b>" + showQstr);
    //ui.textBrowser_show->repaint();

    //����C*c2-D��C��D�ֱ�Ϊ���������ä���Ե�ָ��
    element_t C_c2_D;
    element_init_Zr(C_c2_D, pairing);
    element_t C_c2;
    element_init_Zr(C_c2, pairing);
    element_mul(C_c2, C, c2);
    element_sub(C_c2_D, C_c2, D);
    showQstr = elementToQString(C_c2_D);
    resultQstr += showQstr + ";";
    ui.textBrowser_show->append("<b>C_c2_D:</b>" + showQstr);
    //ui.textBrowser_show->repaint();

    //d2��ӵ�resultQstr
    showQstr = elementToQString(d2);
    ui.textBrowser_show->append("<b>d2:</b>" + showQstr);
    resultQstr += showQstr;

    element_clear(g);
    element_clear(A);
    element_clear(B);
    element_clear(C);
    element_clear(D);
    element_clear(AV);
    element_clear(BV);
    element_clear(CV);
    element_clear(DV);

    element_clear(w1);
    element_clear(d1);
    element_clear(x1);
    element_clear(d1_x1);
    element_clear(c1);
    element_clear(u_x1);
    element_clear(A_c1_B);
    element_clear(A_c1);

    element_clear(w2);
    element_clear(d2);
    element_clear(x2);
    element_clear(d2_x2);
    element_clear(c2);
    element_clear(u_x2);
    element_clear(C_c2_D);
    element_clear(C_c2);


    return resultQstr;
}

void EDClient::blindPairGen4()
{
    element_t g;//����Ԫ����������ä����
    element_init_G1(g, pairing);
    element_set_str(g, PK.at(0).toStdString().c_str(), 10);

    element_t blindIndexA, blindIndexB, blindIndexC, blindIndexD;//����ä���Ե�ָ��
    element_t blindA, blindB, blindC, blindD;//���ܷ���������ʱ����[����]���ä���Լ�blindA=g^blindIndexA
    element_init_Zr(blindIndexA, pairing);
    element_init_Zr(blindIndexB, pairing);
    element_init_Zr(blindIndexC, pairing);
    element_init_Zr(blindIndexD, pairing);
    element_init_G1(blindA, pairing);
    element_init_G1(blindB, pairing);
    element_init_G1(blindC, pairing);
    element_init_G1(blindD, pairing);

    //���ѡ��ָ��
    element_random(blindIndexA);
    element_random(blindIndexB);
    element_random(blindIndexC);
    element_random(blindIndexD);

    //ä���Լ���
    element_pow_zn(blindA, g, blindIndexA);
    element_pow_zn(blindB, g, blindIndexB);
    element_pow_zn(blindC, g, blindIndexC);
    element_pow_zn(blindD, g, blindIndexD);

    //��ָ�����浽blindPairIndex4��
    blindPairIndex4.append(elementToQString(blindIndexA));
    blindPairIndex4.append(elementToQString(blindIndexB));
    blindPairIndex4.append(elementToQString(blindIndexC));
    blindPairIndex4.append(elementToQString(blindIndexD));

    //�����������浽blindPairValue4��
    blindPairValue4.append(elementToQString(blindA));
    blindPairValue4.append(elementToQString(blindB));
    blindPairValue4.append(elementToQString(blindC));
    blindPairValue4.append(elementToQString(blindD));

    element_clear(g);
    element_clear(blindIndexA);
    element_clear(blindIndexB);
    element_clear(blindIndexC);
    element_clear(blindIndexD);
    element_clear(blindA);
    element_clear(blindB);
    element_clear(blindC);
    element_clear(blindD);

}

void EDClient::rGen(QStringList& rList, int& rowAPM)
{
    element_t r;
    element_init_Zr(r, pairing);
    for (int i = 0; i < rowAPM; i++)
    {
        element_random(r);
        rList.append(elementToQString(r));
    }
    element_clear(r);
}

void EDClient::computeLambda(QStringList& lambda, int& rowAPM, int& colAPM, Eigen::MatrixXd& APMatrix)
{
    element_t y;
    element_init_Zr(y, pairing);

    QStringList yList;//���colAPM-1��y
    yList.append(sQstr);
    //���ѡ��n-1��Zr�е�Ԫ����Ϊ���ܷ����������ĳ�s֮�����������y
    for (int i = 0; i < colAPM - 1; i++)
    {
        element_random(y);
        yList.append(elementToQString(y));
    }

    element_t temp;//tempΪ�;������������м�Ԫ��,���������е�Ԫ��
    element_init_Zr(temp, pairing);
    element_t tempM;//APM�����е�Ԫ��
    element_init_Zr(tempM, pairing);
    element_t subLambda;//��ż����lambdaֵ
    element_init_Zr(subLambda, pairing);
    element_t tempMul;//���APMԪ�غ����ܷ�������Ԫ����˵Ľ��
    element_init_Zr(tempMul, pairing);

    //����lambda��rowAPM��
    for (int i = 0; i < rowAPM; i++)
    {
        element_set0(subLambda);//ÿ�μ����µ�lambdaʱ��Ϊ0
        for (int j = 0; j < colAPM; j++)
        {
            element_set_str(temp, yList.at(j).toStdString().c_str(), 10);
            element_set_si(tempM, APMatrix(i, j));
            element_mul(tempMul, tempM, temp);
            element_add(subLambda, subLambda, tempMul);
        }
        lambda.append(elementToQString(subLambda));
    }

    element_clear(y);
    element_clear(temp);
    element_clear(tempM);
    element_clear(subLambda);
    element_clear(tempMul);
}

QString EDClient::sendToES(QString& allOutCiDi)
{
    ClientSetup clientSetup("192.168.43.169", "65533");
    if (!clientSetup.isConnected)//����ES������ʧ��
        return QString();
    clientSetup.writeData(allOutCiDi);
    ui.textBrowser_show->append("<font color=\"#008000\"><b>�ɹ��������ϴ���ES�����������...</b></font>");
    ui.textBrowser_show->repaint();
    
    clientSetup.clientSocket->waitForReadyRead(-1);//�ȴ�ES��socket,���û�з���˵��������ʾ�������
    QString recvQstr = clientSetup.readData();

    return recvQstr;
}

bool EDClient::verifyES(QString outResult, QString& CiDiQstr)
{
    QStringList CiDiList;//���α���Ci��Di
    element_t Ci, Di;//���浥��������Ci��DiԪ��
    element_init_G1(Ci, pairing);
    element_init_G1(Di, pairing);

    element_t BV, DV;//��ԭ��2��4��ä���Ե�ֵ
    element_init_G1(BV, pairing);
    element_init_G1(DV, pairing);
    element_set_str(BV, blindPairValue4.at(1).toStdString().c_str(), 10);
    element_set_str(DV, blindPairValue4.at(3).toStdString().c_str(), 10);

    //sub1��Ӧw1^c1,sub2��Ӧu^(d1*x1),sub3��Ӧw2^c2,sub4��Ӧu^(d2*x2),sub5��Ӧg^(A*c1-B),sub6��Ӧg^(C*c2-D)
    element_t sub1, sub2, sub3, sub4, sub5, sub6;
    element_init_G1(sub1, pairing);
    element_init_G1(sub2, pairing);
    element_init_G1(sub3, pairing);
    element_init_G1(sub4, pairing);
    element_init_G1(sub5, pairing);
    element_init_G1(sub6, pairing);

    element_t firstValue, secondValue;//�ֱ��Ӧ��һ���͵ڶ����������������
    element_init_G1(firstValue, pairing);
    element_init_G1(secondValue, pairing);

    element_t CiFirst, CiSecond;//Ci�ĵ�һ�͵ڶ����ݲ���
    element_init_G1(CiFirst, pairing);
    element_init_G1(CiSecond, pairing);

    QStringList powerSub = outResult.split("|");//ÿ��Ԫ�ػ�ԭһ����������
    int index;//iter��Ӧ�±�

    vSignal = true;//��ʼΪtrue
    for (QStringList::iterator iter = powerSub.begin(); iter != powerSub.end(); iter++)
    {
        index = std::distance(powerSub.begin(), iter);
        QStringList elementSub = (*iter).split(";");//elementSub���������ӽṹ
        element_set_str(sub1, elementSub.at(0).toStdString().c_str(), 10);
        element_set_str(sub2, elementSub.at(1).toStdString().c_str(), 10);
        element_set_str(sub3, elementSub.at(2).toStdString().c_str(), 10);
        element_set_str(sub4, elementSub.at(3).toStdString().c_str(), 10);
        element_set_str(sub5, elementSub.at(4).toStdString().c_str(), 10);
        element_set_str(sub6, elementSub.at(5).toStdString().c_str(), 10);

        element_mul(firstValue, BV, sub5);
        element_mul(secondValue, DV, sub6);
        element_mul(firstValue, firstValue, sub1);
        element_mul(secondValue, secondValue, sub3);
        element_mul(firstValue, firstValue, sub2);
        element_mul(secondValue, secondValue, sub4);

        //element_printf("firstValue = %B\n", firstValue);
        //element_printf("secondValue = %B\n", secondValue);

        if (elementToQString(firstValue) == elementToQString(secondValue))//��֤ͨ��,element_t���ͱ���תΪQString���ͽ��бȽϣ��������
        {
            if (index % 3 == 0)//Ci�ĵ�һ����
            {
                element_set(CiFirst, firstValue);//����Ci��һ������
            }
            else if (index % 3 == 1)//Ci�ĵڶ�����
            {
                element_set(CiSecond, firstValue);//����Ci�ĵڶ�������
                element_mul(Ci, CiFirst, CiSecond);//��������Ci
                CiDiList.append(elementToQString(Ci));//��Ci����CiDiQstr
            }
            else//��ǰ�����ΪDi
            {
                element_set(Di, firstValue);//����Di
                CiDiList.append(elementToQString(Di));//��Di����CiDiQstr
            }
        }
        else//��֤��ͨ��
        {
            if (index % 3 != 2)//Ci�ĵ�һ���ݻ�ڶ����ݴ���
            {
                ui.textBrowser_show->append("<font color=\"red\">" + QString("C%1�ĵ�%2������֤ʧ�ܣ�").arg(QString::number((index / 3) + 1), QString::number((index % 3) + 1)) + "</font>");
                ui.textBrowser_show->repaint();
            }
            else//Di��֤����
            {
                ui.textBrowser_show->append(QString("<font color=\"#FF0000\">D%1��֤ʧ��!</font>").arg(QString::number((index / 3) + 1)));
                ui.textBrowser_show->repaint();
            }
            vSignal = false;//��֤����
        }

    }
    CiDiQstr = CiDiList.join(";");//CiDi�ϲ���Qstring����CiDiQstr

    element_clear(Ci);
    element_clear(Di);
    element_clear(BV);
    element_clear(DV);
    element_clear(sub1);
    element_clear(sub2);
    element_clear(sub3);
    element_clear(sub4);
    element_clear(sub5);
    element_clear(sub6);
    element_clear(firstValue);
    element_clear(secondValue);
    element_clear(CiFirst);
    element_clear(CiSecond);

    return vSignal;
}

void EDClient::updateMsgCatalog(QString& msgCatalog)//[0 or 1|FileName;Owner;MsgDesc;MUID|...|...]
{
    ui.tableWidget->setRowCount(0);
    ui.tableWidget->clearContents();
    QStringList subCatalog = msgCatalog.split("|");
    if (subCatalog.at(0) == "0")
        return;

    subCatalog.removeFirst();//ȥ��01��ʶ��
    for (QStringList::iterator iter = subCatalog.begin(); iter != subCatalog.end(); iter++)//����ÿ����Ϣ
    {
        QStringList subContent = (*iter).split(";");
        //qDebug() << "subContent = " << subContent;
        int rowCount = std::distance(subCatalog.begin(), iter); //��ȡ������
        ui.tableWidget->insertRow(rowCount); //��������

        //�½�item
        QTableWidgetItem* item1 = new QTableWidgetItem;//FileName
        QTableWidgetItem* item2 = new QTableWidgetItem;//Owner
        QTableWidgetItem* item3 = new QTableWidgetItem;//FileDesc
        QTableWidgetItem* item4 = new QTableWidgetItem;//MUID

        //����������ʾ��񣺾���
        item1->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        item2->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        item3->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        item4->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

        item1->setText(subContent.at(0));
        item2->setText(subContent.at(1));
        item3->setText(subContent.at(2));
        item4->setText(subContent.at(3));


        //����item
        ui.tableWidget->setItem(rowCount, 0, item1);
        ui.tableWidget->setItem(rowCount, 1, item2);
        ui.tableWidget->setItem(rowCount, 2, item3);
        ui.tableWidget->setItem(rowCount, 3, item4);
    }

}

void EDClient::enableDown()
{
    ui.pushButton_down->setDisabled(false);
    if (ui.tableWidget->currentRow() == -1)//û��ѡ����
        ui.pushButton_down->setDisabled(true);
}

void EDClient::showSSMsgCatalog()
{
    ClientSetup clientSetup("192.168.43.169", "65531");
    clientSetup.writeData(QString("catalog"));

    clientSetup.clientSocket->waitForReadyRead();//�ȴ�SS��socket
    QString recvQstr = clientSetup.readData();//��ȡ��SS���ص���ϢĿ¼[0 or 1|FileName;Owner;MsgDesc;MUID|...|...]
    //qDebug() << "recvSSCatalog = " << recvQstr;

    updateMsgCatalog(recvQstr);
}

void EDClient::on_pushButton_clicked()
{
    showSSMsgCatalog();
}

void EDClient::downMsg()
{
    MUID = ui.tableWidget->item(ui.tableWidget->currentRow(), 3)->text();//��ǰѡ���е�MUID
    QString fileName = ui.tableWidget->item(ui.tableWidget->currentRow(), 0)->text();//��ǰѡ���е��ļ���

    QString sendSS = "down|" + MUID;
    ClientSetup clientSetup("192.168.43.169", "65531");//����SS������

    clientSetup.writeData(sendSS);
    
    clientSetup.clientSocket->waitForReadyRead();

    QString msgBase64 = clientSetup.readData();
    QString rawMsg = msgBase64.toUtf8().fromBase64(msgBase64.toUtf8());//��Base64�����CTתΪQString

    ui.textBrowser_2->setText("<b>�ļ���:</b>");//��fileName��ʾ��textBrowser_2
    ui.textBrowser_2->setText(fileName);
    ui.textBrowser_2->append("<b>����:</b>");//��rawMsg��ʾ��textBrowser_2
    ui.textBrowser_2->append(rawMsg);

    cipher = rawMsg;
}

//���շ���DS�ĸ�ʽ[K;L;subKx|C_1;C1;D1;C2;D2;...;Ci;Di|subTAPM|name|firstPos]subTAPMΪAPM�Ӿ���ת�ú�ľ���(QString��ʽ)
void EDClient::DVCipher()//����SS���ܵ��ľ���Base64������QString[C;C_1;C_2;daw;C1;D1;...;Ci;Di]�����Ͻ��ܷ�����DS���ܲ���֤
{
    ui.textBrowser_3->setText("<font color = \"green\">������KDS��������ѯ���Ƿ���Խ���MUID��Ӧ���ļ�...</font>");
    ui.textBrowser_3->repaint();
    QString keyOrder = isAvail(MUID);//����ʱ��KDS����MUID��ѯ�Ƿ���Խ��ܣ������򷵻ض�Ӧÿ��CiDi��ӦKx��λ����KxOrder[1,3,1,...,3],�Ͷ�ӦAPM������Ӿ���ת�ú�ľ���QString
    //keyOrder[1;KxOrder;subTAPM;firstPos]1������Խ��ܣ�0�����ܽ���[0;������ʾ]
    QStringList keyOrderList = keyOrder.split(";");

    if (keyOrderList.at(0) == "0")//�û����Լ���������ʲ���
    {
        ui.textBrowser_3->append(QString("<font color = \"red\">%1</font>").arg(keyOrderList.at(1)));
        return;
    }
    else if (keyOrderList.at(0) == "1")//�û����Լ�������ʲ���
    {
        QStringList KxOrder = keyOrderList.at(1).split(",");//��ӦKx
        QString subTAPM = keyOrderList.at(2);//subTAPM
        QString firstPos = keyOrderList.at(3);//firstPos

        ui.textBrowser_3->append("<font color = \"green\">�����û���������ʲ��ԣ����Խ��ܴ���Ϣ��</font>");
        ui.textBrowser_3->append("<b>���ν��ܵ���ЧKx��λ��Ϊ:</b>");
        ui.textBrowser_3->append(keyOrderList.at(1));

        ui.textBrowser_3->append("<b>��һ����ЧCiλ��Ϊ:</b>");
        ui.textBrowser_3->append(firstPos);

        ui.textBrowser_3->append("<b>���ν��ܶ�Ӧ��APMת���Ӿ���Ϊ:</b>");
        ui.textBrowser_3->append(subTAPM);

        ui.textBrowser_3->append("<font color = \"green\">����ѡȡ��ЧKx����...</font>");
        ui.textBrowser_3->repaint();
        QString subKx = subKxGen(KxOrder);//����KxOrderѡȡ��Ӧλ�õ�Kx��������ַ���[K1;K2;...;Kx]
        ui.textBrowser_3->append(subKx);
        ui.textBrowser_3->repaint();

        QString sendDS = SK.at(1) + ";";//K
        sendDS += SK.at(2) + ";";//L
        sendDS += subKx + "|";//subKx

        QStringList subCipherList = cipher.split(";");

        sendDS += subCipherList.at(1) + ";";//C_1

        //��ȡCiDi��ɵ�QString[C1;D1;C2;D2;...;Ci;Di]
        int dawPos = subCipherList.indexOf("daw");//����daw�ַ���λ�ã����ڶ�λC_2�Ľ�β
        for (int i = 0; i < dawPos + 1; i++)
            subCipherList.removeFirst();
        QString CiDiQstr = subCipherList.join(";");

        sendDS += CiDiQstr + "|";
        sendDS += subTAPM + "|" + ui.label_name->text() + "|" + firstPos;
        ui.textBrowser_3->append("<font color = \"green\">���շ��͸����ܷ�����(DS)���м���������:</font>");
        ui.textBrowser_3->append("<b>��ʽ��K;L;subKx|C_1;C1;D1;C2;D2;...;Ci;Di|subTAPM|name|firstPos</b>");
        ui.textBrowser_3->append(sendDS);

        ui.textBrowser_3->append("<font color = \"green\">������DS�����м�����...</font>");
        ui.textBrowser_3->repaint();

        ClientSetup clientSetup("192.168.43.169", "65532");//���Ӽ��ܷ�����DS

        clientSetup.writeData(sendDS);

        ui.textBrowser_3->append("<font color = \"green\">���ͳɹ������ڵȴ�DS���г�������...</font>");
        ui.textBrowser_3->repaint();

        clientSetup.clientSocket->waitForReadyRead();

        //[e(g,g)^(alpha*s)]DS���صĽ����GT�е�Ԫ��
        QString DSCompute = clientSetup.readData();

        ui.textBrowser_3->append("<font color = \"green\">�ɹ����յ�DS���صĽ�����Ϣ:</font>");
        ui.textBrowser_3->append(DSCompute);
        ui.textBrowser_3->append("<font color = \"green\">������֤DS����������ȷ��...</font>");
        ui.textBrowser_3->repaint();

        verifyDS(DSCompute);//��֤DS���ؽ������ȷ�Բ�������ܺ������
    }
}

void EDClient::on_pushButton_2_clicked()//���ܷ����Ҫ���ܵ��ļ�չʾ���µ�ȷ����ťʱ������DS���н���
{
    if (cipher.isEmpty())//�û�û��ѡ��Ҫ���ܵ��ļ�
    {
        QMessageBox::critical(this, "����", "��ѡ����Ҫ���ܵ��ļ�");
        return;
    }
    DVCipher();//���ܲ���֤DS���ܽ������ȷ��
}

QString EDClient::subKxGen(QStringList& KxOrder)
{
    QStringList KxRawList = SK.at(3).split(",");
    QStringList KxList;
    QString subKxQstr;//ÿ����Kx�ַ���
    //����ͬKx��";"�ֿ�
    for (QStringList::iterator iter = KxRawList.begin(); iter != KxRawList.end(); iter++)
    {
        int index = std::distance(KxRawList.begin(), iter);
        if (index % 2 == 0)
        {
            subKxQstr += *iter;
        }
        else if (index % 2 == 1)
        {
            subKxQstr += "," + (*iter);
            KxList.append(subKxQstr);
            subKxQstr.clear();
        }
    }
    
    QStringList subKxList;
    for (QStringList::iterator iter = KxOrder.begin(); iter != KxOrder.end(); iter++)
        subKxList.append(KxList.at((*iter).toInt()));

    QString KxQstr = subKxList.join(";");

    return KxQstr;
}

void EDClient::verifyDS(QString& DSCompute)
{
    //QMessageBox::information(this, "verifyDS", DSCompute);

    //ui.textBrowser_3->append("<font color = \"red\">r</font>");
    //ui.textBrowser_3->append(rQstr);

    ui.textBrowser_3->append("<font color = \"red\">��ԭ��r:</font>");
    element_t C, CTZ, r, z;//rΪ����������ܵĽ������õ���
    element_init_GT(C, pairing);
    element_init_GT(CTZ, pairing);
    element_init_GT(r, pairing);
    element_init_Zr(z, pairing);

    QStringList cipherList = cipher.split(";");
    element_set_str(C, cipherList.at(0).toStdString().c_str(), 10);
    element_set_str(z, SK.at(0).toStdString().c_str(), 10);

    element_t DSRet;//DS���ܵĵ���e(g,g)^(s*alpha*(1/z))
    element_init_GT(DSRet, pairing);
    element_set_str(DSRet, DSCompute.toStdString().c_str(), 10);

    element_pow_zn(CTZ, DSRet, z);
    element_div(r, C, CTZ);
    QString rODQstr = elementToQString(r);
    ui.textBrowser_3->append(rODQstr);
    ui.textBrowser_3->append("<font color = \"green\">���ڼ���R[SHA256(r)]...</font>");
    ui.textBrowser_3->repaint();

    //��ȡR����r��Ӧ��sha256��16�����ַ���
    std::string Rstr;//R���SHA256(r)��Ӧ��16���ƹ�ϣ�ַ���
    CryptoPP::SHA256 sha256;
    CryptoPP::StringSource ssA(//��r�еõ���Ӧ�Ĺ�ϣ�ַ�������R
        rODQstr.toStdString(),
        true,
        new CryptoPP::HashFilter(sha256,
            new CryptoPP::HexEncoder(
                new CryptoPP::StringSink(Rstr)
            )
        )
    );
    QString R = QString::fromStdString(Rstr);

    ui.textBrowser_3->append("<b>�����R:</b>");
    ui.textBrowser_3->append(R);
    ui.textBrowser_3->append("<font color = \"green\">���ڼ��㹲������s...</font>");
    ui.textBrowser_3->repaint();


    unsigned char byteArrayR[32];//SHA256��32���ֽ�
    hexStr2Byte(Rstr, byteArrayR);
    //����r��ԭ���ܵ���ϢMsg
    //��ȡC_2
    
    QStringList newC_2List;
    int dawIndex = cipherList.indexOf("daw");

    for (QStringList::iterator iter = cipherList.begin() + 2; iter != cipherList.begin() + dawIndex; iter++)//�ϲ�C_2
        newC_2List.append(*iter);
    QString C_2Qstr = newC_2List.join(";");

    QByteArray cipherByteArray = QByteArray::fromBase64(C_2Qstr.toUtf8());//��ԭʼ����C_2תΪutf�����µ��ֽ���
    QByteArray plainByteArray;//���ܺ������
    plainByteArray.resize(cipherByteArray.size());//�����ڴ�
    //��ÿ���ֽ���ѭ����byteArrayR���ֽ����
    for (QByteArray::iterator iter = cipherByteArray.begin(); iter != cipherByteArray.end(); iter++)
    {
        int index = std::distance(cipherByteArray.begin(), iter);
        plainByteArray[index] = (*iter) ^ byteArrayR[index % 32];
    }
    QString plainText = QString::fromUtf8(plainByteArray);//���ܺ������
    QString cipherText = QString::fromUtf8(cipherByteArray);//����

    qDebug() << "plain text = " << plainText;
    qDebug() << "cipher text = " << cipherByteArray;
    
    //���㹲������s[SHA256(R|m)]
    element_t s;
    element_init_Zr(s, pairing);
    std::string R_M = (R + plainText).toStdString();
    //qDebug() << R + fileContent;
    std::string RMHash;//���R��ԭʼ��Ϣƴ�ӵ�SHA256��16�����ַ���
    CryptoPP::StringSource ssB(
        R_M,
        true,
        new CryptoPP::HashFilter(sha256,
            new CryptoPP::HexEncoder(
                new CryptoPP::StringSink(RMHash)
            )
        )
    );
    //��RMHashӳ�䵽Zr�е�s
    element_from_hash(s, (void*)RMHash.c_str(), RMHash.length());

    ui.textBrowser_3->append("<b>��������s:</b>");
    ui.textBrowser_3->append(elementToQString(s));

    ui.textBrowser_3->append("<font color = \"green\">���ڸ�������������C...</font>");
    ui.textBrowser_3->repaint();


    element_t C_OD;//���������������ԭ��'C',C = r*e(g,g)^(alpha*s)
    element_init_GT(C_OD, pairing);
    element_t e_g_g_alpha;
    element_init_GT(e_g_g_alpha, pairing);
    element_set_str(e_g_g_alpha, PK.at(1).toStdString().c_str(), 10);
    element_t e_g_g_alpha_s;
    element_init_GT(e_g_g_alpha_s, pairing);
    element_pow_zn(e_g_g_alpha_s, e_g_g_alpha, s);
    element_mul(C_OD, r, e_g_g_alpha_s);
    QString C_ODQstr = elementToQString(C_OD);
    QString rawC = cipherList.at(0);
    ui.textBrowser_3->append("<b>���������������C:</b>");
    ui.textBrowser_3->append(C_ODQstr);
    ui.textBrowser_3->append("<b>ԭʼ�����е�C:</b>");
    ui.textBrowser_3->append(rawC);
    ui.textBrowser_3->append("<font color = \"green\">������֤����õ���C��ԭʼ�����е�C�Ƿ����...</font>");



    if (rawC != C_ODQstr)
    {
        ui.textBrowser_3->append("<font color = \"red\">��һ����֤ʧ��!</font>");
        element_clear(C);
        element_clear(CTZ);
        element_clear(r);
        element_clear(z);
        element_clear(DSRet);
        element_clear(s);
        element_clear(C_OD);
        element_clear(e_g_g_alpha);
        element_clear(e_g_g_alpha_s);
        return;
    }

    //�ڶ�����֤[�ж�DS���صĽ����e(g,g)^(alpha*s/z)�Ƿ����]
    ui.textBrowser_3->append("<font color = \"green\">��һ����֤�ɹ������ڽ��еڶ�����֤[�ж�DS���صĽ����e(g,g)^(alpha*s/z)�Ƿ����]...</font>");
    ui.textBrowser_3->repaint();

    element_t z_invert;
    element_init_Zr(z_invert, pairing);
    element_invert(z_invert, z);

    element_t CTCompute;//����õ���e(g,g)^(alpha*s/z)
    element_init_GT(CTCompute, pairing);
    element_pow_zn(CTCompute, e_g_g_alpha_s, z_invert);
    ui.textBrowser_3->append("<b>���������������CT[e(g,g)^(alpha*s/z)]:</b>");
    ui.textBrowser_3->append(elementToQString(CTCompute));
    ui.textBrowser_3->append("<b>DS���ص�CT:</b>");
    ui.textBrowser_3->append(DSCompute);

    if (elementToQString(CTCompute) != DSCompute)
    {
        ui.textBrowser_3->append("<font color = \"red\">�ڶ�����֤ʧ��!</font>");
        element_clear(C);
        element_clear(CTZ);
        element_clear(r);
        element_clear(z);
        element_clear(DSRet);
        element_clear(s);
        element_clear(C_OD);
        element_clear(e_g_g_alpha);
        element_clear(e_g_g_alpha_s);
        element_clear(z_invert);
        element_clear(CTCompute);
        return;
    }

    ui.textBrowser_3->append("<font color = \"green\">�ڶ�����֤�ɹ���������Ϣ����:</font>");
    ui.textBrowser_3->append(plainText);


    element_clear(C);
    element_clear(CTZ);
    element_clear(r);
    element_clear(z);
    element_clear(DSRet);
    element_clear(s);
    element_clear(C_OD);
    element_clear(e_g_g_alpha);
    element_clear(e_g_g_alpha_s);
    element_clear(z_invert);
    element_clear(CTCompute);

}