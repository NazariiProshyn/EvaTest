#include "paymentwindow.h"
#include "./ui_paymentwindow.h"
#include "addproductdialog.h"
#include <QMessageBox>

PaymentWindow::PaymentWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::PaymentWindow)
{
    ui->setupUi(this);

    setupTable();
}

void PaymentWindow::on_btnAddProduct_clicked() {
    AddProductDialog dialog(this);

    dialog.setInstruction("Enter barcode(xxxx)");
    dialog.setMaxDigits(4);

    if (dialog.exec() == QDialog::Accepted) {
        int code = dialog.getEnteredCode();

        if (catalog.contains(code)) {
            dialog.clearInput();
            dialog.setInstruction(catalog.getProduct(code).getName() + ": enter quantity");
            dialog.setMaxDigits(2);

            if (dialog.exec() == QDialog::Accepted) {
                int quantity = dialog.getEnteredCode();
                if (quantity > 0) {
                    receipt.addProduct(catalog.getProduct(code), quantity);
                    updateUI();
                } else {
                    QMessageBox::warning(this, "Error", "Quantity must be > 0!");
                }

            }
        } else {
            QMessageBox::warning(this, "Error", "Product with code " + QString::number(code) + " not found!");
        }
    }
}

void PaymentWindow::setupTable() {
    ui->tableProducts->setColumnCount(columnCount);
    ui->tableProducts->setHorizontalHeaderLabels(headers);
    ui->tableProducts->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->tableProducts->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableProducts->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableProducts->verticalHeader()->setVisible(false);
}

void PaymentWindow::updateUI() {
    ui->tableProducts->setRowCount(0);
}

PaymentWindow::~PaymentWindow()
{
    delete ui;
}
