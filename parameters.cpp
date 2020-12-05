#include <QDebug>
#include "parameters.h"
#include "../shared/qstd.h"
using namespace qstd;

int Parameters::game_mode = 0;
int Parameters::nb_try = 10;
int Parameters::nb_ingredient = 4; //max 8
int Parameters::nb_ingredient_available = 0;

//Genetique :
int Parameters::nb_individu = 10;
int Parameters::best_fitness;

Random *Parameters::random_nbr= new Random(0);

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
