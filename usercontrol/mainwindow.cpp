#include "mainwindow.h"
#include "ui_mainwindow.h"

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
    QProcess * rc = new QProcess();
    QStringList arg;
    arg<<"-localhost";
    rc->start("x11vnc",arg);
    MainWindow::hide();
    qDebug()<<"ready ";
}
void MainWindow::vo_proc()
{
    ui->pushButton_RC->setEnabled(false);
    ui->pushButton_VO->setEnabled(false);

    QProcess * vo = new QProcess();
    QStringList arg;
    arg << "-viewonly -localhost";
    vo->start("x11vnc",arg);
    MainWindow::hide();
    qDebug()<<"ready";
}
