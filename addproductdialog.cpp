#include "addproductdialog.h"
#include "ui_addproductdialog.h"

AddProductDialog::AddProductDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddProductDialog)
{
    ui->setupUi(this);

    QList<QPushButton*> allButtons = this->findChildren<QPushButton*>();

    for(QPushButton* btn : allButtons) {

        if(btn->text().length() == 1 && btn->text()[0].isDigit()) {
            connect(btn, &QPushButton::clicked, this, &AddProductDialog::onNumberClicked);
        }
    }
}

AddProductDialog::~AddProductDialog()
{
    delete ui;
}


int AddProductDialog::getEnteredCode() const {
    return ui->editCode->text().toInt();
}


void AddProductDialog::onNumberClicked() {
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (button) {
        QString currentText = ui->editCode->text();

        if (currentText.isEmpty() && button->text() == "0"){
            return;
        }

        if (currentText.length() >= ui->editCode->maxLength()){
            return;
        }

        ui->editCode->setText(currentText + button->text());
    }
}

void AddProductDialog::on_btnClear_clicked() {
    ui->editCode->clear();
}

void AddProductDialog::on_btnConfirm_clicked() {
    if (!ui->editCode->text().isEmpty()) {
        accept();
    }
}

void AddProductDialog::setInstruction(const QString &text) {
    ui->textBrowser->setHtml(
        "<center><p style='font-size: 12px; font-weight: bold; margin: 0;'>"
        + text +
        "</p></center>"
        );
}

void AddProductDialog::clearInput() {
    ui->editCode->clear();
}

void AddProductDialog::setMaxDigits(int count) {
    ui->editCode->setMaxLength(count);
}
