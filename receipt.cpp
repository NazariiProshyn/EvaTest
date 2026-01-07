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

void Receipt::addProduct(const Product& product, int quantity)
{
    int index = findItemIndex(product.getId());
    if (index != -1) {
        items[index].addQuantity(quantity);
    } else {
        items.append({ product, quantity });
    }
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
