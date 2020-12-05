#ifndef MASTERRACLETTE_H
#define MASTERRACLETTE_H

#include <QList>
#include "ingredient.h"
#include "parameters.h"
#include "combination.h"

class MasterRaclette : QWidget
{
private:
    QList <Ingredient *> _ingredients;

    //Mode 0 : Player vs IA
    Combination _player_combination;

public:
    MasterRaclette();
    QList<Ingredient *> ingredients() const;

public slots:
    void setGameMode(int mode);
    void setNumberIngredient(int nb_ingredient);
    void setPlayerCombination(QList <int> list_ind_ingredient);
};

#endif // MASTERRACLETTE_H
