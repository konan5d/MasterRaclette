#include <QDebug>
#include "parameters.h"
#include "../shared/qstd.h"
using namespace qstd;

int Parameters::game_mode = 0;
int Parameters::nb_try = 10;
int Parameters::nb_ingredient = 4; //max 8
int Parameters::nb_ingredient_available = 0;
bool Parameters::game_in_progress = false;

//Genetique :
int Parameters::nb_individu = 100;
double Parameters::best_fitness;
int Parameters::max_generation = 200;
    //Selection : (tournoi)
int Parameters::tournament_size = 20;
bool Parameters::elitisme = false;

    //Crossover Rate
double Parameters::crossover_rate = 0.5;

//Display Info
bool Parameters::display_population = true;
bool Parameters::display_selection = true;
bool Parameters::display_crossover = true;

int Parameters::nb_generation = 0;

Random *Parameters::random_nbr= new Random(-1);

Parameters::Parameters()
{

}

/*void Parameters::print(QString txt, int d)
{
    if(d<debug)
    {
        cout<<txt<<endl;
    }
}*/
