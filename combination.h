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
    QList <Ingredient *> _ingredient; //List of genome

    //Compare with secret combination
    int _count_ingredient[8] = {0,0,0,0,0,0,0,0};
    int _count_good_ingredient[8] = {0,0,0,0,0,0,0,0};
    int _count_bad_ingredient[8] = {0,0,0,0,0,0,0,0};

    //Counter : good & bad ingredient
    int _nb_good_ingredient = 0;
    int _nb_bad_ingredient = 0;

public:
    Combination();
    Combination(QList <Ingredient *> list_ingredient);

    void setPlayerIngredient(Ingredient *ingredient, int pos_ingredient);

    void countIngredient(QList<Ingredient *> list_ingredient);

    void compareCombination(Combination *secret);
    void compareGoodPlaceinCombi(Combination *secret);
    void compareBadPlaceinCombi(Combination *secret);

    int nb_good_ingredient() const;
    int nb_bad_ingredient() const;

    QString toString(void);


};

#endif // COMBINATION_H
