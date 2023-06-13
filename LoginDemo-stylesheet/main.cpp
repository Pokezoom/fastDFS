#include "mainwindow.h"
#include <QApplication>
#include <QFile>
#include "login.h"
#include <QDebug>
#include "changeskin.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString str = "QLabel#loginTitle"
    "{"
        "font-family: '华文新魏';"
        "font-size: 20px;"
    "}";
    // 设置样式表
    ChangeSkin::changeSkin(":/style1.qss");

    Login w;
    w.show();

    return a.exec();
}
