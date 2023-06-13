#ifndef MYTITLEBAR_H
#define MYTITLEBAR_H

#include <QWidget>

namespace Ui {
class MyTitleBar;
}

class MyTitleBar : public QWidget
{
    Q_OBJECT

public:
    explicit MyTitleBar(QWidget *parent = 0);
    ~MyTitleBar();
    void setMyParent(QWidget* parent);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

signals:
    void showSetWindow();
    void showMinWidnow();
    void closeWindow();
    void otherSkin();

private:
    Ui::MyTitleBar *ui;

    QPoint m_pt;    // 鼠标按下位置和屏幕左上角的点的差值
    QWidget* m_parent;
};

#endif // MYTITLEBAR_H
