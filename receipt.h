#ifndef RECEIPT_H
#define RECEIPT_H

#pragma once

#include <QVector>
#include "ReceiptItem.h"

class Receipt
{
public:
    Receipt() = default;

    void addProduct(const Product& product, int quantity = 1);
    void setQuantity(int productId, int quantity);
    void removeProduct(int productId);

    double totalAmount() const;

private:
    int findItemIndex(int productId) const;

    QVector<ReceiptItem> items;
};

#endif // RECEIPT_H
