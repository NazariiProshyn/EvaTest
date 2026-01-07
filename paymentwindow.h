#ifndef PAYMENTWINDOW_H
#define PAYMENTWINDOW_H

#include <QDialog>

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

private:
    Ui::PaymentWindow *ui;
};
#endif // PAYMENTWINDOW_H
