#include "EDClient.h"
#include "ClientSetup.h"

EDClient::EDClient(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    pairing_init_set_buf(pairing, aTypeStr, strnlen_s(aTypeStr, 400));//为pairing指定类型

    QFont font = ui.tableWidget->horizontalHeader()->font(); //获取表头原来的字体
    font.setBold(true);//字体设置粗体
    ui.tableWidget->horizontalHeader()->setFont(font);
    ui.tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers); //设置不可编辑
    ui.tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}");

    ui.tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);//设置只能选中一行
    ui.tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);//设置选中一行

    ui.pushButton_down->setDisabled(true);//未选择下载消息时禁用

    //connect(this, &EDClient::closeEvent, this, &EDClient::clearLogged);//客户端退出时向服务器发送清理登录信息
    connect(ui.pushButton_browse, SIGNAL(clicked()), this, SLOT(getMsgInfo()));
    connect(ui.pushButton_submitE, SIGNAL(clicked()), this, SLOT(processMsgFile()));
    connect(ui.pushButton_down, SIGNAL(clicked()), this, SLOT(downMsg()));//点击下载按钮从SS服务器下载对应文件(MUID)的Msg的base64编码主体
    connect(ui.tableWidget,SIGNAL(itemSelectionChanged()),this,SLOT(enableDown()));//点击SS文件目录表格时触发判断是否选中某行

}

EDClient::~EDClient()
{
}

void EDClient::closeEvent(QCloseEvent* close)//关闭客户端主窗口时调用
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
    QString sendKDS = "Decry," + ui.textBrowser_cookie->toPlainText() + "," + MUID;//发送给KDS的格式[Decry,cookie,MUID]
    
    clientSetup.writeData(sendKDS);
    clientSetup.clientSocket->waitForReadyRead();
    QString askResult = clientSetup.readData();

    return askResult;
}

void EDClient::displayESRet(QString& outResult)//[6个子结构分号分开|...|...]
{
    QStringList resultList = outResult.split("|");
    for (QStringList::iterator iter = resultList.begin(); iter != resultList.end(); iter++)
    {
        int index = std::distance(resultList.begin(), iter);
        if (index % 3 == 0)//Ci第一部分
            ui.textBrowser_show->append("<font color=\"#008000\"><b>" + QString("C%1第一部分:").arg(QString::number((index / 3) + 1)) + "</b></font>");
        else if (index % 3 == 1)//Ci第二部分
            ui.textBrowser_show->append("<font color=\"#008000\"><b>" + QString("C%1第二部分:").arg(QString::number((index / 3) + 1)) + "</b></font>");
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
    //选择文件对话框/
    QFileDialog* f = new QFileDialog(this);
    f->setWindowTitle("选择需要加密的文件*.txt");
    f->setNameFilter("*.txt");
    f->setViewMode(QFileDialog::Detail);
    f->setDirectoryUrl(QUrl("file:C:\\work\\campus\\Graduation_Project\\Graduation-Project\\code\\"));
    QString filePath;
    if (f->exec() == QDialog::Accepted)
        filePath = f->selectedFiles()[0];

    ui.lineEdit->setText(filePath);
    QFileInfo info(filePath);

    fileName = info.fileName();//文件名

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::warning(this, "失败", "文件打开失败");
        return;
    }
    //读取文件内容
    QTextStream readStream(&file);
    while (!readStream.atEnd())
        fileContent += readStream.readLine();
    //qDebug() << "fileContent = " << fileContent;

    ui.textBrowser->clear();
    ui.textBrowser->append("<b>文件名:</b>");
    ui.textBrowser->append(fileName);
    ui.textBrowser->append("<b>文件内容:</b>");
    ui.textBrowser->append(fileContent);
}

void EDClient::processMsgFile()
{
    //向KDS服务器提交访问策略,KDS服务器返回APMatrix;MUID
    if (ui.textBrowser->toPlainText().isEmpty())//没有选择需要加密的文件
    {
        QMessageBox::warning(this, "warn", "请选择需要加密的文件！");
        return;
    }
    else if (ui.plainTextEdit_2->toPlainText().isEmpty())//没有写文件描述
    {
        QMessageBox::warning(this, "warn", "请为加密的文件添加描述！");
        return;
    }
    else if (ui.plainTextEdit->toPlainText().isEmpty())//没有输入访问策略
    {
        QMessageBox::warning(this, "warn", "输入访问策略！");
        return;
    }
    ui.textBrowser_show->clear();
    //ui.textBrowser_show->clearHistory();
    ui.textBrowser_show->append("<font color=\"#008000\"><b>正在向KDS服务器提交访问策略...</b></font>");
    //ui.textBrowser_show->repaint();
    QString retQstr = getAPMatrixMUID(ui.plainTextEdit->toPlainText());
    QStringList retList = retQstr.split(";");

    ui.textBrowser_show->append("<b>访问策略矩阵:</b>");
    ui.textBrowser_show->append(retList.at(0));
    ui.textBrowser_show->append("<b>MUID:</b>");
    ui.textBrowser_show->append(retList.at(1));
    ui.textBrowser_show->append("<b>HXNUM:</b>");
    ui.textBrowser_show->append(retList.at(2));
    ui.textBrowser_show->repaint();

    hxOrderList = retList.at(2).split(",");//将hx的对应顺序存入hxOrderList
    Eigen::MatrixXd APMatrix = toMatrix(retList.at(0));//将QString类型的访问策略矩阵[1 1\n1 0]格式转为Eigen::MatrixXd类型的矩阵
    
    QString CTMUID = encryAndVerify(APMatrix);//根据APMatrix计算最终密文CT
    CTMUID += ";" + ui.plainTextEdit_2->toPlainText();//文件描述
    CTMUID += ";" + retList.at(1);//MUID
    //此时CTMUID组成:CT;文件描述;MUID
    ui.textBrowser_show->append("<font color=\"#008000\"><b>正在将密文上传到存储服务器...</b></font>");
    ui.textBrowser_show->repaint();
    if(vSignal == true)
        uploadToSS(CTMUID);
    else
        QMessageBox::critical(this, "验证错误", "ES计算结果验证错误!");
}

