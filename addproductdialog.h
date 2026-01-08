#ifndef ADDPRODUCTDIALOG_H
#define ADDPRODUCTDIALOG_H

#include <QDialog>
#include <QPushButton>

namespace Ui {
class AddProductDialog;
}

class AddProductDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddProductDialog(QWidget *parent = nullptr);
    ~AddProductDialog();

    int getEnteredCode() const;
    void clearInput();
    void setInstruction(const QString &text);
    void setMaxDigits(int count);

private slots:
    void onNumberClicked();
    void on_btnClear_clicked();
    void on_btnConfirm_clicked();

private:
    Ui::AddProductDialog *ui;
};

#endif // ADDPRODUCTDIALOG_H
