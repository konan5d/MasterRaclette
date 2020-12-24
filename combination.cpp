#include "combination.h"

int Combination::nb_good_ingredient() const
{
    return _nb_good_ingredient;
}

int Combination::nb_bad_ingredient() const
{
    return _nb_bad_ingredient;
}

QList<Ingredient *> Combination::ingredient() const
{
    return _ingredient;
}

void Combination::setFitness(double fitness)
{
    _fitness = fitness;
}

double Combination::fitness() const
{
    return _fitness;
}

void Combination::setGenome(Ingredient *gen, int pos)
{
    _ingredient.replace(pos, gen);
}



Combination::Combination()
{

}

Combination::Combination(QList<Ingredient *> list_ingredient)
{
    for(int nb_ingredient = 0; nb_ingredient < Parameters::nb_ingredient; nb_ingredient++)
    {
        int rand_nb_ing = Parameters::random_nbr->get(Parameters::nb_ingredient_available);

        _ingredient.append(list_ingredient.at(rand_nb_ing));
    }
}

void Combination::setPlayerIngredient(Ingredient *ingredient, int pos_ingredient)
{
    _ingredient.insert(pos_ingredient, ingredient);
}

void Combination::countIngredient(QList <Ingredient *> list_ingredient)
{
    int index_ingredient = 0;

    foreach (Ingredient *ing_in_comb, this->_ingredient) //On parcours la combinaison joueur
    {
        foreach (Ingredient *ing_in_list, list_ingredient) //On parcours la liste d'ingrédients
        {
            if(ing_in_comb == ing_in_list) //Si l'ingredient est présent dans les 2 listes, alors on l'enregistre dans le tab
            {
                this->_count_ingredient[index_ingredient] +=1;
                index_ingredient = 0;
                break;
            }
            else
            {
                index_ingredient += 1;
            }
        }
        if(index_ingredient == Parameters::nb_ingredient - 1)
        {
            break;
        }
    }
}

void Combination::compareCombination(Combination *secret)
{
    compareGoodPlaceinCombi(secret);
}

void Combination::compareGoodPlaceinCombi(Combination *secret)
{
    Combination temp_secret = *secret;

    int index_ing_player = 0;
    int index_ing_secret = 0;
    int pos_ing = 0;

    foreach(Ingredient *ing_player, _ingredient)
    {
        //On récupère la position de l'ingrédient dans la liste des ingrédients pour l'enregistrer dans le tableau
        pos_ing = ing_player->getValue() - 1;

        //On cherche l'ingrédient dans toute la liste
        index_ing_secret = temp_secret._ingredient.indexOf(ing_player);

        //Si on trouve l'ingrédient (positions identiques dans les 2 listes)
        if(index_ing_secret == index_ing_player)
        {
            //On le supprime de la liste secret
            temp_secret._ingredient.replace(index_ing_player, nullptr);

            _count_good_ingredient[pos_ing] += 1;

            _nb_good_ingredient += 1;
        }

        index_ing_player += 1;
    }

    compareBadPlaceinCombi(&temp_secret);
}

void Combination::compareBadPlaceinCombi(Combination *temp_secret)
{
    int index_ing_player = 0;
    int index_ing_secret = 0;
    int pos_ing = 0;

    //On parcours la liste des ingrédients de la combinaison joueur / individu
    foreach(Ingredient *ing_player, _ingredient)
    {
        //On récupère la position de l'ingrédient dans la liste des ingrédients pour l'enregistrer dans le tableau
        pos_ing = ing_player->getValue() - 1;

        //Tant que l'ingrédient est présent dans la liste
        while(temp_secret->_ingredient.contains(ing_player))
        {
            index_ing_secret = temp_secret->_ingredient.indexOf(ing_player);

            if(index_ing_secret != index_ing_player)
            {
                //A une position différente
                temp_secret->_ingredient.replace(index_ing_secret, nullptr);

                _count_bad_ingredient[pos_ing] += 1;

                _nb_bad_ingredient += 1;
            }
            if(index_ing_secret == index_ing_player)
            {
                //On le supprime de la liste secret
                temp_secret->_ingredient.replace(index_ing_player, nullptr);

                _count_good_ingredient[pos_ing] += 1;

                _nb_good_ingredient += 1;
            }
        }
        index_ing_player += 1;
    }
}

QString Combination::toString(void)
{
    QString buf = "[";

    foreach(Ingredient *ing, _ingredient)
    {
        buf = buf + ing->toString() + ", ";
    }

    return buf + "]";
}

double Combination::evaluate(Combination *best_individu)
{
    double fitness = 0;

    this->compareCombination(best_individu);

    for(int index_ing = 0; index_ing < Parameters::nb_ingredient; index_ing++)
    {
        if(_count_good_ingredient[index_ing] > 0)
        {
            fitness += _ingredient.at(index_ing)->getValue();
        }

        if(_count_bad_ingredient[index_ing] > 0)
        {
            fitness += (_ingredient.at(index_ing)->getValue()/2);
        }
    }

//    _fitness = fitness;

    return fitness;
}

bool Combination::lessFitnessThan(const Combination *comb1, const Combination *comb2)
{
    return comb1->fitness() > comb2->fitness();
}

void Combination::clearAllTabs()
{
    clearTab(_count_good_ingredient);
    clearTab(_count_bad_ingredient);
}

void Combination::resetValues()
{
    clearAllTabs();
    _nb_good_ingredient = 0;
    _nb_bad_ingredient = 0;
    _fitness = 0;
}

void Combination::clearTab(int *tab)
{
    for(int index_tab = 0; index_tab < 8; index_tab++)
    {
        if(tab[index_tab])
        {
            tab[index_tab] = int(0);
        }
    }
}
