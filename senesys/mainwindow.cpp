#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
    proxy(new Proxy),
    scanner(new Scanner),
    senesys(new Senesys),
    ui(new Ui::MainWindow),
    showTimer(0)
{
    ui->setupUi(this);

    connect(proxy, &Proxy::cardDetected, this, &MainWindow::cardDetected);
    connect(scanner, &Scanner::fingerPresent, this, &MainWindow::fingerPresent);

    proxy->moveToThread(&proxyThread);
    scanner->moveToThread(&scannerThread);

    proxyThread.start();
    scannerThread.start();
}

MainWindow::~MainWindow()
{
    proxyThread.quit();
    scannerThread.quit();

    proxyThread.wait();
    scannerThread.wait();

    delete proxy;
    delete scanner;
    delete senesys;
    delete ui;
}

void MainWindow::cardDetected(ulong cardId)
{
    ulong userId;

    if (senesys->getUserId(&userId, cardId))
    {
        QString userName = senesys->getUserName(userId);

        if (senesys->checkAccess(userId))
        {
            ui->frontLabel->setText("<font color=darkGreen>" + userName + "<br>Права подтверждены</font>");
        }
        else
            ui->frontLabel->setText("<font color=red>" + userName + "<br>Доступ запрещен</font>");
    }
    else
        ui->frontLabel->setText("<font color=red>Пользователь не найден</font>");

    if (showTimer != 0)
    {
        ui->fingerLabel->clear();
        killTimer(showTimer);
    }

    showTimer = startTimer(2000);
}

void MainWindow::fingerPresent(QPixmap pixmap)
{
    ui->fingerLabel->setPixmap(pixmap);

    if (showTimer != 0)
    {
        ui->frontLabel->clear();
        killTimer(showTimer);
    }

    showTimer = startTimer(2000);
}

void MainWindow::timerEvent(QTimerEvent *)
{
    if (showTimer != 0)
    {
        ui->fingerLabel->clear();
        ui->frontLabel->clear();
        killTimer(showTimer);
        showTimer = 0;
    }
}
