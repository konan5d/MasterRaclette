#include "masterraclette.h"

MasterRaclette::MasterRaclette()
{
    _ingredients.append(new Ingredient("Fromage", 1));
    _ingredients.append(new Ingredient("Cornichon", 2));
    _ingredients.append(new Ingredient("Patate", 3));
    _ingredients.append(new Ingredient("Jambon", 4));
    _ingredients.append(new Ingredient("Vin blanc", 5));
    _ingredients.append(new Ingredient("Mortadelle", 6));
    _ingredients.append(new Ingredient("Chorizo", 7));
    _ingredients.append(new Ingredient("Bacon", 8));

    Parameters::nb_ingredient_available = _ingredients.size();
}

QList<Ingredient *> MasterRaclette::ingredients() const
{
    return _ingredients;
}

/* ############################ SLOTS #######################################*/
void MasterRaclette::setGameMode(int mode)
{
    Parameters::game_mode = mode;
}

void MasterRaclette::setNumberIngredient(int nb_ingredient)
{
    Parameters::nb_ingredient = nb_ingredient;
}

void MasterRaclette::setPlayerCombination(QList <int> list_ind_ingredient)
{
    Ingredient *ingredient = nullptr;

    for(int index = 0; index < list_ind_ingredient.size(); index++)
    {
        //On récupère l'ingrédient dans la liste
        ingredient = _ingredients.at(list_ind_ingredient.at(index));

        //On l'ajoute à la combinaison
        _player_combination.setPlayerIngredient(ingredient, index);
    }
}
