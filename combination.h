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

    //Comparaison avec la combinaison secrete / individu zero
    int _count_ingredient[8] = {0,0,0,0,0,0,0,0};
    int _count_good_ingredient[8] = {0,0,0,0,0,0,0,0};
    int _count_bad_ingredient[8] = {0,0,0,0,0,0,0,0};

    //Compteur : Nombre d'ingrédients valide ou non
    int _nb_good_ingredient = 0;
    int _nb_bad_ingredient = 0;

    //Génétique
    double _fitness = 0;

public:
    Combination();
    Combination(QList <Ingredient *> list_ingredient);


    void setPlayerIngredient(Ingredient *ingredient, int pos_ingredient);

    void countIngredient(QList<Ingredient *> list_ingredient);
    void compareCombination(Combination *secret);
    void compareGoodPlaceinCombi(Combination *secret);
    void compareBadPlaceinCombi(Combination *secret);

//    void compareIngredientPlace(Combination *secret);

    int nb_good_ingredient() const;
    int nb_bad_ingredient() const;

    QString toString(void);

    // Génétique
    double evaluate(Combination *best_individu);

    QList<Ingredient *> ingredient() const;
    void setFitness(double fitness);
    double fitness() const;

    void setGenome(Ingredient *gen, int pos);

    static bool lessFitnessThan(const Combination *comb1, const Combination *comb2);

    void clearTab(int *tab);
    void clearAllTabs(void);
    void resetValues(void);

};

#endif // COMBINATION_H
