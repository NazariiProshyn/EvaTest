#ifndef PAYMENTWINDOW_H
#define PAYMENTWINDOW_H

#include <QDialog>
#include "catalog.h"
#include "receipt.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class PaymentWindow;
}
QT_END_NAMESPACE

class PaymentWindow : public QDialog
{
    Q_OBJECT

public:
    PaymentWindow(QWidget *parent = nullptr);
    ~PaymentWindow();

private slots:
    void on_btnAddProduct_clicked();
    void on_btnDltProduct_clicked();
    void on_btnAddMoney_clicked();
    void on_btnCancel_clicked();
    void on_btnPay_clicked();

private:
    Ui::PaymentWindow *ui;

    QStringList headers{"ID", "Name", "Quantity", "Price", "Total"};

    int columnCount{5};

    const Catalog catalog;// BD

    Receipt receipt;

    void setupTable();
    void setupLabels();
    void updateUI();
    void updateChange();
};
#endif // PAYMENTWINDOW_H