QString EDClient::getAPMatrixMUID(QString& accessPolicy)
{
    ClientSetup clientSetup("192.168.43.169", "65534");//连接KDS服务器
    QString sendOrRecvQstr = "AP";//发送内容格式AP代表发送的为访问策略,最终发送格式为[AP,accessPolicy,cookie]
    sendOrRecvQstr += ",";
    sendOrRecvQstr += accessPolicy;
    sendOrRecvQstr += ",";
    sendOrRecvQstr += ui.textBrowser_cookie->toPlainText();

    clientSetup.writeData(sendOrRecvQstr);
    clientSetup.clientSocket->waitForReadyRead();//等待KDS读取访问策略
    QString recvQstr = clientSetup.readData();//返回格式:APMatrix;MUID;HXNUM
    return recvQstr;
}

QString EDClient::computeCiDi(Eigen::MatrixXd& APMatrix)
{
    //QMessageBox::warning(this, "warn", "computeCiDi");    
    int rowAPM = APMatrix.rows();
    int colAPM = APMatrix.cols();

    ui.textBrowser_show->append("<font color=\"#008000\"><b>共享秘密s:</b></font>");
    ui.textBrowser_show->append(sQstr);
    ui.textBrowser_show->append("<font color=\"#008000\"><b>正在计算共享秘密份额lambda...</b></font>");
    ui.textBrowser_show->repaint();

    QStringList rList;//存放rowAPM个r
    QStringList lambda;//存放lambda分量

    rGen(rList,rowAPM);//在Zr中随机选择rowAPM个元素r存入rList
    computeLambda(lambda, rowAPM, colAPM, APMatrix);//生成lambda分量并存入lambda

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

    //计算所有CiDi需要的参数[w1;c1;uBase^x1;A*c1-B;d1;w2;c2;uBase^x2;C*c2-D;d2;2个前面格式|重复rowAPM-1次|g]
    QString allOutCiDi;

    ////测试
    //QStringList CiList, DiList;
    //element_t Ci, Di;
    //element_t A1, B1, C1, D1;
    //element_init_G1(Ci, pairing);
    //element_init_G1(Di, pairing);
    //element_init_G1(A1, pairing);
    //element_init_Zr(B1, pairing);
    //element_init_G1(C1, pairing);
    //element_init_Zr(D1, pairing);
    ////测试


    for (int i = 0; i < rowAPM; i++)//计算rowAPM个CiDi对
    {

        ui.textBrowser_show->append("<font color=\"#008000\"><b>" + QString("正在计算外包C%1需要的参数...").arg(QString::number(i + 1)) + "</b></font>");
        ui.textBrowser_show->append("<b>计算第一部分[g^(a*lambda)]...</b>");
        ui.textBrowser_show->repaint();

        element_set_str(uBase, PK.at(2).toStdString().c_str(), 10);
        element_set_str(aIndex, lambda.at(i).toStdString().c_str(), 10);
        allOutCiDi += outPow(uBase, aIndex);
        allOutCiDi += ";";

        ////测试
        //element_set(A1, uBase);
        //element_set(B1, aIndex);
        ////测试

        ui.textBrowser_show->append("<b>计算第二部分[hx^(-r)]...</b>");
        ui.textBrowser_show->repaint();

        element_set_str(uBase, PK.at(3 + hxOrderList.at(i).toInt()).toStdString().c_str(), 10);
        element_set_str(aIndex, rList.at(i).toStdString().c_str(), 10);
        element_neg(aIndex, aIndex);
        allOutCiDi += outPow(uBase, aIndex);
        allOutCiDi += ";";

        ////测试
        //element_set(C1, uBase);
        //element_set(D1, aIndex);
        //element_pow2_zn(Ci, A1, B1, C1, D1);
        //CiList.append(elementToQString(Ci));
        ////测试

        ui.textBrowser_show->append("<font color=\"#008000\"><b>" + QString("正在计算外包D%1需要的参数...").arg(QString::number(i + 1)) + "</b></font>");
        ui.textBrowser_show->repaint();

        element_set_str(uBase, PK.at(0).toStdString().c_str(), 10);
        element_set_str(aIndex, rList.at(i).toStdString().c_str(), 10);
        allOutCiDi += outPow(uBase, aIndex);
        allOutCiDi += "|";
        ui.textBrowser_show->repaint();

        ////测试
        //element_set(A1, uBase);
        //element_set(B1, aIndex);
        //element_pow_zn(Di, A1, B1);
        //DiList.append(elementToQString(Di));
        ////测试
    }

    allOutCiDi += PK.at(0);//在最后添加生成元g
    allOutCiDi += "|";
    allOutCiDi += ui.label_name->text();//最后添加加密者名字

    ////测试
    //qDebug() << "CiList = ";
    //qDebug() << CiList;
    //qDebug() << "DiList = ";
    //qDebug() << DiList
    //qDebug() << "allOutCiDi" << allOutCiDi;
    ////测试

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
        QStringList metaItemList = (*iterRow).split(" ");//每行的元素组成列表
        if (iterRow == rowList.begin())//第一次循环指定destMatrix的大小，为其分配内存
        {
            int colNum = (int)metaItemList.size();
            destMatrix.resize(rowNum, colNum);//指定大小
        }
        for (QStringList::iterator iterCol = metaItemList.begin(); iterCol != metaItemList.end(); iterCol++)
            destMatrix(std::distance(rowList.begin(), iterRow), std::distance(metaItemList.begin(), iterCol)) = (*iterCol).toInt();
    }
    //std::cout << destMatrix << std::endl;
    return destMatrix;
}

