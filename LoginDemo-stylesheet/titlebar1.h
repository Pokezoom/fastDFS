#ifndef TITLEBAR1_H
#define TITLEBAR1_H

#include <QWidget>

namespace Ui {
class TitleBar1;
}

class TitleBar1 : public QWidget
{
    Q_OBJECT

public:
    explicit TitleBar1(QWidget *parent = 0);
    ~TitleBar1();

    void setMyParent(QWidget* parent);

signals:
    void setMyWindow();
    void minMyWindow();
    void closeMyWindow();

protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);

private:
    Ui::TitleBar1 *ui;
    QPoint m_pt;    // 差值
    QWidget* m_parent;
};

#endif // TITLEBAR1_H
