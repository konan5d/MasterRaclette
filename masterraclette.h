#ifndef MASTERRACLETTE_H
#define MASTERRACLETTE_H

#include <QList>
#include "ingredient.h"
#include "parameters.h"
#include "combination.h"

class MasterRaclette : public QWidget
{
    Q_OBJECT
private:
    QList <Ingredient *> _ingredients;

    //Mode 0 : Player vs IA
    Combination *_secret_combination = new Combination();
    Combination *_player_combination;


    //Game
    bool _game_finish = true;
    int _nb_try = 0;

public:
    MasterRaclette(QWidget *parent = 0);
    QList<Ingredient *> ingredients() const;

    void launchGame();
    void playModePlayerVsIa();

    //virtual ~MasterRaclette();
    Combination *player_combination() const;

    int nb_try() const;

signals:
    //Mode : Player Vs IA
    void inputUser(int nb_good, int nb_bad);
    void setNbTry(int nb_try);
    void gameFinished(bool state);

public slots:
    void setGameMode(int mode);
    void setNumberIngredient(int nb_ingredient);
    void setPlayerCombination(QList <int> list_ind_ingredient);
    void resetGame(void);

};

#endif // MASTERRACLETTE_H
