#include "paymentwindow.h"
#include "./ui_paymentwindow.h"

PaymentWindow::PaymentWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::PaymentWindow)
{
    ui->setupUi(this);
}

PaymentWindow::~PaymentWindow()
{
    delete ui;
}
