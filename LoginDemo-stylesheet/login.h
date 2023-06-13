#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    ~Login();

protected:
    void paintEvent(QPaintEvent *event);

private slots:
    void on_regAccount_clicked();

    void on_loginButton_clicked();

private:
    Ui::Login *ui;
};

#endif // LOGIN_H
