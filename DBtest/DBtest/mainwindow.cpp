#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QSqlError>
#include <QSqlRecord>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
    //scanner(new Scanner),
    //showTimer(0)
{
    ui->setupUi(this);

    /*connect(scanner, &Scanner::fingerPresent, this, &MainWindow::fingerPresent);
    scanner->moveToThread(&scannerThread);
    scannerThread.start();*/

    db = QSqlDatabase::addDatabase("QTDS");

    db.setHostName("senesys-db.elvees.com");
    db.setDatabaseName("SenesysSQL");
    db.setUserName("board");
    db.setPassword("senesys");

    /*db.setHostName("slicer-pc.elvees.com");
    db.setDatabaseName("SenesysSQL2");
    db.setUserName("sa");
    db.setPassword("senesys");*/

    //if(db.open()) ui->statusBar->showMessage("Connect OK");
    if(!db.open())
    {
        ui->statusBar->showMessage(db.lastError().text());
        return ;
    }

    QString strQueryTerms = "SELECT Terminals.Terminals_Id, Terminals.Name as TName,\
            Terminals.NetDevice_Id, Terminals.TypeOfTerm, Terminals.ConfigOfTerm, Terminals.IPAddress,\
            Terminals.TypeOfAccess, Terminals.TimeZones_Id, Boards.IPAddress as BoardProperty, Proxy.TypeOfProxy,\
            Proxy.modeSound, TermMasterSlave.TermMasterSlave_Id, TermMasterSlave.flagMaster, TermMasterSlave.pairTermID,\
            Readers.SecurityLevel, Locks.Length, Terminals_1.TypeOfAccess AS TypeOfAccessSlave,\
            Locks_1.Length AS Length2, Proxy_1.TypeOfProxy AS TypeOfProxy2, Proxy_1.modeSound AS modeSound2,\
            Boards.Boards_Id, Boards.Type, Computers.Name, Terminals.modeVisit AS modeAcc, Terminals_1.modeVisit AS modeAccSlave\
            FROM(((((((Terminals LEFT JOIN Locks ON Terminals.Terminals_Id = Locks.Terminals_Id)\
            LEFT JOIN(TermMasterSlave LEFT JOIN Locks AS Locks_1 ON TermMasterSlave.pairTermID=Locks_1.Terminals_Id)\
            ON Terminals.Terminals_Id = TermMasterSlave.TermMasterSlave_Id)\
            LEFT JOIN Proxy ON Terminals.Terminals_Id = Proxy.Terminals_Id)\
            LEFT JOIN(TermMasterSlave AS TermMasterSlave_1\
            LEFT JOIN Proxy AS Proxy_1 ON TermMasterSlave_1.pairTermID = Proxy_1.Terminals_Id)\
            ON Terminals.Terminals_Id = TermMasterSlave_1.TermMasterSlave_Id)\
            LEFT JOIN Readers ON Terminals.Terminals_Id = Readers.Terminals_Id))\
            LEFT JOIN Terminals AS Terminals_1 ON TermMasterSlave.pairTermID = Terminals_1.Terminals_Id)\
            INNER JOIN(Boards INNER JOIN Computers ON Boards.Computers_Id = Computers.Computers_Id)\
            ON Terminals.Boards_Id = Boards.Boards_Id\
            WHERE((TermMasterSlave.TermMasterSlave_Id=Terminals.Terminals_Id Or TermMasterSlave.TermMasterSlave_Id Is Null)\
            AND (TermMasterSlave.flagMaster=1 Or TermMasterSlave.flagMaster Is Null)\
            AND (Boards.flagActive=1) AND (Computers.Computers_Id=4)\
            AND (Terminals.ConfigOfTerm=12 OR Terminals.ConfigOfTerm=15 OR Terminals.ConfigOfTerm=23)) ORDER BY Terminals.NetDevice_Id";
    QSqlQuery queryTerms = QSqlQuery(db);
    if(!queryTerms.exec(strQueryTerms))
    {
        ui->statusBar->showMessage(db.lastError().text());
        return;
    }

    while(queryTerms.next())
    {
       //qDebug() << queryTerms.record();
       //qDebug() << queryTerms.record().value(1).toString();
       ui->listTerms->addItem(new QListWidgetItem(QIcon(":/img/Gray.bmp"), queryTerms.record().value(1).toString()));
    }

    FTRHANDLE handle = ftrScanOpenDevice();
    FTRSCAN_IMAGE_SIZE imageSize;
    if (handle) ftrScanGetImageSize(handle, &imageSize);
    else ui->statusBar->showMessage("Can't open Futronic");
}

MainWindow::~MainWindow()
{
    /*scannerThread.quit();
    scannerThread.wait();
    delete scanner;*/

    delete ui;
}

void MainWindow::fingerPresent(QPixmap pixmap)
{
    ui->fingerLabel->setPixmap(pixmap);

    if (showTimer != 0)
    {
        killTimer(showTimer);
    }

    showTimer = startTimer(2000);
}
