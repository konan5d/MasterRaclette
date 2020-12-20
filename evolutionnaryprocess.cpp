//TODO : Mutation
//TODO : Revoir le calcul du fitness

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
    int temp_generation = 0;
    //Initialisation
    QList <Combination *> new_population;
    QList <Combination *> last_population;
    //Combination == class Individu
    Combination *bestIndividu;

    double bestFitness = 0;
    double fitness = 0;

    //On tri la population intiale
    std::sort(_population.begin(), _population.end(), Combination::lessFitnessThan);

    //On récupère l'individu avec le  meilleur fitness
    bestIndividu = _population.first();

    //Vérification si on trouve l'individu dans la 1ère pop
    bestFitness = bestIndividu->fitness();

    last_population = _population;

    refreshGenetiqueInformation("---------------------------------- Generation 0 (Initialisation) ----------------------------------\n");

    //    if(Parameters::display_population)
    //    {
    //        for(int index_pop = 0; index_pop < Parameters::nb_individu; index_pop++)
    //        {
    //            refreshGenetiqueInformation("Individu " + QString::number(index_pop) + " : "+ last_population.at(index_pop)->toString());
    //            refreshGenetiqueInformation(" ; Fitness = " + QString::number(last_population.at(index_pop)->fitness()) + "\n");
    //        }
    //    }

    displayPopulation(last_population);

    //On cherche le meilleur individu dans les différentes générations
    //Tant qu'on a pas atteint le nombre de génération
    //Ou tant qu'on a pas atteint le fitness de l'individu zéro (entré par l'utilisateur)
    while(nb_generation <= Parameters::max_generation && bestFitness < _individu_zero->fitness())
    {
        refreshGenetiqueInformation("---------------------------------- Generation " + QString::number(nb_generation, 10) + " ----------------------------------\n");

        if(Parameters::elitisme == true)
        {
            new_population.append(bestIndividu);

            if(Parameters::display_population)
            {
                refreshGenetiqueInformation("Best individu : " + bestIndividu->toString() + "\n");
            }

        }

        //Selection : tournoi
        new_population = selection(&last_population);
        //new_population = new_population + this->selection(last_population);

        //Croisement
        new_population = new_population + this->crossover(&last_population, Parameters::crossover_rate);

        //Mutation


        int size_pop = new_population.size();

        for(int nb_indiv=0; nb_indiv < Parameters::nb_individu - size_pop; nb_indiv++)
        {
            new_population.append(new Combination(_list_ingredient));
        }


        foreach(Combination *indiv, new_population)
        {
            indiv->resetValues();

            fitness = indiv->evaluate(_individu_zero);

            indiv->setFitness(fitness);
        }

        //On tri la nouvelle génération
        std::sort(new_population.begin(), new_population.end(), Combination::lessFitnessThan);

        //On récupère l'individu avec le  meilleur fitness
        bestIndividu = new_population.first();

        bestFitness = bestIndividu->fitness();

        refreshGenetiqueInformation("\nBest individu : " + bestIndividu->toString() + "\n");
        refreshGenetiqueInformation("Fitness = " + QString::number(bestFitness) + "\n\n");

        last_population = new_population;
        // --> Nouvelle génération

        nb_generation += 1;
    }

    Parameters::nb_generation = nb_generation;
    Parameters::best_fitness = bestFitness;

    refreshGenetiqueInformation("---------------------------------- Process Completed  ----------------------------------\n");


    //Affichage des infos : gen + fitness
}

//void EvolutionnaryProcess::run_2()
//{
//    if(_init_evo_process == false)
//    {
//        //On tri la population intiale
//        std::sort(_population.begin(), _population.end(), Combination::lessFitnessThan);

//        //On récupère l'individu avec le  meilleur fitness
//        _bestIndividu = _population.first();

//        //Vérification si on trouve l'individu dans la 1ère pop
//        _bestFitness = _bestIndividu->fitness();

