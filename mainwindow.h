#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>
#include <QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QProcess * whois = new QProcess();

private:
    Ui::MainWindow *ui;
    void refreshusers();
    void waitFinishProcess();
    void contextMenuUser();
};

#endif // MAINWINDOW_H
