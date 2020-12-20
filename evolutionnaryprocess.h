#ifndef EVOLUTIONNARYPROCESS_H
#define EVOLUTIONNARYPROCESS_H

#include <QObject>
#include <QWidget>

#include "combination.h"
#include "parameters.h"
#include <QTextEdit>

class EvolutionnaryProcess : public QObject
{
    Q_OBJECT

private:
    QList <Ingredient *> _list_ingredient;

    QList <Combination *> _population;

    Combination *_individu_zero;

    int nb_generation = 0;

    //Evo Process (run_2())
    bool _init_evo_process = false;
    QList <Combination *> _new_population;
    QList <Combination *> _last_population;
    Combination *_bestIndividu;
    double _bestFitness = 0;
    double _fitness = 0;
    int _nb_generation = 0;



public:
    explicit EvolutionnaryProcess(QObject *parent = nullptr);

    EvolutionnaryProcess(QList<Ingredient *> list_ingredient, Combination *individu_zero);
    void initFirstPopulation(void);
    double evaluateFirstIndividu(Combination *individu_zero);

    void run(void);
    void run_2(void);

    //Selection
    QList <Combination *> selection(QList<Combination *> *population);
    Combination *tournament(Combination *indiv1, Combination *indiv2);
    QList <Combination *> crossover(QList<Combination *> *population, float crossover_rate);



signals:
    void refreshGenetiqueInformation(QString data);
};

#endif // EVOLUTIONNARYPROCESS_H