//        _last_population = _population;
//    }
//}

QList<Combination *> EvolutionnaryProcess::selection(QList <Combination *> *population)
{
    QList <Combination *> selected_individu;
    Combination *bestIndividu;
    Combination *individu1;
    Combination *individu2;

    if(Parameters::display_selection)
    {
        refreshGenetiqueInformation("------ Selection ------\n");
    }

    for(int nb_turn = 0; nb_turn < Parameters::tournament_size; nb_turn++)
    {
        individu1 = population->takeAt(Parameters::random_nbr->get(population->size()));
        individu2 = population->takeAt(Parameters::random_nbr->get(population->size()));

        bestIndividu = tournament(individu1, individu2);

        if(Parameters::display_selection)
        {
            refreshGenetiqueInformation(" -- Tournament number " + QString::number(nb_turn) + "\n");
            refreshGenetiqueInformation("   Individu 1 : " + individu1->toString() + "; Fitness = " +  QString::number(individu1->fitness()) + "\n");
            refreshGenetiqueInformation("   Individu 2 : " + individu2->toString() + "; Fitness = " + QString::number(individu2->fitness()) + "\n");
            refreshGenetiqueInformation("   => Winner : " + bestIndividu->toString() + "; Fitness = " + QString::number(bestIndividu->fitness()) + "\n");
        }

        selected_individu.append(bestIndividu);

    }

    return selected_individu;
}

Combination *EvolutionnaryProcess::tournament(Combination *indiv1, Combination *indiv2)
{
    if(indiv1->fitness() > indiv2->fitness())
    {
        return indiv1;
    }
    else if(indiv1->fitness() < indiv2->fitness())
    {
        return indiv2;
    }
    else
    {
        return indiv1;
    }
}

QList<Combination *> EvolutionnaryProcess::crossover(QList <Combination *> *population, float crossover_rate)
{

    //TODO : setter pour le genome

    int nb_indiv = 20;

    QList <Combination *> temp_pop;

    for(int index = 0; index < nb_indiv; index++)
    {

        Combination *indiv_1 = population->takeAt(Parameters::random_nbr->get(population->size()));
        Combination *indiv_2 = population->takeAt(Parameters::random_nbr->get(population->size()));

        int cross_rate_1 = int(Parameters::nb_ingredient * crossover_rate);
        int cross_rate_2 = Parameters::nb_ingredient - cross_rate_1;

        Ingredient *temp_ing;

        for(int index_genome = 0; index_genome < cross_rate_1; index_genome++)
        {
            temp_ing = indiv_1->ingredient().at(index_genome);

            indiv_2->setGenome(temp_ing, index_genome);
        }

        for(int index_genome = cross_rate_1; index_genome < cross_rate_2; index_genome++)
        {
            temp_ing = indiv_2->ingredient().at(index_genome);

            indiv_1->setGenome(temp_ing, index_genome);
        }

        indiv_1->resetValues();
        indiv_2->resetValues();

        temp_pop.append(indiv_1);
        temp_pop.append(indiv_2);
    }

    return temp_pop;

}

void EvolutionnaryProcess::displayPopulation(QList<Combination *> population)
{
    if(Parameters::display_population)
    {
        for(int index_pop = 0; index_pop < Parameters::nb_individu; index_pop++)
        {
            refreshGenetiqueInformation("Individu " + QString::number(index_pop) + " : "+ population.at(index_pop)->toString() + "\n");
            refreshGenetiqueInformation("   Fitness = " + QString::number(population.at(index_pop)->fitness()) + "\n");
            refreshGenetiqueInformation("   Number of good ingredient : " + QString::number(population.at(index_pop)->nb_good_ingredient()) + "\n");
            refreshGenetiqueInformation("   Number of bad ingredient : " + QString::number(population.at(index_pop)->nb_bad_ingredient()) + "\n");
        }
    }
}

