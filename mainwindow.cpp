#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    refreshusers();

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
    QList <QString> itemproc = process[i].split("|");
    qDebug()<<itemproc[5]<<itemproc[7]<<itemproc[11];
    timeconnect->setText(itemproc[5]);
    host->setText(itemproc[7]);
    nameclient->setText(itemproc[11]);
    ui->tableWidget->insertRow(i);
    ui->tableWidget->setItem(i,0,timeconnect);
    ui->tableWidget->setItem(i,1,host);
    ui->tableWidget->setItem(i,2,nameclient);

    i++;
    }
    i=0;

}
void MainWindow::contextMenuUser(QPoint pos)
{

        QModelIndex index=ui->tableWidget->indexAt(pos);
        qDebug()<<pos;
        QMenu *menu=new QMenu(this);//Контекстное меню)
        menu->addAction("Suspend", this, SLOT(SuspendSession()));
        menu->addAction("2", this, SLOT(two()));
        menu->addAction("3", this, SLOT(free()));
        menu->popup(ui->tableWidget->viewport()->mapToGlobal(pos));


}
void MainWindow::SuspendSession()
{
qDebug()<<"no work";
}
void MainWindow::two()
{

}
void MainWindow::free()
{

}
