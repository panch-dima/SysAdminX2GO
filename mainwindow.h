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
public slots:
    void refreshusers();
    void waitFinishProcess();
    void contextMenuUser(QPoint pos);
    void SuspendSession();
    void two();
    void free();
};

#endif // MAINWINDOW_H
