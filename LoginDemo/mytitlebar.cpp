#include "mytitlebar.h"
#include "ui_mytitlebar.h"
#include <QMouseEvent>

MyTitleBar::MyTitleBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyTitleBar)
{
    ui->setupUi(this);
    // m_parent = parent;

    connect(ui->setBtn, &QToolButton::clicked, this, [=]()
    {
        emit showSetWindow();
    });
    connect(ui->minBtn, &QToolButton::clicked, this, [=]()
    {
        emit showMinWindow();
    });
    connect(ui->closeBtn, &QToolButton::clicked, this, [=]()
    {
        emit closeMyWindow();
    });
    // 设置logo
    // ui->logo->setPixmap(QPixmap(":/images/logo.ico").scaled(40, 40));
}

MyTitleBar::~MyTitleBar()
{
    delete ui;
}

void MyTitleBar::setMyParent(QWidget *parent)
{
    m_parent = parent;
}

void MyTitleBar::mouseMoveEvent(QMouseEvent *event)
{
    // 鼠标移动到了什么位置? -> 通过参数globalPos();
    // 得到位置之后 -> 让窗口跟随鼠标移动 -> move();
    // 移动的应该是外部的login窗口
    // event->globalPos()鼠标移动到了屏幕的什么位置, 要求的是窗口左上角的点
    // 左上角的位置 = 当前鼠标位置 - 相对位置;
    // 判断持续状态, 鼠标左键
    if(event->buttons() & Qt::LeftButton)
    {
         m_parent->move(event->globalPos() - m_pt);
    }
}

void MyTitleBar::mousePressEvent(QMouseEvent *event)
{
    // 如果是鼠标左键, 瞬间状态
    if(event->button() == Qt::LeftButton)
    {
        // 相对位置 = 当前鼠标位置 - 左上角的位置;
        m_pt = event->globalPos() - m_parent->geometry().topLeft();
    }
}
