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

private:
    Ui::PaymentWindow *ui;
    QStringList headers{"Name", "Quantity", "Price", "Total"};
    int columnCount{4};

    const Catalog catalog;// BD
    Receipt receipt;

    void setupTable();
    void updateUI();
};
#endif // PAYMENTWINDOW_H
