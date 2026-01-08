#ifndef CATALOG_H
#define CATALOG_H

#pragma once

#include <QHash>
/*
 *
 * DB simulation
 *
 */

#include "Product.h"
//BD simulation
class Catalog
{
public:
    Catalog() = default;

    bool contains(int productHash) const;
    Product getProduct(int productHash) const;
private:
    QHash<int, Product> products{
        {1000, {1, "Shampoo", 10.5}},
        {1001, {2, "Toothpaste", 5}},
        {1002, {3, "Toothbrush", 7}},
        {1003, {4, "Gel", 2.44}},
        {1004, {5, "Perfume", 4.63}},
        {1005, {6, "Sponge", 2.22}},
        {1006, {7, "Deodorant", 1}},
        {1007, {8, "Cream", 20}},
        {1008, {9, "IndianInk", 11}},
        {1009, {10, "Hairbrush", 12.5}},
        {1010, {11, "Balm", 21.1}},
        {1011, {12, "Pencil", 24.1}},
        {1012, {13, "Napkins", 1}},
        {1013, {14, "Toilet", 2.5}},
        {1013, {15, "Soap", 3.3}},
        {1015, {16, "Capsule", 20}}
    };
};

#endif // CATALOG_H
