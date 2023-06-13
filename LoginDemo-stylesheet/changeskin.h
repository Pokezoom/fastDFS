#ifndef CHANGESKIN_H
#define CHANGESKIN_H

#include <QObject>

class ChangeSkin : public QObject
{
    Q_OBJECT
public:
    explicit ChangeSkin(QObject *parent = nullptr);
    static void changeSkin(QString qss);

signals:

public slots:
};

#endif // CHANGESKIN_H
