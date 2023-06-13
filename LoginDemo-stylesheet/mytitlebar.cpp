#include "mytitlebar.h"
#include "ui_mytitlebar.h"
#include <QMouseEvent>

MyTitleBar::MyTitleBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyTitleBar)
{
    ui->setupUi(this);

    //ui->logo->setPixmap(QPixmap(":/images/logo.ico").scaled(35, 35));
    ui->logoName->setText(" 传智播客");

    connect(ui->setBtn, &QToolButton::clicked, this, &MyTitleBar::showSetWindow);
    connect(ui->minBtn, &QToolButton::clicked, this, &MyTitleBar::showMinWidnow);
    connect(ui->closeBtn, &QToolButton::clicked, this, &MyTitleBar::closeWindow);
    connect(ui->skinBtn, &QToolButton::clicked, this, &MyTitleBar::otherSkin);

    ui->setBtn->setToolTip("设置");
    ui->minBtn->setToolTip("最小化");
    ui->closeBtn->setToolTip("关闭");
    ui->skinBtn->setToolTip("换肤");
}

MyTitleBar::~MyTitleBar()
{
    delete ui;
}

void MyTitleBar::setMyParent(QWidget *parent)
{
    m_parent = parent;
}

void MyTitleBar::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        m_pt = event->globalPos() - m_parent->geometry().topLeft();
    }
}

void MyTitleBar::mouseMoveEvent(QMouseEvent *event)
{
    // 判断是不是鼠标左键
    if(event->buttons() & Qt::LeftButton)
    {
        // 窗口跟随移动 - QWidget -> move(窗口左上角坐标)
        m_parent->move(event->globalPos() - m_pt);
    }
}
