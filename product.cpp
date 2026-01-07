#include "product.h"

Product::Product(int Id, const QString& Name, double Price)
    : id(Id)
    , name(Name)
    , price(Price)
{
}

int Product::getId() const {
    return id;
}

QString Product::getName() const {
    return name;
}

double Product::getPrice() const {
    return price;
}
