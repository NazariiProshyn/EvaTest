#include "product.h"

Product::Product(int Id, const QString& Name, double Price)
    : id(Id)
    , name(Name)
    , price(Price)
{
}

int Product::GetId() const {
    return id;
}

QString Product::GetName() const {
    return name;
}

double Product::GetPrice() const {
    return price;
}
