#ifndef RECEIPT_H
#define RECEIPT_H

#pragma once

#include <QList>
#include "ReceiptItem.h"

class Receipt
{
public:
    Receipt() = default;

    void addProduct(const Product& product, int quantity = 1);
    void setQuantity(int productId, int quantity);
    void removeProduct(int productId);

    double totalAmount() const;
    const  QList<ReceiptItem>& getItems() const;
    void   addCash(double amount);
    double getCash() const;
    void   resetCash();
    void   clear();
private:
    int findItemIndex(int productId) const;

    QList<ReceiptItem> items;

    const int MAXQUANTITY {99};
    double    cash {0.0};
};

#endif // RECEIPT_H
