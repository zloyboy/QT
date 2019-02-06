#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QObject>
#include <QPixmap>
#include <QString>
#include <QThread>

#include "scanner.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void fingerPresent(QPixmap pixmap);

private slots:

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;

    Scanner *scanner;
    QThread scannerThread;
    int showTimer;
};

#endif // MAINWINDOW_H
