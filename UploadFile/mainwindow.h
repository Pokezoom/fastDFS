#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QString getMd5(QString path);

private slots:
    void on_selFile_clicked();

    void on_uploadBtn_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
