#include "mainwindow.h"
#include "ui_mainwindow.h"

double num_first = 0;
double num_second = 0;
bool has_oper = false;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->btn_0, SIGNAL(clicked()), this, SLOT(digit_numbers()));
    connect(ui->btn_1, SIGNAL(clicked()), this, SLOT(digit_numbers()));
    connect(ui->btn_2, SIGNAL(clicked()), this, SLOT(digit_numbers()));
    connect(ui->btn_3, SIGNAL(clicked()), this, SLOT(digit_numbers()));
    connect(ui->btn_4, SIGNAL(clicked()), this, SLOT(digit_numbers()));
    connect(ui->btn_5, SIGNAL(clicked()), this, SLOT(digit_numbers()));
    connect(ui->btn_6, SIGNAL(clicked()), this, SLOT(digit_numbers()));
    connect(ui->btn_7, SIGNAL(clicked()), this, SLOT(digit_numbers()));
    connect(ui->btn_8, SIGNAL(clicked()), this, SLOT(digit_numbers()));
    connect(ui->btn_9, SIGNAL(clicked()), this, SLOT(digit_numbers()));
    connect(ui->btn_sign, SIGNAL(clicked()), this, SLOT(operations()));
    connect(ui->btn_perc, SIGNAL(clicked()), this, SLOT(operations()));
    connect(ui->btn_div, SIGNAL(clicked()), this, SLOT(math_operations()));
    connect(ui->btn_mult, SIGNAL(clicked()), this, SLOT(math_operations()));
    connect(ui->btn_plus, SIGNAL(clicked()), this, SLOT(math_operations()));
    connect(ui->btn_minus, SIGNAL(clicked()), this, SLOT(math_operations()));

    ui->btn_div->setCheckable(true);
    ui->btn_mult->setCheckable(true);
    ui->btn_plus->setCheckable(true);
    ui->btn_minus->setCheckable(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::digit_numbers()
{
    QPushButton* button = (QPushButton*)sender();
    if(has_oper) num_second = button->text().toDouble();
    else num_first = button->text().toDouble();
    ui->result_show->setText(ui->result_show->text() + button->text());
}

void MainWindow::on_btn_dot_clicked()
{
    if(!ui->result_show->text().contains('.'))
        ui->result_show->setText(ui->result_show->text() + ".");
}

void MainWindow::operations()
{
    QPushButton* button = (QPushButton*)sender();
    double result = ui->result_show->text().toDouble();

    if(button->text() == "+/-") result *= -1.0;
    else
    if(button->text() == "%") result *= 0.01;

    ui->result_show->setText(QString::number(result, 'g', 15));
}

void MainWindow::on_btn_clear_clicked()
{
    ui->btn_div->setChecked(false);
    ui->btn_mult->setChecked(false);
    ui->btn_plus->setChecked(false);
    ui->btn_minus->setChecked(false);
    has_oper = false;
    ui->result_show->setText("");
}

void MainWindow::on_btn_equal_clicked()
{
    double result;

    if(ui->btn_plus->isChecked()) result = num_first + num_second;
    else
    if(ui->btn_minus->isChecked()) result = num_first - num_second;
    else
    if(ui->btn_mult->isChecked()) result = num_first * num_second;
    else
    if(ui->btn_div->isChecked()) result = num_first / num_second;

    ui->result_show->setText(QString::number(result, 'g', 15));
}

void MainWindow::math_operations()
{
    QPushButton* button = (QPushButton*)sender();
    ui->result_show->setText(ui->result_show->text() + button->text());

    has_oper = true;
    button->setChecked(true);
}
