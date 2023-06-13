#include "login.h"
#include "ui_login.h"
#include <QPainter>
#include <QRegExp>
#include <QMessageBox>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QFile>

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    // 去边框
    this->setWindowFlags(Qt::FramelessWindowHint | windowFlags());

    // 给titbar对象设置父亲
    ui->myToolBar->setMyParent(this);

    // 处理接受的titlebar的信号
    connect(ui->myToolBar, &MyTitleBar::showSetWindow, [=]()
    {
        ui->stackedWidget->setCurrentWidget(ui->setPage);
    });
    connect(ui->myToolBar, &MyTitleBar::showMinWindow, [=]()
    {
        // 窗口最小化
        this->showMinimized();
    });
    connect(ui->myToolBar, &MyTitleBar::closeMyWindow, [=]()
    {
        if(ui->stackedWidget->currentWidget() == ui->setPage)
        {
            ui->stackedWidget->setCurrentIndex(0);  // 登录窗口
            // 清空控件中的用户数据
        }
        else if(ui->stackedWidget->currentWidget() == ui->regPage)
        {
            ui->stackedWidget->setCurrentIndex(0);  // 登录窗口
            // 清空控件中的用户数据
        }
        else
        {
            this->close();
        }
    });

    // 设置样式表
    QFile file("d:\\mytest.qss");
    file.open(QFile::ReadOnly);
    QByteArray all = file.readAll();
    file.close();
    qApp->setStyleSheet(all);
}

Login::~Login()
{
    delete ui;
}

void Login::paintEvent(QPaintEvent *event)
{
    // 画背景图的操作
//    QPainter p(this);   // 绘图设备为当前窗口
//    p.drawPixmap(0, 0, this->width(), this->height(), QPixmap(":/images/login_bk.jpg"));
}

void Login::on_regAccount_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


//void Login::on_regButton_clicked()
//{
//    // 处理的动作
//    // 1. 从控件中取出用户输入的数据
//    QString userName = ui->reg_userName->text();
//    QString nickName = ui->reg_NickName->text();
//    QString passwd = ui->reg_passwd->text();
//    QString confirmPwd = ui->reg_confirmPwd->text();
//    QString email = ui->reg_mail->text();
//    QString phone = ui->reg_phone->text();
//    // 2. 数据校验
//    QRegExp regexp;
//    // 校验用户名,密码
//    QString USER_REG   = "^[a-zA-Z0-9_@#-\\*]\\{3,16\\}$";
//    regexp.setPattern(USER_REG);
//    bool bl = regexp.exactMatch(userName);
//    if(bl == false)
//    {
//        QMessageBox::warning(this, "ERROR", "用户名格式不正确!");
//        return;
//    }
//    // regexp.setPattern();
//    // 3. 用户信息发送给服务器
//    //  - 如何发送: 使用http协议发送, 使用post方式
//    //  - 数据格式: json对象
//    QNetworkAccessManager* pManager = new QNetworkAccessManager(this);
//    QNetworkRequest request;
//    QString url = QString("http://%1:%2/reg").arg(ui->ip->text()).arg(ui->port->text());
//    request.setUrl(url);
//    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");    // 描述post数据的格式
//    // 将用户提交的数据拼接成功json对象字符串
//    /*
//        {
//            userName:xxxx,
//            nickName:xxx,
//            firstPwd:xxx,
//            phone:xxx,
//            email:xxx
//        }
//    */
//    QJsonObject obj;
//    // insert(const QString &key, const QJsonValue &value)
//    obj.insert("userName", userName); // QJsonValue(userName)
//    obj.insert("nickName", nickName);
//    obj.insert("firstPwd", passwd);
//    obj.insert("phone", phone);
//    obj.insert("email", mail);
//    // obj -> doc
//    QJsonDocument doc(obj);
//    // doc -> qbytearray
//    QByteArray json = doc.toJson();
//    QNetworkReply* reply = pManager->post(request, json);
//    // 4. 接收服务器发送的响应数据
//    connect(reply, &QNetworkReply::readyRead, this, [=](){
//        // 5. 对服务器响应进行分析处理, 成功or失败
//        // 5.1 接收数据 {"code":"003"}
//        QByteArray all = reply->readAll();
//        // 5.2 需要知道服务器往回发送的字符串的格式 -> 解析
//        // qbytearray -> doc
//        QJsonDocument doc = QJsonDocument::fromJson(all);
//        // doc -> obj
//        QJsonObject myobj = doc.object();
//        QString status = myobj.value("code").toString();
//        // 5.3 判读成功, 失败, 给用户提示
//        if("002" == status)
//        {
//            // 成功
//        }
//        else if("003" == status)
//        {
//            // 用户已经存在
//        }
//        else
//        {
//            // 失败
//        }
//    })

//}
