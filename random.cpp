#include "random.h"
#include <QDateTime>

Random::Random(int seed)
{
    if(seed==-1)
        seed=QTime::currentTime().msec();
    qsrand(seed);
}

int Random::get(int max)
{
    int value = qrand()%max;
    return value;
}

double Random::getFloat()
{
    return (qrand()%1001)/1000.0;
}
