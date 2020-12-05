#ifndef COMBINATION_H
#define COMBINATION_H

#include <QWidget>
#include <QList>
#include "ingredient.h"
#include "parameters.h"
#include "random.h"

//Classe Individu Génétique

class Combination
{
private:
    QList <Ingredient *> _genome;
public:
    Combination();
    Combination(QList <Ingredient *> list_ingredient);

    void setPlayerIngredient(Ingredient *ingredient, int pos_ingredient);
};

#endif // COMBINATION_H
