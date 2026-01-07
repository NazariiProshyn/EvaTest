#ifndef RECEIPTITEM_H
#define RECEIPTITEM_H

#pragma once

#include "Product.h"

class ReceiptItem
{
public:
    ReceiptItem() = delete;
    ReceiptItem(const Product& product, int quantity);

    int     getId() const;
    QString getName() const;
    double  getPrice() const;
    int     getQuantity() const;
    double  getTotal() const;

    void setQuantity(int quantity);
    void addQuantity(int quantity);
private:
    Product product;
    int     quantity{0};
};

#endif // RECEIPTITEM_H
