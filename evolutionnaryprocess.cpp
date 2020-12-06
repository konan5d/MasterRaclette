#include "evolutionnaryprocess.h"

EvolutionnaryProcess::EvolutionnaryProcess(QObject *parent) : QObject(parent)
{

}

EvolutionnaryProcess::EvolutionnaryProcess(QList <Ingredient *> list_ingredient, Combination *individu_zero)
{
    //On sauvegarde la liste d'ingrédients
    _list_ingredient = list_ingredient;

    //On sauvegarde le premier individu
    _individu_zero = individu_zero;

    //Calcul du fitness du premier individu
    _individu_zero->setFitness(evaluateFirstIndividu(_individu_zero));

    //Initialisation de la première population, avec le calcul du fitness
    initFirstPopulation();

}

double EvolutionnaryProcess::evaluateFirstIndividu(Combination *individu_zero)
{
    double fitness = 0;

    individu_zero->countIngredient(_list_ingredient);

    foreach (Ingredient *ing, individu_zero->ingredient()) {
        fitness += ing->getValue() * 2;
    }

    return fitness;
}

void EvolutionnaryProcess::initFirstPopulation()
{
    Combination *indiv;

    double fitness = 0;

    for(int index_pop = 0; index_pop < Parameters::nb_individu; index_pop++)
    {
        indiv = new Combination(_list_ingredient);

        fitness = indiv->evaluate(_individu_zero);

        indiv->setFitness(fitness);

        _population.append(indiv);
    }
}

void EvolutionnaryProcess::run()
{
    //Initialisation
    Combination *bestIndividu;

    double bestFitness = 0;

    //On tri la population intiale
    std::sort(_population.begin(), _population.end(), Combination::lessFitnessThan);

    //On récupère l'individu avec le  meilleur fitness
    bestIndividu = _population.first();

    //On cherche le meilleur individu dans les différentes générations
    //Tant qu'on a pas atteint le nombre de génération
    //Ou tant qu'on a pas atteint le fitness de l'individu zéro (entré par l'utilisateur)
    while(nb_generation < Parameters::max_generation && bestFitness < _individu_zero->fitness())
    {

        //Vérification si on trouve l'individu dans la 1ère pop

        //Selection + Elitisme ?
            //Mode de sélection : tournoi

        //Croisement

        //Mutation

        // --> Nouvelle génération

        nb_generation += 1;
    }
}
