#ifndef PARAMETERS_H
#define PARAMETERS_H

#include <QObject>
#include <QString>
#include "random.h"
class Parameters : public QObject
{
public:
    Parameters();

    //Paramètres du jeu
    static int game_mode;
    static int nb_try;
    static int nb_ingredient;
    static int nb_ingredient_available;
    static bool game_in_progress;

    //Paramètres Génétique
    static int nb_individu;
    static double best_fitness;
    static int max_generation;
        //Selection : (tournoi)
    static int tournament_size;
    static bool elitisme;
        //Crossover
    static double crossover_rate;

    static int nb_generation;

    static int debug;
    //static void print(QString txt, int d);

    static Random *random_nbr;
};

#endif // PARAMETERS_H
