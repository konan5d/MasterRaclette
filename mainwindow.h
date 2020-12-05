/*
 * @todo: Afficher les règles au démarrage dans une autre fenêtre
 *
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// QT Widget
#include <QMainWindow>
#include <QGroupBox>
#include <QLabel>
#include <QComboBox>
#include <QGridLayout>
#include <QRadioButton>
#include <QPushButton>
#include <QTextEdit>
#include <QHBoxLayout>
#include <QList>
#include <QStringList>
#include <QLineEdit>

//MasterRaclette Widget
#include "ingredientbox.h"

#include "masterraclette.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    MasterRaclette *_masterraclette;
    QWidget *_widget_ui;

    /* ###### UI ###### */
    QGridLayout *_grid_window;

    // Parameters for the game
    QGroupBox *_grbox_game_param;

    //Combination
    QGroupBox *_grbox_combination;
    QStringList *_strlist_ingredient;
    QComboBox *_combo_ing_1;
    QComboBox *_combo_ing_2;
    QComboBox *_combo_ing_3;
    QComboBox *_combo_ing_4;
    QComboBox *_combo_ing_5;
    QComboBox *_combo_ing_6;
    QComboBox *_combo_ing_7;
    QComboBox *_combo_ing_8;
    QList <QComboBox *> _list_combo_ing;

    //Display
    QTextEdit *_textedit_display;

    //Game Info
    QGroupBox *_grbox_game_info;
        /* Player Vs IA */
    QLineEdit *_line_nb_try;

        /* IA vs Player */
    QLineEdit *_line_nb_gen;
    QLineEdit *_line_nb_gen2;

    //Button Group : Quit & Change Game mode
    QHBoxLayout *_hbox_ui_button;
    QPushButton *_ui_play;
    QPushButton *_ui_change_mode;
    QPushButton *_ui_quit;

public:
    MainWindow(QWidget *parent = nullptr);

    //Parameters of game
    QGroupBox *createGameParamGroup(void);

    //Combination
    QGroupBox *createCombinationGroup(void);
    QStringList *generateIngredientList(QList <Ingredient *> list_ingredient);

    //Game info
    QGroupBox *createGameInfoGroup(void);
    QGroupBox *playerVsIaInfo(QGroupBox *group_box);
    QGroupBox *IaVsPlayerInfo(QGroupBox *group_box);

    //Button Group : Quit & Change Game mode
    QHBoxLayout *createUIButtonGroup(void);

    ~MainWindow();

public slots:
    //Parameters of game
    void enableGameParamGroup(bool mode);

    //Combination
    void enableCombinationGroup(bool mode);
    void inputCombination(void);
    //Game info
    void changeInformationDisplayed(int mode);

    //UI Button
    void enablePlayButton(int mode);
    void enableChangeModeButton(int mode);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
