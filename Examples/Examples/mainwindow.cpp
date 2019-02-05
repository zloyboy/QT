#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->listWidget->addItem("One");
    ui->listWidget->addItem("Two");
    ui->listWidget->addItem("Three");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnShow_clicked()
{
    ui->statusBar->showMessage(ui->listWidget->currentItem()->text());
}
