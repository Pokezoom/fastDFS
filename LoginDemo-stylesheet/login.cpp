#include "login.h"
#include "ui_login.h"
#include "changeskin.h"
#include <QPainter>
#include <QRegExp>
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

const QString USER_REG      = "^[a-zA-Z\d_@#-\*]{3,16}$";
const QString PASSWD_REG    = "^[a-zA-Z\d_@#-\*]{6,18}$";

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);

    setFixedSize(640, 480);
    // 去边框
    //setWindowFlag(Qt::FramelessWindowHint);
    setWindowFlags(windowFlags() | Qt::FramelessWindowHint);

    ui->titleBar->setMyParent(this);
    ui->stackedWidget->setCurrentIndex(0);

    connect(ui->titleBar, &MyTitleBar::showMinWidnow, this, &Login::showMinimized);
    connect(ui->titleBar, &MyTitleBar::showSetWindow, [=]()
    {
        ui->stackedWidget->setCurrentWidget(ui->netSetPage);
    });
    connect(ui->titleBar, &MyTitleBar::closeWindow, [=]()
    {
        if(ui->stackedWidget->currentWidget() == ui->loginPage)
        {
            close();
        }
        else
        {
            ui->stackedWidget->setCurrentIndex(0);
        }
    });
    connect(ui->titleBar, &MyTitleBar::otherSkin, [=]()
    {
        static bool bl = false;
        QString str = bl ? ":/style1.qss" : ":/style2.qss";
        ChangeSkin::changeSkin(str);
        bl = !bl;
    });
}

Login::~Login()
{
    delete ui;
}

void Login::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.drawPixmap(0, 0, width(), height(), QPixmap(":/images/login_bk.jpg"));
}

// 没有账号, 马上注册
void Login::on_regAccount_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->regPage);
}

// 登录按钮
void Login::on_loginButton_clicked()
{
    // 1. 取出控件数据
    QString user = ui->userName_login->text();
    QString passwd = ui->passwd_login->text();

    // 2. 检验用户输入的数据 -> 正则表达式
    QRegExp exp(USER_REG);
    // 判断是否能匹配成功
    bool bl = exp.exactMatch(user);
    if(bl == false)
    {
        QMessageBox::warning(this, "Waring", "输入的用户名格式错误, 请重新输入.");
        return;
    }
    // 重写设置匹配规则
    exp.setPattern(PASSWD_REG);
    bl = exp.exactMatch(passwd);
    if(bl == false)
    {
        QMessageBox::warning(this, "Waring", "输入的密码格式错误, 请重新输入.");
        return;
    }

    // 3. 组织数据格式, 发送数据给服务器
    // 3-1. 数据组织成什么格式?
//    {
//        user:xxxx,
//        pwd:xxx
//    }
    QJsonObject obj;
    obj.insert("user", user);
    obj.insert("pwd", passwd);
    // obj->Qbytearray
    // obj->jsondoc
    QJsonDocument doc(obj);
    // jsondoc->qbytearray
    QByteArray json = doc.toJson();
    // 3-2. http协议, 使用post方式提交数据
    // 3-3. 数据发送 post方法
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QNetworkRequest request;
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setHeader(QNetworkRequest::ContentLengthHeader, json.size());
    // url的设置
    QString url = QString("http://%1:%2/login").arg("192.168.80.254").arg(80);
    request.setUrl(url);
    QNetworkReply* reply = manager->post(request, json);
    // 4. 等待接收服务器回发的数据
    connect(reply, &QNetworkReply::readyRead, this, [=]()
    {
        // 读返回的数据 -> http响应中的响应正文
        QByteArray recvData = reply->readAll();
//        {
//            "code": "001",
//            "token": "faild"
//        }
        // QByteArray-> jsondoc
        // jsondoc->jsonobj
        // jsonobj->value(key)
    });
    // 5. 解析服务器回发的数据 -> 需要知道服务器回发的数据的格式
    // 6. 如果需要记住密码, 将登陆信息写入配置文件 -> 文件格式json
}
