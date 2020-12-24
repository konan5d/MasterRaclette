#include "ingredient.h"

int Ingredient::getValue() const
{
    return _value;
}

Ingredient::Ingredient(QString n, int v)
{
    _name = n;
    _value = v;
}

QString Ingredient::getIngredient() const
{
    return _name;
}

QString Ingredient::toString()
{
    return this->getIngredient();
}
