#include "catalog.h"

bool Catalog::contains(int productHash) const
{
    return products.contains(productHash);
}

Product Catalog::getProduct(int productHash) const
{
    return products.value(productHash);
}
