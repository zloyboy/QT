#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

private slots:
    void digit_numbers();
    void on_btn_dot_clicked();
    void operations();
    void on_btn_clear_clicked();
    void on_btn_equal_clicked();
    void math_operations();
};

#endif // MAINWINDOW_H
