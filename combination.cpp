#include "combination.h"

Combination::Combination()
{

}

Combination::Combination(QList<Ingredient *> list_ingredient)
{
    for(int nb_ingredient = 0; nb_ingredient < Parameters::nb_ingredient; nb_ingredient++)
    {
        int rand_nb_ing = Parameters::random_nbr->get(Parameters::nb_ingredient_available);

        _genome.append(list_ingredient.at(rand_nb_ing));
    }
}

void Combination::setPlayerIngredient(Ingredient *ingredient, int pos_ingredient)
{
    _genome.insert(pos_ingredient, ingredient);
}
