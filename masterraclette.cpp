#include "masterraclette.h"

Combination *MasterRaclette::player_combination() const
{
    return _player_combination;
}

int MasterRaclette::nb_try() const
{
    return _nb_try;
}

MasterRaclette::MasterRaclette(QWidget *parent)
    : QWidget(parent)
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

void MasterRaclette::launchGame()
{

    if(Parameters::game_mode == 0)
    {
        //Player vs IA
        playModePlayerVsIa();
    }
    else if(Parameters::game_mode == 1)
    {
        //IA vs Player
    }
}

void MasterRaclette::playModePlayerVsIa()
{
    if(Parameters::game_in_progress == false)
    {
        //On génère une nouvelle combinaison secrète lors d'une nouvelle partie
        _secret_combination = new Combination(_ingredients);

        _nb_try = Parameters::nb_try;

        Parameters::game_in_progress = true;
    }

    if(Parameters::game_in_progress == true)
    {
        if(_nb_try > 0)
        {
            //On compte le nombre d'ingrédients présents dans la liste du joueur
            _secret_combination->countIngredient(_ingredients);

            //On compte le nombre d'ingrédients bien et mal placés
            _player_combination->compareGoodPlaceinCombi(_secret_combination);
            _player_combination->compareBadPlaceinCombi(_secret_combination);

            //On informe le joueur
            inputUser(_player_combination->nb_good_ingredient(), _player_combination->nb_bad_ingredient());

            _nb_try -= 1;
            setNbTry(_nb_try);
        }
        else
        {
            Parameters::game_in_progress = false;
        }
    }
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

    _player_combination = new Combination();

    for(int index = 0; index < list_ind_ingredient.size(); index++)
    {
        //On récupère l'ingrédient dans la liste
        ingredient = _ingredients.at(list_ind_ingredient.at(index));

        //On l'ajoute à la combinaison
        _player_combination->setPlayerIngredient(ingredient, index);
    }
}

void MasterRaclette::resetGame()
{
    Parameters::game_in_progress = false;
}

