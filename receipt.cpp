#include "receipt.h"

int Receipt::findItemIndex(int productId) const
{
    for (size_t i = 0; i < items.size(); ++i) {
        if (items[i].getId() == productId) {
            return i;
        }
    }
    return -1;
}

void Receipt::addProduct(const Product& p, int quantity) {
    for (int i = 0; i < items.size(); ++i) {
        if (items[i].getId() == p.getId()) {
            int newQuantity = items[i].getQuantity() + quantity;

            if (newQuantity > MAXQUANTITY) {
                items[i].setQuantity(MAXQUANTITY);
            } else {
                items[i].setQuantity(newQuantity);
            }
            return;
        }
    }

    if (quantity > MAXQUANTITY) {
        quantity = MAXQUANTITY;
    }
    items.append(ReceiptItem(p, quantity));
}

void Receipt::setQuantity(int productId, int quantity)
{
    int index = findItemIndex(productId);
    if (index != -1) {
        items[index].setQuantity(quantity);
    }
}

void Receipt::removeProduct(int productId)
{
    int index = findItemIndex(productId);
    if (index != -1) {
        items.removeAt(index);
    }
}

double Receipt::totalAmount() const
{
    double total = 0.0;
    for (size_t i = 0; i < items.size(); ++i) {
        total += items[i].getTotal();
    }
    return total;
}

const QList<ReceiptItem>& Receipt::getItems() const {
    return items;
}

void Receipt::addCash(double amount) {
    cash += amount;
    }

double Receipt::getCash() const {
    return cash;
}

void Receipt::resetCash() {
    cash = 0.0;
}

void Receipt::clear() {
    items.clear();
    cash = 0.0;
}
