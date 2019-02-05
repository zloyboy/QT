#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "proxy.h"
#include "scanner.h"
#include "senesys.h"

#include <QMainWindow>
#include <QObject>
#include <QPixmap>
#include <QString>
#include <QThread>

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
    void cardDetected(ulong cardId);
    void fingerPresent(QPixmap pixmap);

protected:
    virtual void timerEvent(QTimerEvent *) Q_DECL_OVERRIDE;

private:
    Proxy *proxy;
    Scanner *scanner;
    Senesys *senesys;
    QThread proxyThread;
    QThread scannerThread;
    Ui::MainWindow *ui;
    int showTimer;
};

#endif // MAINWINDOW_H
