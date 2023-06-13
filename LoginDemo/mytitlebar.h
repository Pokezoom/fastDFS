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

signals:
    void showSetWindow();
    void showMinWindow();
    void closeMyWindow();

protected:
    // 鼠标移动 -> 让窗口跟随鼠标懂
    void mouseMoveEvent(QMouseEvent *event);
    // 鼠标按下 -> 求相对距离
    void mousePressEvent(QMouseEvent *event);

private:
    Ui::MyTitleBar *ui;
    QWidget* m_parent = NULL;
    QPoint m_pt;
};

#endif // MYTITLEBAR_H
