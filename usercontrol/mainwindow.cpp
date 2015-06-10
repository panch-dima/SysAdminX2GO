#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTcpSocket>
#include <QTimer>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton_RC,SIGNAL(clicked()),SLOT(rc_proc()));
    connect(ui->pushButton_VO,SIGNAL(clicked()),SLOT(vo_proc()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::rc_proc()
{
    ui->pushButton_RC->setEnabled(false);
    ui->pushButton_VO->setEnabled(false);

    MainWindow::hide();
    QProcess * rc = new QProcess();
    QStringList arg;
    arg<<"-localhost";
    QTimer * time = new QTimer;
    time->start(10000);
    connect(time,SIGNAL(timeout()),SLOT(state()));
    rc->startDetached("x11vnc",arg);



}
void MainWindow::vo_proc()
{
    ui->pushButton_RC->setEnabled(false);
    ui->pushButton_VO->setEnabled(false);
    MainWindow::hide();
    QProcess * vo = new QProcess();
    QStringList arg;
    arg << "-viewonly -localhost";
    QTimer * time = new QTimer;
    time->start(10000);
    connect(time,SIGNAL(timeout()),SLOT(state()));
    vo->startDetached("x11vnc",arg);

}

void MainWindow::state()
{
    QTcpSocket * client = new QTcpSocket(this);
    client->connectToHost("127.0.0.1",5900);

    if (client->waitForConnected(30))
    {
        qDebug()<<"ready";
        exit(0);
    }
    else
     {
        return;
     }
}
