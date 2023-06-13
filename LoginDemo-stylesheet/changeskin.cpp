#include "changeskin.h"
#include <QFile>
#include <QApplication>

ChangeSkin::ChangeSkin(QObject *parent) : QObject(parent)
{

}

void ChangeSkin::changeSkin(QString qss)
{
    QFile file(qss);
    file.open(QFile::ReadOnly);
    QByteArray style = file.readAll();
    qApp->setStyleSheet(style);
    file.close();
}
