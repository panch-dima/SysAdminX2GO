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


    rc->start("x11vnc");
    connect(rc,SIGNAL(finished(int)),SLOT(close()));
}
void MainWindow::vo_proc()
{
    ui->pushButton_RC->setEnabled(false);
    ui->pushButton_VO->setEnabled(false);
    MainWindow::hide();
    QProcess * vo = new QProcess();
    QStringList arg;
    arg << "-viewonly";
    vo->start("x11vnc",arg);
    connect(vo,SIGNAL(finished(int)),SLOT(close()));
}
