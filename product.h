#ifndef PRODUCT_H
#define PRODUCT_H

#pragma once

#include <QString>

class Product
{
public:
    Product() = delete;
    Product(int Id, const QString& Name, double Price);

    int getId() const;
    QString getName() const;
    double getPrice() const;

private:
    int id{0};
    QString name;
    double price{0.0};
};

#endif // PRODUCT_H
