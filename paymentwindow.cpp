#include "paymentwindow.h"
#include "./ui_paymentwindow.h"
#include "addproductdialog.h"
#include <QMessageBox>

PaymentWindow::PaymentWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::PaymentWindow)
{
    ui->setupUi(this);

    setupLabels();
    setupTable();
}

void PaymentWindow::on_btnAddProduct_clicked() {
    AddProductDialog dialog(this);
    dialog.setInstruction("Enter barcode (4 digits)");
    dialog.setMaxDigits(4);

    if (dialog.exec() == QDialog::Accepted) {
        int code = dialog.getEnteredCode();

        if (catalog.contains(code)) {
            const Product& p = catalog.getProduct(code);

            dialog.clearInput();
            dialog.setInstruction(p.getName() + ": enter quantity");
            dialog.setMaxDigits(2);

            if (dialog.exec() == QDialog::Accepted) {
                int inputQuantity = dialog.getEnteredCode();

                if (inputQuantity > 0) {
                    int currentInReceipt = 0;

                    const auto& items = receipt.getItems();

                    for (const auto& item : items) {
                        if (item.getName() == p.getName()) {
                            currentInReceipt = item.getQuantity();
                            break;
                        }
                    }

                    if (currentInReceipt + inputQuantity > 99) {
                        QMessageBox::warning(this, "Quantity Limit",
                                             "Maximum quantity for " + p.getName() + " is 99.\n"
                                                                                     "The amount will be adjusted.");
                    }

                    receipt.addProduct(p, inputQuantity);
                    updateUI();
                }
            }
        } else {
            QMessageBox::warning(this, "Error", "Product not found!");
        }
    }
}

void PaymentWindow::on_btnDltProduct_clicked() {
    if (receipt.getItems().isEmpty()) {
        QMessageBox::information(this, "Empty Receipt",
                                 "The receipt is empty. There is nothing to delete!");
        return;
    }

    AddProductDialog dialog(this);
    dialog.setInstruction("ENTER PRODUCT ID TO DELETE");
    dialog.setMaxDigits(2);
    dialog.clearInput();

    if (dialog.exec() == QDialog::Accepted) {
        int targetId = dialog.getEnteredCode();

        if (targetId > 0) {
            bool found = false;
            for (const auto& item : receipt.getItems()) {
                if (item.getId() == targetId) {
                    found = true;
                    break;
                }
            }

            if (found) {
                receipt.removeProduct(targetId);

                updateUI();

            } else {
                QMessageBox::warning(this, "Error",
                                     "Product with ID " + QString::number(targetId) + " is not in the receipt!");
            }
        } else {
            QMessageBox::warning(this, "Error", "Please enter a valid Product ID!");
        }
    }
}

void PaymentWindow::on_btnAddMoney_clicked() {
    AddProductDialog dialog(this);

    dialog.setInstruction("ENTER CASH AMOUNT");
    dialog.setMaxDigits(6);
    dialog.clearInput();

    if (dialog.exec() == QDialog::Accepted) {
        double newAmount = dialog.getEnteredCode();
        double currentCash = receipt.getCash();

        if (currentCash + newAmount > 1000000) {
            QMessageBox::warning(this, "Cash Limit",
                                 "Maximum cash amount (1,000,000) exceeded.\n"
                                 "Transaction rejected. Please take your money back!");
        } else {
            receipt.addCash(newAmount);
            updateUI();
        }
    }
}

void PaymentWindow::on_btnCancel_clicked() {
    if (receipt.getItems().isEmpty() && receipt.getCash() == 0) {
        return;
    }

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Cancel Receipt",
                                  "Are you sure you want to clear the current receipt and all cash entered?",
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        double cashToReturn = receipt.getCash();

        if (cashToReturn > 0) {
            QMessageBox::information(this, "Money Return",
                                     "Cash is returned to the customer: " +
                                         QString::number(cashToReturn, 'f', 2));
        }

        receipt.clear();

        updateUI();
    }
}

void PaymentWindow::on_btnPay_clicked() {
    double total = receipt.totalAmount();
    double cash = receipt.getCash();

    if (total <= 0) {
        QMessageBox::warning(this, "Empty Receipt",
                             "Cannot process payment: There are no items in the receipt.");
        return;
    }

    if (cash < total) {
        double missing = total - cash;
        QMessageBox::critical(this, "Insufficient Funds",
                              "The amount entered is not enough!\n"
                              "Missing: " + QString::number(missing, 'f', 2));
        return;
    }

    double change = cash - total;
    QString message = "Payment successful!\n\nTotal: " + QString::number(total, 'f', 2);

    if (change > 0) {
        message += "\nChange to return: " + QString::number(change, 'f', 2);
    }

    QMessageBox::information(this, "Transaction Completed", message);

    receipt.clear();
    updateUI();
}

void PaymentWindow::setupTable() {
    ui->tableProducts->setColumnCount(columnCount);
    ui->tableProducts->setHorizontalHeaderLabels(headers);
    ui->tableProducts->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->tableProducts->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableProducts->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableProducts->verticalHeader()->setVisible(false);
}

void PaymentWindow::setupLabels() {
    ui->editTotalSum->setText("0.00");
    ui->editCash->setText("0.00");
    ui->editChange->setText("0.00");
}

void PaymentWindow::updateUI() {
    ui->tableProducts->setRowCount(0);

    const auto& items = receipt.getItems();

    for (int i = 0; i < items.size(); ++i) {
        const auto& item = items.at(i);

        int row = ui->tableProducts->rowCount();
        ui->tableProducts->insertRow(row);

        ui->tableProducts->setItem(row, 0, new QTableWidgetItem(QString::number(item.getId())));
        ui->tableProducts->setItem(row, 1, new QTableWidgetItem(item.getName()));
        ui->tableProducts->setItem(row, 2, new QTableWidgetItem(QString::number(item.getQuantity())));
        ui->tableProducts->setItem(row, 3, new QTableWidgetItem(QString::number(item.getPrice(), 'f', 2)));
        ui->tableProducts->setItem(row, 4, new QTableWidgetItem(QString::number(item.getTotal(), 'f', 2)));

        ui->tableProducts->item(row, 0)->setTextAlignment(Qt::AlignCenter);
        ui->tableProducts->item(row, 2)->setTextAlignment(Qt::AlignCenter);
    }

    double total = receipt.totalAmount();
    double cash = receipt.getCash();

    ui->editTotalSum->setText(QString::number(total, 'f', 2));
    ui->editCash->setText(QString::number(cash, 'f', 2));

    updateChange();

    if (total > 0 && cash >= total) {
        ui->btnPay->setStyleSheet("background-color: #2ECC71; color: white; font-weight: bold; border-radius: 5px;");
    } else {
        ui->btnPay->setStyleSheet("background-color: #145A32; color: #7FB3D5; font-weight: bold; border-radius: 5px;");
    }
}

void PaymentWindow::updateChange() {
    double total = receipt.totalAmount();
    double cash = receipt.getCash();

    double change = 0.0;
    if (cash > total) {
        change = cash - total;
    }

    ui->editChange->setText(QString::number(change, 'f', 2));
}


PaymentWindow::~PaymentWindow()
{
    delete ui;
}
