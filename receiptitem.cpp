#include "receiptitem.h"

ReceiptItem::ReceiptItem(const Product& product, int quantity)
    : product(product)
    , quantity(quantity)
{
}


int ReceiptItem::getQuantity() const {
    return quantity;
}

void ReceiptItem::setQuantity(int num) {
    quantity = num;
}

void ReceiptItem::addQuantity(int num) {
    quantity += num;
}

double ReceiptItem::getTotal() const {
    return product.getPrice() * quantity;
}

int ReceiptItem::getId() const {
    return product.getId();
}

QString ReceiptItem::getName() const {
    return product.getName();
}

double ReceiptItem::getPrice() const {
    return product.getPrice();
}
