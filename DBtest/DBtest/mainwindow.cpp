#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QSqlError>
#include <QSqlRecord>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    db = QSqlDatabase::addDatabase("QTDS");
    db.setHostName("senesys-db.elvees.com");
    db.setDatabaseName("SenesysSQL");
    db.setUserName("board");
    db.setPassword("senesys");

    if(db.open()) ui->statusBar->showMessage("Connect OK");
    else
    {
        ui->statusBar->showMessage(db.lastError().text());
        return ;
    }

    //ui->listTerms->addItem(new QListWidgetItem(QIcon(":/img/Gray.bmp"), "term1"));
    //ui->listTerms->addItem(new QListWidgetItem(QIcon(":/img/Green.bmp"), "term2"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*void MainWindow::on_btnQuery_clicked()
{
    QSqlQuery query = QSqlQuery(db);
    if(!query.exec("select * from Versions"))
    {
        ui->statusBar->showMessage(db.lastError().text());
        return;
    }
    while(query.next())
    {
       qDebug() << query.record();
    }
}*/
