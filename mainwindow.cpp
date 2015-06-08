#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    refreshusers();
    ui->tableWidget->setContextMenuPolicy(Qt::CustomContextMenu);

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
    ui->tableWidget->setColumnCount(4);
    QList <QString> process;
    QString proc = whois->readAll();
    process = proc.split("\n");
    qDebug()<<process;
    whois->close();
    whois->disconnect();
    int i=0;
    while(i<process.count()-1)
    {
    QTableWidgetItem * timeconnect = new QTableWidgetItem();
    QTableWidgetItem * host = new QTableWidgetItem();
    QTableWidgetItem * nameclient = new QTableWidgetItem();
    QTableWidgetItem * sessionid = new QTableWidgetItem();
    QList <QString> itemproc = process[i].split("|");
    qDebug()<<itemproc[5]<<itemproc[7]<<itemproc[11];
    timeconnect->setText(itemproc[5]);
    host->setText(itemproc[7]);
    nameclient->setText(itemproc[11]);
    sessionid->setText(itemproc[1]);
    ui->tableWidget->insertRow(i);
    ui->tableWidget->setItem(i,0,timeconnect);
    ui->tableWidget->setItem(i,1,host);
    ui->tableWidget->setItem(i,2,nameclient);
    ui->tableWidget->setItem(i,3,sessionid);
    i++;
    }
    i=0;
    ui->tableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem("Date/Time"));
    ui->tableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem("Host"));
    ui->tableWidget->setHorizontalHeaderItem(2, new QTableWidgetItem("Username"));
    ui->tableWidget->setHorizontalHeaderItem(3, new QTableWidgetItem("SessionID"));

}
void MainWindow::contextMenuUser(QPoint pos)
{
        QModelIndex index=ui->tableWidget->indexAt(pos);
        QModelIndex indextwo;
        QVariant tabledata;
        indextwo = ui->tableWidget->model()->index(index.row(),3,QModelIndex());
        tabledata = ui->tableWidget->data(indextwo,Qt::DisplayRole);
        SessionId=tabledata.toString();
        QMenu *menu=new QMenu(this);//Контекстное меню)
        menu->addAction("Suspend", this, SLOT(SuspendSession()));
        menu->addAction("Terminate", this, SLOT(TerminateSession()));
        menu->addAction("No Work", this, SLOT(free()));
        menu->popup(ui->tableWidget->viewport()->mapToGlobal(pos));


}
void MainWindow::SuspendSession()
{
    QProcess * suspend = new QProcess();
    suspend->arguments(SessionId);
    suspend->start("x2gosuspend-session");
}
void MainWindow::TerminateSession()
{
    QProcess * terminate = new QProcess();
    terminate->arguments(SessionId);
    terminate->start("x2goterminate-session");
}
void MainWindow::free()
{

}
