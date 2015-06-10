#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QHeaderView>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    refreshusers();
    QTableWidget * ConnectTable = ui->tableWidget;
    ConnectTable->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->tableWidget->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    connect(ui->pushButton,SIGNAL(clicked()),SLOT(refreshusers()));
    connect(ui->tableWidget,SIGNAL(customContextMenuRequested(QPoint)),SLOT(contextMenuUser(QPoint)));

}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::refreshusers()
{
    whois->start("x2golistsessions_root");
    ui->tableWidget->clear();
    while (ui->tableWidget->rowCount() > 0)
    {
        ui->tableWidget->removeRow(0);
    }
    connect(whois,SIGNAL(finished(int)),SLOT(waitFinishProcess()));

}
void MainWindow::waitFinishProcess()
{
    ui->tableWidget->setColumnCount(5);
    QList <QString> process;
    QString proc = whois->readAll();
    process = proc.split("\n");
    whois->close();
    whois->disconnect();
    int i=0;
    while(i<process.count()-1)
    {
    QTableWidgetItem * timeconnect = new QTableWidgetItem();
    QTableWidgetItem * host = new QTableWidgetItem();
    QTableWidgetItem * nameclient = new QTableWidgetItem();
    QTableWidgetItem * sessionid = new QTableWidgetItem();
    QTableWidgetItem * dispid = new QTableWidgetItem();
    QList <QString> itemproc = process[i].split("|");
    timeconnect->setText(itemproc[5]);
    host->setText(itemproc[7]);
    nameclient->setText(itemproc[11]);
    sessionid->setText(itemproc[1]);
    dispid->setText(itemproc[2]);
    ui->tableWidget->insertRow(i);
    ui->tableWidget->setItem(i,0,timeconnect);
    ui->tableWidget->setItem(i,1,host);
    ui->tableWidget->setItem(i,2,nameclient);
    ui->tableWidget->setItem(i,3,sessionid);
    ui->tableWidget->setItem(i,4,dispid);
    i++;
    }
    i=0;
    ui->tableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem("Date/Time"));
    ui->tableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem("Host"));
    ui->tableWidget->setHorizontalHeaderItem(2, new QTableWidgetItem("Username"));
    ui->tableWidget->setHorizontalHeaderItem(3, new QTableWidgetItem("SessionID"));
    ui->tableWidget->setHorizontalHeaderItem(4, new QTableWidgetItem("DISPLAY"));
}
void MainWindow::contextMenuUser(QPoint pos)
{
        QModelIndex index=ui->tableWidget->indexAt(pos);
        SessionId=ui->tableWidget->item(index.row(),3)->text();
        DisplayId=ui->tableWidget->item(index.row(),4)->text();
        UserName=ui->tableWidget->item(index.row(),2)->text();
        QMenu *menu=new QMenu(this);//Контекстное меню)
        menu->addAction("Suspend", this, SLOT(SuspendSession()));
        menu->addAction("Terminate", this, SLOT(TerminateSession()));
        menu->addAction("Control", this, SLOT(ControlSession()));
        menu->popup(ui->tableWidget->viewport()->mapToGlobal(pos));


}
void MainWindow::SuspendSession()
{
    QProcess * suspend = new QProcess();
    QStringList arg;
    arg<< SessionId;
    suspend->start("x2gosuspend-session",arg);
}
void MainWindow::TerminateSession()
{
    QProcess * terminate = new QProcess();
    QStringList arg;
    arg<< SessionId;
    terminate->start("x2goterminate-session",arg);
}
void MainWindow::ControlSession()
{
    QStringList arg;
    int i=0;
    arg <<DisplayId<<UserName;
    connectuser->start("/home/dima/SysAdminX2GO/startcli.sh",arg);
    readprocess();
    //connect(connectuser,SIGNAL(finished(int)),SLOT(errorprocess(int)));

}
void MainWindow::readprocess()
{

    waituser->start(1000);
    connect(waituser,SIGNAL(timeout()),SLOT(whatprocess()));


}
void MainWindow::whatprocess()
{
    qDebug()<<connectuser->readAll();

}

void MainWindow::errorprocess()
{
    qDebug()<<"Finish";
    QProcess * vncstart = new QProcess();
    Status = connectuser->readAll();
    qDebug()<<Status;
    vncstart->start("/home/dima/SysAdminX2GO/startvncv.sh");
    Status="";
}
