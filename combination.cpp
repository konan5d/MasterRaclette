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

void Combination::setFitness(int fitness)
{
    _fitness = fitness;
}

int Combination::fitness() const
{
    return _fitness;
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
    compareBadPlaceinCombi(secret);
}

void Combination::compareGoodPlaceinCombi(Combination *secret)
{
    int index_player = 0;
    int index_secrete = 0;

    foreach (Ingredient *ing_player, this->_ingredient)
    {
        //Position de l'ingrédient dans la liste
        int ing_pos = ing_player->getValue() - 1;

        foreach (Ingredient *ing_secret, secret->_ingredient)
        {
            if((ing_player == ing_secret) && (index_player == index_secrete))
            {
                this->_count_good_ingredient[ing_pos] += 1;

                secret->_count_ingredient[ing_pos] -= 1;

                _nb_good_ingredient += 1;

                index_secrete = 0;

                break;
            }

            index_secrete += 1;
        }

        index_secrete = 0;
        index_player += 1;
    }
}

void Combination::compareBadPlaceinCombi(Combination *secret)
{
    int index_player = 0;
    int index_secrete = 0;

    foreach (Ingredient *ing_player, this->_ingredient)
    {
        //Position de l'ingrédient dans la liste
        int ing_pos = ing_player->getValue() - 1;

        foreach (Ingredient *ing_secret, secret->_ingredient)
        {
            if((ing_player == ing_secret) && (index_player != index_secrete)) //Même ingrédient, index différent
            {
                if(secret->_count_ingredient[ing_pos] > 0) //On vérifie qu'il n'a pas été déjà trouvé (_nb_good_ingredient)
                {
                    this->_count_bad_ingredient[ing_pos] += 1;

                    secret->_count_ingredient[ing_pos] -= 1;

                    _nb_bad_ingredient += 1;

                    index_secrete = 0;

                    break;
                }
            }
            index_secrete += 1;
        }

        index_secrete = 0;
        index_player += 1;
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
            fitness += _ingredient.at(index_ing)->getValue()*2;
        }

        if(_count_bad_ingredient[index_ing] > 0)
        {
            fitness += _ingredient.at(index_ing)->getValue()*1;
        }
    }

    return fitness;
}

bool Combination::lessFitnessThan(const Combination *comb1, const Combination *comb2)
{
    return comb1->fitness() > comb2->fitness();
}
