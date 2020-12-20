#ifndef MASTERRACLETTE_H
#define MASTERRACLETTE_H

#include <QList>
#include "ingredient.h"
#include "parameters.h"
#include "combination.h"
#include "evolutionnaryprocess.h"
#include <QTextEdit>

class MasterRaclette : public QWidget
{
    Q_OBJECT
private:
    QList <Ingredient *> _ingredients;

    Combination *_player_combination;

    //Mode 0 : Player vs IA
    Combination *_secret_combination = new Combination();

    //Mode  : IA vs Player
    EvolutionnaryProcess *_evo;

    //Game
    bool _game_finish = true;
    int _nb_try = 0;

    //Display
    QTextEdit *_display;

public:
    MasterRaclette(QWidget *parent = 0);
    QList<Ingredient *> ingredients() const;

    void launchGame();
    void playModePlayerVsIa();
    void playModeIaVsPlayer();

    Combination *player_combination() const;

    int nb_try() const;

    EvolutionnaryProcess *evo() const;

signals:
    //Mode : Player Vs IA
    void inputUser(int nb_good, int nb_bad);
    void setNbTry(int nb_try);
    void gameFinished(bool state);

    void refreshGenetiqueInfoOnDisplay(QString data);

public slots:
    void setGameMode(int mode);
    void setNumberIngredient(int nb_ingredient);
    void setPlayerCombination(QList <int> list_ind_ingredient);
    void resetGame(void);

    void setGenetiqueInfo(QString data);

};

#endif // MASTERRACLETTE_H
