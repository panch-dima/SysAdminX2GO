#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    refreshusers();
    ui->tableWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->tableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem("Prueba"));
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
    ui->tableWidget->setColumnCount(3);
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

}
void MainWindow::contextMenuUser(QPoint pos)
{
        qDebug()<<pos<<"pos";
        QModelIndex index=ui->tableWidget->indexAt(pos);
        QModelIndex indextwo;
        QVariant tabledata;
        QMenu *menu=new QMenu(this);//Контекстное меню)
        menu->addAction("Suspend", this, SLOT(SuspendSession()));
        menu->addAction("Terminate", this, SLOT(TerminateSession()));
        menu->addAction("No Work", this, SLOT(OutIndex3()));
        menu->popup(ui->tableWidget->viewport()->mapToGlobal(pos));


}
void MainWindow::SuspendSession()
{

}
void MainWindow::TerminateSession()
{

}
void MainWindow::free()
{

}
