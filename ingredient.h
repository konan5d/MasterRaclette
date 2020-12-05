#ifndef INGREDIENT_H
#define INGREDIENT_H

#include <QString>

class Ingredient
{
private:
    QString _name;
    int _value; //Valeur pour le calcul de fitness (Génétique)
public:
    Ingredient(QString n, int v);
    QString getIngredient() const;
    QString toString();
    int getValue() const;
};

#endif // INGREDIENT_H
