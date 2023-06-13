#include "titlebar1.h"
#include "ui_titlebar1.h"
#include <QMouseEvent>

TitleBar1::TitleBar1(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TitleBar1)
{
    ui->setupUi(this);


    ui->logo->setPixmap(QPixmap(":/images/logo.ico").scaled(40, 40));
    connect(ui->set, &QToolButton::clicked, [=]()
    {
       emit setMyWindow();
    });
    connect(ui->min, &QToolButton::clicked, [=]()
    {
       emit minMyWindow();
    });
    connect(ui->close, &QToolButton::clicked, [=]()
    {
       emit closeMyWindow();
    });
}

TitleBar1::~TitleBar1()
{
    delete ui;
}

void TitleBar1::setMyParent(QWidget *parent)
{
    m_parent = parent;
}

void TitleBar1::mouseMoveEvent(QMouseEvent *event)
{
    // 如果按下是左键, 窗口移动
    if(event->buttons() & Qt::LeftButton)
    {
        // 控制窗口移动
        // 当前鼠标的位置
        QPoint cur = event->globalPos();
        m_parent->move(cur - m_pt);
    }
}

void TitleBar1::mousePressEvent(QMouseEvent *event)
{
    // 如果按下是鼠标左键
    if(event->button() == Qt::LeftButton)
    {
        // 求当前位置和屏蔽左上角的差值
        m_pt = event->globalPos() - m_parent->geometry().topLeft();
    }
}
