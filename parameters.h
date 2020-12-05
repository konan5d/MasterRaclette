#ifndef PARAMETERS_H
#define PARAMETERS_H

#include <QString>
#include "random.h"
class Parameters
{
public:
    Parameters();

    //Paramètres du jeu
    static int game_mode;
    static int nb_try;
    static int nb_ingredient;
    static int nb_ingredient_available;

    //Paramètres Génétique
    static int nb_individu;
    static int best_fitness;

    static int debug;
    //static void print(QString txt, int d);

    static Random *random_nbr;

};

#endif // PARAMETERS_H