QString EDClient::encryAndVerify(Eigen::MatrixXd& APMatrix)
{

    //首先计算C、C_1、C_2，这是密文CT的前三项，完全由加密方完成计算
    ui.textBrowser_show->append("<font color=\"#008000\"><b>正在计算C、C_1、C_2...</b></font>");
    ui.textBrowser_show->repaint();
    QStringList CTList = computeThreeOfCT();//密文CT:C;C_1;C_2
    QString CT;//最终密文
    ui.textBrowser_show->append("<b>C:</b>");
    ui.textBrowser_show->append(CTList.at(0));
    ui.textBrowser_show->append("<b>C_1:</b>");
    ui.textBrowser_show->append(CTList.at(1));
    ui.textBrowser_show->append("<b>C_2:</b>");
    ui.textBrowser_show->append(CTList.at(2));
    ui.textBrowser_show->append("<font color=\"#008000\"><b>正在计算外包计算Ci和Di需要的参数...</b></font>");
    ui.textBrowser_show->repaint();

    //然后计算Ci和Di
    CT = CTList.join(";");//合并成QString,";"隔开

    QString allOutCiDi = computeCiDi(APMatrix);//allOutCiDi存放计算CiDi需要的参数

    ui.textBrowser_show->append("<font color=\"#008000\"><b>正在将外包参数[计算CiDi需要]发送给ES...</b></font>");
    ui.textBrowser_show->repaint();

    //将计算CiDi需要的参数上传给外包加密服务器ES，返回6*3*rowAPM个子结构，3指每个Ci返回2个结果，每个Di返回1个结果，和为3，每个结果包括6个子结构
    QString outResult = sendToES(allOutCiDi);//[w1^c1;u^(d1*x1);w2^c2;u^(d2*x2);g^(A*c1-B);g^(C*c2-D);.;.|...]


    ui.textBrowser_show->append("<font color=\"#008000\"><b><br>ES返回结果:</b></font>");
    ui.textBrowser_show->append(outResult);

    displayESRet(outResult);//显示返回结果

    ui.textBrowser_show->append("<font color=\"#008000\"><b>正在验证ES返回结果的正确性...</b></font>");
    ui.textBrowser_show->repaint();

    QString CiDiQstr;//验证正确存放最终CiDi结果,[C1;D1;C2;D2;...;Ci;Di]
    vSignal = verifyES(outResult, CiDiQstr);//验证正确返回true
    ui.textBrowser_show->append("<font color=\"#008000\"><b><br>验证完成！</b></font>");
    ui.textBrowser_show->repaint();

    QStringList CiDiQstrList = CiDiQstr.split(";"); //[C1;D1;C2;D2;...;Ci;Di]
    ui.textBrowser_show->append("<font color=\"#008000\"><b>CiDi的值如下:</b></font>");

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
    CT += ";daw;";//定位符号，表示消息的结尾
    CT += CiDiQstr;//此时密文CT:C;C_1;C_2;daw;Ci;Di

    ui.textBrowser_show->append("<b>最终密文CT:</b>");
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
    //获取生成元g
    element_t g;
    element_init_G1(g, pairing);
    element_set_str(g, PK.at(0).toStdString().c_str(), 10);

    //计算C
    
    //随机在GT中选择r
    element_t r;
    element_init_GT(r, pairing);
    element_random(r);
    rQstr = elementToQString(r);

    //获取e(g,g)^alpha
    element_t e_g_g_alpha;
    element_init_GT(e_g_g_alpha, pairing);
    element_set_str(e_g_g_alpha, PK.at(1).toStdString().c_str(), 10);

    //获取R，即r对应的sha256的16进制字符串
    std::string Rstr;//R存放SHA256(r)对应的16进制哈希字符串
    CryptoPP::SHA256 sha256;
    CryptoPP::StringSource ssA(//从r中得到对应的哈希字符串存入R
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

    //计算共享秘密s[SHA256(R|m)]
    element_t s;
    element_init_Zr(s, pairing);
    std::string R_M = (R + fileContent).toStdString();
    //qDebug() << R + fileContent;
    std::string RMHash;//存放R和原始消息拼接的SHA256的16进制字符串
    CryptoPP::StringSource ssB(
        R_M,
        true,
        new CryptoPP::HashFilter(sha256,
            new CryptoPP::HexEncoder(
                new CryptoPP::StringSink(RMHash)
            )
        )
    );
    //将RMHash映射到Zr中的s
    element_from_hash(s, (void*)RMHash.c_str(), RMHash.length());
    //保存s
    sQstr = elementToQString(s);

    //计算e(g,g)^(alpha*s)
    element_t e_g_g_alpha_s;
    element_init_GT(e_g_g_alpha_s, pairing);
    element_pow_zn(e_g_g_alpha_s, e_g_g_alpha, s);

    //计算C[r*e(g,g)^(alpha*s)]
    element_mul(C, r, e_g_g_alpha_s);
    
    //element_printf("e(g,g)^(s*alpha) = %B\n", e_g_g_alpha_s);
    //计算C_1[g^s]
    element_pow_zn(C_1, g, s);

    //计算C_2[小段fileContent和R异或]
    unsigned char byteArrayR[32];//SHA256有32个字节
    //const char* ptrR = (const char*)byteArrayR;
    if (!hexStr2Byte(Rstr, byteArrayR))//输入哈希值非法
    {
        QMessageBox::critical(this, "error", "输入哈希值非法！");
        return QStringList();
    }
    //qDebug() << R;
    //qDebug() << QString::fromUtf8(ptrR,32);
    std::cout << Rstr << std::endl;
    QByteArray msgByteArray = fileContent.toUtf8();//将原始消息转为utf编码下的字节流
    QByteArray cipherByteArray;//加密后的密文
    cipherByteArray.resize(msgByteArray.size());//分配内存
    //对每个字节用循环用byteArrayR中字节异或
    for (QByteArray::iterator iter = msgByteArray.begin(); iter != msgByteArray.end(); iter++)
    {
        int index = std::distance(msgByteArray.begin(), iter);
        cipherByteArray[index] = (*iter) ^ byteArrayR[index % 32];
    }

    QByteArray base64C_2 = cipherByteArray.toBase64();

    QString C_2 = QString::fromUtf8(base64C_2);//经过Base64加密后的密文

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
    if (!clientSetup.isConnected)//连接SS服务器失败
        return;
    QString sentSS = "up|" + ui.label_name->text() + ";" + fileName + ";" + CTMUID;//格式化
    clientSetup.writeData(sentSS);//发送上传信息给SS

    clientSetup.clientSocket->waitForReadyRead();//等待SS读socket
    QString recvQstr = clientSetup.readData();//收到SS发来的消息目录[1|FileName;Owner;MsgDesc;MUID|...|...]
    ui.textBrowser_show->append("<font color=\"#008000\"><b>成功将密文上传到存储服务器,正在更新SS消息目录...</b></font>");
    //qDebug() << "recvQstr = " << recvQstr;
    updateMsgCatalog(recvQstr);//更新SS存储的消息目录
}

void EDClient::clearLogged()
{
    //QMessageBox::information(this, "clear Logged", "exit");
    ClientSetup clientSetup("192.168.43.169", "65534");         //退出时连接KDS                          //连接KDS服务器
    QString sendOrRecvQstr = "exit,";                           //exit表示用户退出
    sendOrRecvQstr += ui.label_name->text();                    //用户名
    sendOrRecvQstr += ",";
    sendOrRecvQstr += ui.textBrowser_cookie->toPlainText();     //用户临时cookie
    //qDebug() << sendOrRecvQstr;
    clientSetup.clientSocket->waitForConnected();               //等待和KDS建立连接
    //QMessageBox::information(this, "success", "connect to KDS");
    clientSetup.writeData(sendOrRecvQstr);                      //发送sendOrRecvQstr给KDS服务器
    clientSetup.clientSocket->waitForDisconnected();            //等待KDS全部接受完socket信息
}

//格式:用户名;密码;z;K;L;Kx;cookie;S;g;e(g,g)^alpha;g^a;hx
void EDClient::showLoggedUserInfo(QString& recvUserLoggedInfo)
{
    QStringList userInfo = recvUserLoggedInfo.split(";");
    QString subShow;//子显示字符串
    //qDebug() << userInfo;

    //显示用户名
    ui.label_name->setText(userInfo.at(0));
    ui.label_name->setWordWrap(true);
    
    //显示密码
    ui.label_passwd->setText(userInfo.at(1));
    ui.label_passwd->setWordWrap(true);
    
    //显示系统参数PK
    subShow = "<b>g:</b>" + userInfo.at(8);
    ui.textBrowser_PK->append(subShow);
    subShow = "<b>e(g,g)^alpha:</b>" + userInfo.at(9);
    ui.textBrowser_PK->append(subShow);
    subShow = "<b>g^a:</b>" + userInfo.at(10);
    ui.textBrowser_PK->append(subShow);
    subShow = "<b>hx:</b>";
    ui.textBrowser_PK->append(subShow);
    //将PK存入QStringList变量PK中
    PK.append(userInfo.at(8));
    PK.append(userInfo.at(9));
    PK.append(userInfo.at(10));
    for (QStringList::iterator iter = userInfo.begin() + 11; iter != userInfo.end(); iter++)//将每个hx拼到PK后面
    {
        PK.append(*iter);
        ui.textBrowser_PK->append(*iter);
    }
    //QMessageBox::information(this, "daw", "ready to show user info");

    //显示用户私钥[z;K;L;Kx]
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

    //显示用户临时cookie
    ui.textBrowser_cookie->setText(userInfo.at(6));
    
    //显示用户属性集S
    ui.label_S->setText(userInfo.at(7));
    ui.label_S->setWordWrap(true);

    blindPairGen4();//随机生成4个盲化对blindPairIndex4

    //显示四个随机盲化对
    subShow = blindPairIndex4.at(0) + ":" + blindPairValue4.at(0) + "\n";
    ui.textBrowser_blind->append(subShow);
    subShow = blindPairIndex4.at(1) + ":" + blindPairValue4.at(1) + "\n";
    ui.textBrowser_blind->append(subShow);
    subShow = blindPairIndex4.at(2) + ":" + blindPairValue4.at(2) + "\n";
    ui.textBrowser_blind->append(subShow);
    subShow = blindPairIndex4.at(3) + ":" + blindPairValue4.at(3) + "\n";
    ui.textBrowser_blind->append(subShow);

    //ui.textBrowser_cookie->setFixedHeight(ui.textBrowser_cookie->document()->size().height()+2);//调整cookie显示页大小
}

QString EDClient::byteToHexStr(unsigned char byte_arr[], int arr_len)
{
    //std::string* hexstr = new std::string();
    QString hexstr;
    for (int i = 0; i < arr_len; i++)
    {
        char hex1;
        char hex2;
        /*借助C++支持的unsigned和int的强制转换，把unsigned char赋值给int的值，那么系统就会自动完成强制转换*/
        int value = byte_arr[i];
        int S = value / 16;
        int Y = value % 16;
        //将C++中unsigned char和int的强制转换得到的商转成字母
        if (S >= 0 && S <= 9)
            hex1 = (char)(48 + S);
        else
            hex1 = (char)(55 + S);
        //将C++中unsigned char和int的强制转换得到的余数转成字母
        if (Y >= 0 && Y <= 9)
            hex2 = (char)(48 + Y);
        else
            hex2 = (char)(55 + Y);
        //最后一步的代码实现，将所得到的两个字母连接成字符串达到目的
        hexstr = hexstr + hex1 + hex2;
    }
    return hexstr;
}

QString EDClient::elementToQString(element_t point)
{
    char* ourQStr = (char*)calloc(350, 1);//初始化
    element_snprint(ourQStr, 350, point);//将point转为char*存入ourQStr
    return QString(ourQStr);
}

bool EDClient::hexStr2Byte(std::string hexStr, unsigned char byteArray[])//将64长度的hex字符串转为32字节的数组，返回false表示输入的hex字符串不合法
{
    for (int i = 0; i < 32; i++)
    {
        int j = 2 * i;//字节高位
        int firstValue = 0;
        int secondValue = 0;
        if (hexStr[j] >= '0' && hexStr[j] <= '9')//计算高位值
            firstValue = 16 * (hexStr[j] - '0');
        else if (hexStr[j] >= 'A' && hexStr[j] <= 'F')
            firstValue = 16 * (hexStr[j] - 'A' + 10);
        else if (hexStr[j] >= 'a' && hexStr[j] <= 'f')
            firstValue = 16 * (hexStr[j] - 'a' + 10);
        else
            return false;//不合法

        if (hexStr[j + 1] >= '0' && hexStr[j + 1] <= '9') // 计算低位值
            secondValue = hexStr[j + 1] - '0';
        else if (hexStr[j + 1] >= 'A' && hexStr[j + 1] <= 'F')
            secondValue = hexStr[j + 1] - 'A' + 10;
        else if (hexStr[j + 1] >= 'a' && hexStr[j + 1] <= 'f')
            secondValue = hexStr[j + 1] - 'a' + 10;
        else
            return false;//不合法
        byteArray[i] = firstValue + secondValue;
    }

    return true;//成功
}

QString EDClient::outPow(element_t uBase, element_t aIndex)//底数u指数a，外包盲化计算u^a
{
    QString resultQstr;//返回的结果存入QString中[w1;c1;uBase^x1;A*c1-B;d1;w2;c2;uBase^x2;C*c2-D;d2],此结果直接发给ES用于完成一次外包指数运算
    QString showQstr;//显示到界面的字符串
    element_t g;//生成元
    element_init_G1(g, pairing);
    element_set_str(g, PK.at(0).toStdString().c_str(), 10);

    //还原随机盲化对
    element_t A, B, C, D, AV, BV, CV, DV;//ABCD依次对应随机盲化对指数、AV对应g^A,以此类推
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


    //计算w1(uBase/g^A),A指第一个盲化对的指数[盲化底数uBase]
    element_t w1;
    element_init_G1(w1, pairing);
    element_div(w1, uBase, AV);
    showQstr = elementToQString(w1);
    resultQstr = showQstr + ";";
    ui.textBrowser_show->append("<b>w1:</b>" + showQstr);
    //ui.textBrowser_show->repaint();

    //计算c1(aIndex-d1*x1)[盲化指数aIndex]
    element_t d1, x1;//随机选择Zr中的元素
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

    //计算uBase^x1
    element_t u_x1;
    element_init_G1(u_x1, pairing);
    element_pow_zn(u_x1, uBase, x1);
    showQstr = elementToQString(u_x1);
    resultQstr += showQstr + ";";
    ui.textBrowser_show->append("<b>u_x1:</b>" + showQstr);
    //ui.textBrowser_show->repaint();

    //计算A*c1-B，A、B分别为前两个随机盲化对的指数
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

    //d1添加到resultQstr
    showQstr = elementToQString(d1);
    resultQstr += showQstr + ";";
    ui.textBrowser_show->append("<b>d1:</b>" + showQstr);


    //计算w2(uBase/g^C),C指第三个盲化对的指数[盲化底数uBase]
    element_t w2;
    element_init_G1(w2, pairing);
    element_div(w2, uBase, CV);
    showQstr = elementToQString(w2);
    resultQstr += showQstr + ";";
    ui.textBrowser_show->append("<b>w2:</b>" + showQstr);
    //ui.textBrowser_show->repaint();

    //计算c2(aIndex-d2*x2)[盲化指数aIndex]
    element_t d2, x2;//随机选择Zr中的元素
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

    //计算uBase^x2
    element_t u_x2;
    element_init_G1(u_x2, pairing);
    element_pow_zn(u_x2, uBase, x2);
    showQstr = elementToQString(u_x2);
    resultQstr += showQstr + ";";
    ui.textBrowser_show->append("<b>u_x2:</b>" + showQstr);
    //ui.textBrowser_show->repaint();

    //计算C*c2-D，C、D分别为后两个随机盲化对的指数
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

    //d2添加到resultQstr
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
    element_t g;//生成元，用于生成盲化对
    element_init_G1(g, pairing);
    element_set_str(g, PK.at(0).toStdString().c_str(), 10);

    element_t blindIndexA, blindIndexB, blindIndexC, blindIndexD;//生成盲化对的指数
    element_t blindA, blindB, blindC, blindD;//加密方程序运行时生成[永久]随机盲化对即blindA=g^blindIndexA
    element_init_Zr(blindIndexA, pairing);
    element_init_Zr(blindIndexB, pairing);
    element_init_Zr(blindIndexC, pairing);
    element_init_Zr(blindIndexD, pairing);
    element_init_G1(blindA, pairing);
    element_init_G1(blindB, pairing);
    element_init_G1(blindC, pairing);
    element_init_G1(blindD, pairing);

    //随机选择指数
    element_random(blindIndexA);
    element_random(blindIndexB);
    element_random(blindIndexC);
    element_random(blindIndexD);

    //盲化对计算
    element_pow_zn(blindA, g, blindIndexA);
    element_pow_zn(blindB, g, blindIndexB);
    element_pow_zn(blindC, g, blindIndexC);
    element_pow_zn(blindD, g, blindIndexD);

    //将指数保存到blindPairIndex4中
    blindPairIndex4.append(elementToQString(blindIndexA));
    blindPairIndex4.append(elementToQString(blindIndexB));
    blindPairIndex4.append(elementToQString(blindIndexC));
    blindPairIndex4.append(elementToQString(blindIndexD));

    //将计算结果保存到blindPairValue4中
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

    QStringList yList;//存放colAPM-1个y
    yList.append(sQstr);
    //随机选择n-1个Zr中的元素作为秘密分享列向量的除s之外的其他分量y
    for (int i = 0; i < colAPM - 1; i++)
    {
        element_random(y);
        yList.append(elementToQString(y));
    }

    element_t temp;//temp为和矩阵进行运算的中间元素,共享向量中的元素
    element_init_Zr(temp, pairing);
    element_t tempM;//APM矩阵中的元素
    element_init_Zr(tempM, pairing);
    element_t subLambda;//存放计算的lambda值
    element_init_Zr(subLambda, pairing);
    element_t tempMul;//存放APM元素和秘密分享向量元素相乘的结果
    element_init_Zr(tempMul, pairing);

    //计算lambda共rowAPM个
    for (int i = 0; i < rowAPM; i++)
    {
        element_set0(subLambda);//每次计算新的lambda时设为0
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
    if (!clientSetup.isConnected)//连接ES服务器失败
        return QString();
    clientSetup.writeData(allOutCiDi);
    ui.textBrowser_show->append("<font color=\"#008000\"><b>成功将参数上传到ES，外包加密中...</b></font>");
    ui.textBrowser_show->repaint();
    
    clientSetup.clientSocket->waitForReadyRead(-1);//等待ES读socket,如果没有返回说明正在演示计算出错
    QString recvQstr = clientSetup.readData();

    return recvQstr;
}

bool EDClient::verifyES(QString outResult, QString& CiDiQstr)
{
    QStringList CiDiList;//依次保存Ci，Di
    element_t Ci, Di;//保存单个完整的Ci和Di元素
    element_init_G1(Ci, pairing);
    element_init_G1(Di, pairing);

    element_t BV, DV;//还原第2、4个盲化对的值
    element_init_G1(BV, pairing);
    element_init_G1(DV, pairing);
    element_set_str(BV, blindPairValue4.at(1).toStdString().c_str(), 10);
    element_set_str(DV, blindPairValue4.at(3).toStdString().c_str(), 10);

    //sub1对应w1^c1,sub2对应u^(d1*x1),sub3对应w2^c2,sub4对应u^(d2*x2),sub5对应g^(A*c1-B),sub6对应g^(C*c2-D)
    element_t sub1, sub2, sub3, sub4, sub5, sub6;
    element_init_G1(sub1, pairing);
    element_init_G1(sub2, pairing);
    element_init_G1(sub3, pairing);
    element_init_G1(sub4, pairing);
    element_init_G1(sub5, pairing);
    element_init_G1(sub6, pairing);

    element_t firstValue, secondValue;//分别对应第一个和第二个计算的幂运算结果
    element_init_G1(firstValue, pairing);
    element_init_G1(secondValue, pairing);

    element_t CiFirst, CiSecond;//Ci的第一和第二个幂部分
    element_init_G1(CiFirst, pairing);
    element_init_G1(CiSecond, pairing);

    QStringList powerSub = outResult.split("|");//每个元素还原一个幂运算结果
    int index;//iter对应下标

    vSignal = true;//初始为true
    for (QStringList::iterator iter = powerSub.begin(); iter != powerSub.end(); iter++)
    {
        index = std::distance(powerSub.begin(), iter);
        QStringList elementSub = (*iter).split(";");//elementSub包含六个子结构
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

        if (elementToQString(firstValue) == elementToQString(secondValue))//验证通过,element_t类型必须转为QString类型进行比较，否则不相等
        {
            if (index % 3 == 0)//Ci的第一个幂
            {
                element_set(CiFirst, firstValue);//保存Ci第一部分幂
            }
            else if (index % 3 == 1)//Ci的第二个幂
            {
                element_set(CiSecond, firstValue);//保存Ci的第二部分幂
                element_mul(Ci, CiFirst, CiSecond);//计算最终Ci
                CiDiList.append(elementToQString(Ci));//将Ci存入CiDiQstr
            }
            else//当前计算的为Di
            {
                element_set(Di, firstValue);//保存Di
                CiDiList.append(elementToQString(Di));//将Di存入CiDiQstr
            }
        }
        else//验证不通过
        {
            if (index % 3 != 2)//Ci的第一个幂或第二个幂错误
            {
                ui.textBrowser_show->append("<font color=\"red\">" + QString("C%1的第%2部分验证失败！").arg(QString::number((index / 3) + 1), QString::number((index % 3) + 1)) + "</font>");
                ui.textBrowser_show->repaint();
            }
            else//Di验证出错
            {
                ui.textBrowser_show->append(QString("<font color=\"#FF0000\">D%1验证失败!</font>").arg(QString::number((index / 3) + 1)));
                ui.textBrowser_show->repaint();
            }
            vSignal = false;//验证出错
        }

    }
    CiDiQstr = CiDiList.join(";");//CiDi合并成Qstring存入CiDiQstr

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

    subCatalog.removeFirst();//去掉01标识符
    for (QStringList::iterator iter = subCatalog.begin(); iter != subCatalog.end(); iter++)//遍历每个消息
    {
        QStringList subContent = (*iter).split(";");
        //qDebug() << "subContent = " << subContent;
        int rowCount = std::distance(subCatalog.begin(), iter); //获取表单行数
        ui.tableWidget->insertRow(rowCount); //插入新行

        //新建item
        QTableWidgetItem* item1 = new QTableWidgetItem;//FileName
        QTableWidgetItem* item2 = new QTableWidgetItem;//Owner
        QTableWidgetItem* item3 = new QTableWidgetItem;//FileDesc
        QTableWidgetItem* item4 = new QTableWidgetItem;//MUID

        //设置字体显示风格：居中
        item1->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        item2->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        item3->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        item4->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

        item1->setText(subContent.at(0));
        item2->setText(subContent.at(1));
        item3->setText(subContent.at(2));
        item4->setText(subContent.at(3));


        //设置item
        ui.tableWidget->setItem(rowCount, 0, item1);
        ui.tableWidget->setItem(rowCount, 1, item2);
        ui.tableWidget->setItem(rowCount, 2, item3);
        ui.tableWidget->setItem(rowCount, 3, item4);
    }

}

void EDClient::enableDown()
{
    ui.pushButton_down->setDisabled(false);
    if (ui.tableWidget->currentRow() == -1)//没有选中行
        ui.pushButton_down->setDisabled(true);
}

void EDClient::showSSMsgCatalog()
{
    ClientSetup clientSetup("192.168.43.169", "65531");
    clientSetup.writeData(QString("catalog"));

    clientSetup.clientSocket->waitForReadyRead();//等待SS读socket
    QString recvQstr = clientSetup.readData();//读取到SS返回的消息目录[0 or 1|FileName;Owner;MsgDesc;MUID|...|...]
    //qDebug() << "recvSSCatalog = " << recvQstr;

    updateMsgCatalog(recvQstr);
}

void EDClient::on_pushButton_clicked()
{
    showSSMsgCatalog();
}

void EDClient::downMsg()
{
    MUID = ui.tableWidget->item(ui.tableWidget->currentRow(), 3)->text();//当前选择行的MUID
    QString fileName = ui.tableWidget->item(ui.tableWidget->currentRow(), 0)->text();//当前选择行的文件名

    QString sendSS = "down|" + MUID;
    ClientSetup clientSetup("192.168.43.169", "65531");//连接SS服务器

    clientSetup.writeData(sendSS);
    
    clientSetup.clientSocket->waitForReadyRead();

    QString msgBase64 = clientSetup.readData();
    QString rawMsg = msgBase64.toUtf8().fromBase64(msgBase64.toUtf8());//将Base64编码的CT转为QString

    ui.textBrowser_2->setText("<b>文件名:</b>");//将fileName显示在textBrowser_2
    ui.textBrowser_2->setText(fileName);
    ui.textBrowser_2->append("<b>密文:</b>");//将rawMsg显示在textBrowser_2
    ui.textBrowser_2->append(rawMsg);

    cipher = rawMsg;
}

//最终发给DS的格式[K;L;subKx|C_1;C1;D1;C2;D2;...;Ci;Di|subTAPM|name|firstPos]subTAPM为APM子矩阵转置后的矩阵(QString格式)
void EDClient::DVCipher()//将从SS接受到的经过Base64解码后的QString[C;C_1;C_2;daw;C1;D1;...;Ci;Di]，联合解密服务器DS解密并验证
{
    ui.textBrowser_3->setText("<font color = \"green\">正在向KDS服务器查询您是否可以解密MUID对应的文件...</font>");
    ui.textBrowser_3->repaint();
    QString keyOrder = isAvail(MUID);//解密时向KDS发送MUID查询是否可以解密，可以则返回对应每个CiDi对应Kx的位置如KxOrder[1,3,1,...,3],和对应APM矩阵的子矩阵转置后的矩阵QString
    //keyOrder[1;KxOrder;subTAPM;firstPos]1代表可以解密，0代表不能解密[0;错误提示]
    QStringList keyOrderList = keyOrder.split(";");

    if (keyOrderList.at(0) == "0")//用户属性集不满足访问策略
    {
        ui.textBrowser_3->append(QString("<font color = \"red\">%1</font>").arg(keyOrderList.at(1)));
        return;
    }
    else if (keyOrderList.at(0) == "1")//用户属性集满足访问策略
    {
        QStringList KxOrder = keyOrderList.at(1).split(",");//对应Kx
        QString subTAPM = keyOrderList.at(2);//subTAPM
        QString firstPos = keyOrderList.at(3);//firstPos

        ui.textBrowser_3->append("<font color = \"green\">您的用户集满足访问策略，可以解密此消息！</font>");
        ui.textBrowser_3->append("<b>本次解密的有效Kx的位置为:</b>");
        ui.textBrowser_3->append(keyOrderList.at(1));

        ui.textBrowser_3->append("<b>第一个有效Ci位置为:</b>");
        ui.textBrowser_3->append(firstPos);

        ui.textBrowser_3->append("<b>本次解密对应的APM转置子矩阵为:</b>");
        ui.textBrowser_3->append(subTAPM);

        ui.textBrowser_3->append("<font color = \"green\">正在选取有效Kx序列...</font>");
        ui.textBrowser_3->repaint();
        QString subKx = subKxGen(KxOrder);//根据KxOrder选取对应位置的Kx组成序列字符串[K1;K2;...;Kx]
        ui.textBrowser_3->append(subKx);
        ui.textBrowser_3->repaint();

        QString sendDS = SK.at(1) + ";";//K
        sendDS += SK.at(2) + ";";//L
        sendDS += subKx + "|";//subKx

        QStringList subCipherList = cipher.split(";");

        sendDS += subCipherList.at(1) + ";";//C_1

        //获取CiDi组成的QString[C1;D1;C2;D2;...;Ci;Di]
        int dawPos = subCipherList.indexOf("daw");//返回daw字符串位置，用于定位C_2的结尾
        for (int i = 0; i < dawPos + 1; i++)
            subCipherList.removeFirst();
        QString CiDiQstr = subCipherList.join(";");

        sendDS += CiDiQstr + "|";
        sendDS += subTAPM + "|" + ui.label_name->text() + "|" + firstPos;
        ui.textBrowser_3->append("<font color = \"green\">最终发送给解密服务器(DS)的中间密文如下:</font>");
        ui.textBrowser_3->append("<b>格式：K;L;subKx|C_1;C1;D1;C2;D2;...;Ci;Di|subTAPM|name|firstPos</b>");
        ui.textBrowser_3->append(sendDS);

        ui.textBrowser_3->append("<font color = \"green\">正在向DS发送中间密文...</font>");
        ui.textBrowser_3->repaint();

        ClientSetup clientSetup("192.168.43.169", "65532");//连接加密服务器DS

        clientSetup.writeData(sendDS);

        ui.textBrowser_3->append("<font color = \"green\">发送成功，正在等待DS进行初步解密...</font>");
        ui.textBrowser_3->repaint();

        clientSetup.clientSocket->waitForReadyRead();

        //[e(g,g)^(alpha*s)]DS返回的结果，GT中的元素
        QString DSCompute = clientSetup.readData();

        ui.textBrowser_3->append("<font color = \"green\">成功接收到DS返回的解密信息:</font>");
        ui.textBrowser_3->append(DSCompute);
        ui.textBrowser_3->append("<font color = \"green\">正在验证DS计算结果的正确性...</font>");
        ui.textBrowser_3->repaint();

        verifyDS(DSCompute);//验证DS返回结果的正确性并输出解密后的明文
    }
}

void EDClient::on_pushButton_2_clicked()//解密方点击要解密的文件展示栏下的确定按钮时，联合DS进行解密
{
    if (cipher.isEmpty())//用户没有选择要解密的文件
    {
        QMessageBox::critical(this, "错误", "请选择需要解密的文件");
        return;
    }
    DVCipher();//解密并验证DS解密结果的正确性
}

QString EDClient::subKxGen(QStringList& KxOrder)
{
    QStringList KxRawList = SK.at(3).split(",");
    QStringList KxList;
    QString subKxQstr;//每个子Kx字符串
    //将不同Kx按";"分开
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

    ui.textBrowser_3->append("<font color = \"red\">还原的r:</font>");
    element_t C, CTZ, r, z;//r为根据外包解密的结果计算得到的
    element_init_GT(C, pairing);
    element_init_GT(CTZ, pairing);
    element_init_GT(r, pairing);
    element_init_Zr(z, pairing);

    QStringList cipherList = cipher.split(";");
    element_set_str(C, cipherList.at(0).toStdString().c_str(), 10);
    element_set_str(z, SK.at(0).toStdString().c_str(), 10);

    element_t DSRet;//DS解密的到的e(g,g)^(s*alpha*(1/z))
    element_init_GT(DSRet, pairing);
    element_set_str(DSRet, DSCompute.toStdString().c_str(), 10);

    element_pow_zn(CTZ, DSRet, z);
    element_div(r, C, CTZ);
    QString rODQstr = elementToQString(r);
    ui.textBrowser_3->append(rODQstr);
    ui.textBrowser_3->append("<font color = \"green\">正在计算R[SHA256(r)]...</font>");
    ui.textBrowser_3->repaint();

    //获取R，即r对应的sha256的16进制字符串
    std::string Rstr;//R存放SHA256(r)对应的16进制哈希字符串
    CryptoPP::SHA256 sha256;
    CryptoPP::StringSource ssA(//从r中得到对应的哈希字符串存入R
        rODQstr.toStdString(),
        true,
        new CryptoPP::HashFilter(sha256,
            new CryptoPP::HexEncoder(
                new CryptoPP::StringSink(Rstr)
            )
        )
    );
    QString R = QString::fromStdString(Rstr);

    ui.textBrowser_3->append("<b>计算的R:</b>");
    ui.textBrowser_3->append(R);
    ui.textBrowser_3->append("<font color = \"green\">正在计算共享秘密s...</font>");
    ui.textBrowser_3->repaint();


    unsigned char byteArrayR[32];//SHA256有32个字节
    hexStr2Byte(Rstr, byteArrayR);
    //根据r还原加密的消息Msg
    //提取C_2
    
    QStringList newC_2List;
    int dawIndex = cipherList.indexOf("daw");

    for (QStringList::iterator iter = cipherList.begin() + 2; iter != cipherList.begin() + dawIndex; iter++)//合并C_2
        newC_2List.append(*iter);
    QString C_2Qstr = newC_2List.join(";");

    QByteArray cipherByteArray = QByteArray::fromBase64(C_2Qstr.toUtf8());//将原始密文C_2转为utf编码下的字节流
    QByteArray plainByteArray;//解密后的明文
    plainByteArray.resize(cipherByteArray.size());//分配内存
    //对每个字节用循环用byteArrayR中字节异或
    for (QByteArray::iterator iter = cipherByteArray.begin(); iter != cipherByteArray.end(); iter++)
    {
        int index = std::distance(cipherByteArray.begin(), iter);
        plainByteArray[index] = (*iter) ^ byteArrayR[index % 32];
    }
    QString plainText = QString::fromUtf8(plainByteArray);//解密后的明文
    QString cipherText = QString::fromUtf8(cipherByteArray);//密文

    qDebug() << "plain text = " << plainText;
    qDebug() << "cipher text = " << cipherByteArray;
    
    //计算共享秘密s[SHA256(R|m)]
    element_t s;
    element_init_Zr(s, pairing);
    std::string R_M = (R + plainText).toStdString();
    //qDebug() << R + fileContent;
    std::string RMHash;//存放R和原始消息拼接的SHA256的16进制字符串
    CryptoPP::StringSource ssB(
        R_M,
        true,
        new CryptoPP::HashFilter(sha256,
            new CryptoPP::HexEncoder(
                new CryptoPP::StringSink(RMHash)
            )
        )
    );
    //将RMHash映射到Zr中的s
    element_from_hash(s, (void*)RMHash.c_str(), RMHash.length());

    ui.textBrowser_3->append("<b>共享秘密s:</b>");
    ui.textBrowser_3->append(elementToQString(s));

    ui.textBrowser_3->append("<font color = \"green\">正在根据外包结果计算C...</font>");
    ui.textBrowser_3->repaint();


    element_t C_OD;//根据外包计算结果还原的'C',C = r*e(g,g)^(alpha*s)
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
    ui.textBrowser_3->append("<b>根据外包结果计算的C:</b>");
    ui.textBrowser_3->append(C_ODQstr);
    ui.textBrowser_3->append("<b>原始密文中的C:</b>");
    ui.textBrowser_3->append(rawC);
    ui.textBrowser_3->append("<font color = \"green\">正在验证计算得到的C和原始密文中的C是否相等...</font>");



    if (rawC != C_ODQstr)
    {
        ui.textBrowser_3->append("<font color = \"red\">第一次验证失败!</font>");
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

    //第二次验证[判断DS返回的结果和e(g,g)^(alpha*s/z)是否相等]
    ui.textBrowser_3->append("<font color = \"green\">第一次验证成功，正在进行第二次验证[判断DS返回的结果和e(g,g)^(alpha*s/z)是否相等]...</font>");
    ui.textBrowser_3->repaint();

    element_t z_invert;
    element_init_Zr(z_invert, pairing);
    element_invert(z_invert, z);

    element_t CTCompute;//计算得到的e(g,g)^(alpha*s/z)
    element_init_GT(CTCompute, pairing);
    element_pow_zn(CTCompute, e_g_g_alpha_s, z_invert);
    ui.textBrowser_3->append("<b>根据外包结果计算的CT[e(g,g)^(alpha*s/z)]:</b>");
    ui.textBrowser_3->append(elementToQString(CTCompute));
    ui.textBrowser_3->append("<b>DS返回的CT:</b>");
    ui.textBrowser_3->append(DSCompute);

    if (elementToQString(CTCompute) != DSCompute)
    {
        ui.textBrowser_3->append("<font color = \"red\">第二次验证失败!</font>");
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

    ui.textBrowser_3->append("<font color = \"green\">第二次验证成功，明文消息如下:</font>");
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