#ifndef EVOLUTIONNARYPROCESS_H
#define EVOLUTIONNARYPROCESS_H

#include <QObject>
#include <QWidget>

#include "combination.h"
#include "parameters.h"

class EvolutionnaryProcess : public QObject
{
    Q_OBJECT

private:
    QList <Ingredient *> _list_ingredient;

    QList <Combination *> _population;

    Combination *_individu_zero;

    int nb_generation = 0;

public:
    explicit EvolutionnaryProcess(QObject *parent = nullptr);

    EvolutionnaryProcess(QList<Ingredient *> list_ingredient, Combination *individu_zero);
    void initFirstPopulation(void);
    double evaluateFirstIndividu(Combination *individu_zero);

    void run(void);

signals:

};

#endif // EVOLUTIONNARYPROCESS_H
