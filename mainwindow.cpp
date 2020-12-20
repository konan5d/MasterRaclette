//TODO : Affichage du mode génétique
//TODO : Défilement automatique
//TODO : Paramètrage des valeurs

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /* Game */
    _masterraclette = new MasterRaclette();
    _strlist_ingredient = generateIngredientList(_masterraclette->ingredients());

    /* UI */
    _widget_ui = new QWidget();
    _grid_window = new QGridLayout();

    _grbox_game_param = createGameParamGroup();
    _textedit_display = new QTextEdit("Display Result !");
    _textedit_display->setReadOnly(true);

    _grbox_combination = createCombinationGroup();
    _grbox_game_info = createGameInfoGroup();
    _hbox_ui_button = createUIButtonGroup();

    //Set Grid Window
    _grid_window->addWidget(_grbox_game_param, 0, 0, 1, 2);
    _grid_window->addWidget(_textedit_display, 1, 0);
    _grid_window->addWidget(_grbox_combination, 1, 1, 2, 1);
    _grid_window->addWidget(_grbox_game_info, 2, 0);
    _grid_window->addLayout(_hbox_ui_button, 3, 0, 1, 2);

    _widget_ui->setLayout(_grid_window);

    //Connect
    connect(_masterraclette, &MasterRaclette::inputUser, [this](int nb_good, int nb_bad){displayResult(nb_good, nb_bad);});
    //connect(_masterraclette->evo(), &EvolutionnaryProcess::refreshInformation, [this](QString data){refreshGenetiqueDisplay(data);});
    connect(_masterraclette, &MasterRaclette::refreshGenetiqueInfoOnDisplay, [this](QString data){refreshGenetiqueDisplay(data);});

    //connect(_masterraclette, &MasterRaclette::gameFinished, [this](bool state){displayResult(state);});

    setCentralWidget(_widget_ui);
}

QGroupBox *MainWindow::createGameParamGroup()
{
    QGridLayout *grid = new QGridLayout();

    //Game mode
    QGroupBox *group_box = new QGroupBox("Game Parameters :");
    QLabel *label_game_mode = new QLabel("Game mode :");
    QComboBox *combo_game_mode = new QComboBox();
    combo_game_mode->addItem("Player VS IA");
    combo_game_mode->addItem("IA VS Player (Genetique)");
    //combo_game_mode->setCurrentIndex(0);

    //Ingredient Number
    QLabel *label_nb_ingredient = new QLabel("Ingredients Number :");
    QRadioButton *radio_4_ingredient = new QRadioButton("4");
    QRadioButton *radio_6_ingredient = new QRadioButton("6");
    QRadioButton *radio_8_ingredient = new QRadioButton("8");

    //Default Ingredient Number
    radio_4_ingredient->setChecked(true);

    //Play Button
    QPushButton *button_intput_param = new QPushButton("Input Parameters / Reset");
    button_intput_param->setFixedHeight(50);

    //Row : 0 (Game mode)
    grid->addWidget(label_game_mode, 0, 0);
    grid->addWidget(combo_game_mode, 0, 1);

    //Row : 1 (Ingredient Number)
    grid->addWidget(label_nb_ingredient, 1, 0);
    grid->addWidget(radio_4_ingredient, 1, 1);
    grid->addWidget(radio_6_ingredient, 1, 2);
    grid->addWidget(radio_8_ingredient, 1, 3);

    //Play Button
    grid->addWidget(button_intput_param, 0, 4, 2, 1);

    group_box->setMaximumHeight(100);
    group_box->setLayout(grid);

    //Signal
    connect(combo_game_mode, QOverload<int>::of(&QComboBox::currentIndexChanged), [=](int const index){_masterraclette->setGameMode(index);});
    connect(combo_game_mode, QOverload<int>::of(&QComboBox::currentIndexChanged), [=](int const index){changeInformationDisplayed(index);});

    connect(radio_4_ingredient, &QRadioButton::toggled, [=](){_masterraclette->setNumberIngredient(4);});
    connect(radio_6_ingredient, &QRadioButton::toggled, [=](){_masterraclette->setNumberIngredient(6);});
    connect(radio_8_ingredient, &QRadioButton::toggled, [=](){_masterraclette->setNumberIngredient(8);});

    //connect(button_intput_param, &QPushButton::clicked, [this](){enableCombinationGroup(false);});
    connect(button_intput_param, &QPushButton::clicked, [this](){enablePlayButton(true);});



    return group_box;
}

QGroupBox *MainWindow::createCombinationGroup()
{
    QGridLayout *grid = new QGridLayout();
    QGroupBox *group_box = new QGroupBox("Raclette Combination :");

    //Combo box to input ingredient for combination

    QLabel *label_ing_1 = new QLabel("Ingredient 1 :");
    QComboBox *_combo_ing_1 = new QComboBox();
    _combo_ing_1->addItems(*_strlist_ingredient);
    _combo_ing_1->setCurrentIndex(-1);
    _list_combo_ing.append(_combo_ing_1);

    QLabel *label_ing_2 = new QLabel("Ingredient 2 :");
    QComboBox *_combo_ing_2 = new QComboBox();
    _combo_ing_2->addItems(*_strlist_ingredient);
    _combo_ing_2->setCurrentIndex(-1);
    _list_combo_ing.append(_combo_ing_2);

    QLabel *label_ing_3 = new QLabel("Ingredient 3 :");
    QComboBox *_combo_ing_3 = new QComboBox();
    _combo_ing_3->addItems(*_strlist_ingredient);
    _combo_ing_3->setCurrentIndex(-1);
    _list_combo_ing.append(_combo_ing_3);

    QLabel *label_ing_4 = new QLabel("Ingredient 4 :");
    QComboBox *_combo_ing_4 = new QComboBox();
    _combo_ing_4->addItems(*_strlist_ingredient);
    _combo_ing_4->setCurrentIndex(-1);
    _list_combo_ing.append(_combo_ing_4);

    QLabel *label_ing_5 = new QLabel("Ingredient 5 :");
    _combo_ing_5 = new QComboBox();
    _combo_ing_5->addItems(*_strlist_ingredient);
    _combo_ing_5->setCurrentIndex(-1);
    _combo_ing_5->setDisabled(true);
    _list_combo_ing.append(_combo_ing_5);

    QLabel *label_ing_6 = new QLabel("Ingredient 6 :");
    _combo_ing_6 = new QComboBox();
    _combo_ing_6->addItems(*_strlist_ingredient);
    _combo_ing_6->setCurrentIndex(-1);
    _combo_ing_6->setDisabled(true);
    _list_combo_ing.append(_combo_ing_6);

    QLabel *label_ing_7 = new QLabel("Ingredient 7 :");
    _combo_ing_7 = new QComboBox();
    _combo_ing_7->addItems(*_strlist_ingredient);
    _combo_ing_7->setCurrentIndex(-1);
    _combo_ing_7->setDisabled(true);
    _list_combo_ing.append(_combo_ing_7);

    QLabel *label_ing_8 = new QLabel("Ingredient 8 :");
    _combo_ing_8 = new QComboBox();
    _combo_ing_8->addItems(*_strlist_ingredient);
    _combo_ing_8->setCurrentIndex(-1);
    _combo_ing_8->setDisabled(true);
    _list_combo_ing.append(_combo_ing_8);

    //Grid
    grid->addWidget(label_ing_1, 0, 0);
    grid->addWidget(_combo_ing_1, 0, 1);

    grid->addWidget(label_ing_2, 1, 0);
    grid->addWidget(_combo_ing_2, 1, 1);

    grid->addWidget(label_ing_3, 2, 0);
    grid->addWidget(_combo_ing_3, 2, 1);

    grid->addWidget(label_ing_4, 3, 0);
    grid->addWidget(_combo_ing_4, 3, 1);

    grid->addWidget(label_ing_5, 4, 0);
    grid->addWidget(_combo_ing_5, 4, 1);

    grid->addWidget(label_ing_6, 5, 0);
    grid->addWidget(_combo_ing_6, 5, 1);

    grid->addWidget(label_ing_7, 6, 0);
    grid->addWidget(_combo_ing_7, 6, 1);

    grid->addWidget(label_ing_8, 7, 0);
    grid->addWidget(_combo_ing_8, 7, 1);

    //Input Button
    QPushButton *input_button = new QPushButton("Input Combination");
    input_button->setFixedHeight(50);

    grid->addWidget(input_button, 8, 0, 1, 2);

    group_box->setLayout(grid);

    group_box->setDisabled(true);

    //Slots
    connect(input_button, &QPushButton::clicked, this, &MainWindow::inputCombination);

    return group_box;
}

QStringList *MainWindow::generateIngredientList(QList<Ingredient *> list_ingredient)
{

    QStringList *string_list = new QStringList();

    foreach (Ingredient *ing, list_ingredient) {
        string_list->append(ing->getIngredient());
    }

    return string_list;
}

QGroupBox *MainWindow::createGameInfoGroup()
{
    QGroupBox *group_box = new QGroupBox("Game Informations :");

    if(Parameters::game_mode == 0)
    {
        //Player Vs IA
        group_box = playerVsIaInfo(group_box);
    }

    else if(Parameters::game_mode == 1)
    {
        //IA vs Player (Génétique)
    }

    return  group_box;
}

QGroupBox *MainWindow::playerVsIaInfo(QGroupBox *group_box)
{
    QGridLayout *grid = new QGridLayout();

    QLabel *label_nb_try = new QLabel("Number of trials :");
    _line_nb_try = new QLineEdit();
    _line_nb_try->setReadOnly(true);
    _line_nb_try->setText(QString::number(Parameters::nb_try, 10));

    QLabel *label_nb_try_player = new QLabel("Number of trials remaining:");
    _line_nb_try_player = new QLineEdit();
    _line_nb_try_player->setReadOnly(true);
    _line_nb_try_player->setText(QString::number(Parameters::nb_try, 10));

    grid->addWidget(label_nb_try, 0, 0);
    grid->addWidget(_line_nb_try, 0, 1);
    grid->addWidget(label_nb_try_player, 1, 0);
    grid->addWidget(_line_nb_try_player, 1, 1);

    group_box->setLayout(grid);

    //Connect
    connect(_masterraclette, &MasterRaclette::setNbTry, [this](int value){refreshGameInfo(0, value);});

    return group_box;
}

QGroupBox *MainWindow::IaVsPlayerInfo(QGroupBox *group_box)
{
    QGridLayout *grid = new QGridLayout();

    QLabel *label_max_gen = new QLabel("(Parameters) Max Generation Number :");
    _line_max_gen = new QLineEdit();
    _line_max_gen->setText(QString::number(Parameters::max_generation));

    QLabel *label_nb_indiv = new QLabel("(Parameters) Number of Individu :");
    _line_nb_indiv = new QLineEdit();
    _line_nb_indiv->setText(QString::number(Parameters::nb_individu));

    QLabel *label_tournament_size = new QLabel("(Selection) Tournament Size :");
    _line_tournament_size = new QLineEdit();
    _line_tournament_size->setText(QString::number(Parameters::tournament_size));

    QLabel *label_crossover_rate = new QLabel("(Crossover) Rate (0 -> 1) :");
    _line_crossover_rate = new QLineEdit();
    _line_crossover_rate->setText(QString::number(Parameters::crossover_rate));

    QLabel *label_nb_gen = new QLabel("(Result) Generation Number :");
    _line_nb_gen = new QLineEdit();
    _line_nb_gen->setReadOnly(true);
    _line_nb_gen->setText("0");

    QLabel *label_best_fitness = new QLabel("(Result) Best Fitness :");
    _line_best_fitness = new QLineEdit();
    _line_best_fitness->setReadOnly(true);
    _line_best_fitness->setText("0");

    grid->addWidget(label_max_gen, 0, 0);
    grid->addWidget(_line_max_gen, 0, 1);

    grid->addWidget(label_nb_indiv, 1, 0);
    grid->addWidget(_line_nb_indiv, 1, 1);

    grid->addWidget(label_tournament_size, 2, 0);
    grid->addWidget(_line_tournament_size, 2, 1);

    grid->addWidget(label_crossover_rate, 3, 0);
    grid->addWidget(_line_crossover_rate, 3, 1);

    grid->addWidget(label_nb_gen, 4, 0);
    grid->addWidget(_line_nb_gen, 4, 1);

    grid->addWidget(label_best_fitness, 5, 0);
    grid->addWidget(_line_best_fitness, 5, 1);

    group_box->setLayout(grid);

    connect(_line_max_gen, &QLineEdit::editingFinished, this, [this](){setMaxGenerationNumber(_line_max_gen->text());});
    connect(_line_nb_indiv, &QLineEdit::editingFinished, this, [this](){setNumberOfIndividu(_line_nb_indiv->text());});
    connect(_line_tournament_size, &QLineEdit::editingFinished, this, [this](){setTournamentSize(_line_tournament_size->text());});
    connect(_line_crossover_rate, &QLineEdit::editingFinished, this, [this](){setCrosssoverRate(_line_crossover_rate->text());});


    return group_box;
}

QHBoxLayout *MainWindow::createUIButtonGroup()
{
    QHBoxLayout *hbox_layout = new QHBoxLayout();

    _ui_play = new QPushButton("Play !");
    _ui_change_mode = new QPushButton("Change Game Mode");
    _ui_quit = new QPushButton("Quit Game");

    _ui_play->setFixedHeight(50);
    _ui_change_mode->setFixedHeight(50);
    _ui_quit->setFixedHeight(50);

    hbox_layout->addWidget(_ui_play);
    hbox_layout->addWidget(_ui_change_mode);
    hbox_layout->addWidget(_ui_quit);

    _ui_play->setDisabled(true);
    _ui_change_mode->setDisabled(true);

    //Signal
    connect(_ui_play, &QPushButton::clicked, [this](){enableGameParamGroup(false);});
    connect(_ui_play, &QPushButton::clicked, [this](){enableChangeModeButton(true);});
    connect(_ui_play, &QPushButton::clicked, [this](){enablePlayButton(false);});
    connect(_ui_play, &QPushButton::clicked, [this](){enableCombinationGroup(true);});
    connect(_ui_play, &QPushButton::clicked, [this](){_masterraclette->resetGame();});

    connect(_ui_change_mode, &QPushButton::clicked, [this](){enableGameParamGroup(true);});
    connect(_ui_change_mode, &QPushButton::clicked, [this](){enableCombinationGroup(false);});

    connect(_ui_quit, &QPushButton::clicked, this, &QWidget::close);


    return hbox_layout;
}

void MainWindow::displayInfo(QString data)
{
    _textedit_display->setPlainText(data);
}

MainWindow::~MainWindow()
{
    delete ui;
}
/* ############################ SLOTS #######################################*/

void MainWindow::enableGameParamGroup(bool mode)
{
    _grbox_game_param->setDisabled(!mode);
}

void MainWindow::enableCombinationGroup(bool mode)
{
    _grbox_combination->setDisabled(!mode);

    if(Parameters::nb_ingredient >= 6)
    {
        _combo_ing_5->setDisabled(false);
        _combo_ing_6->setDisabled(false);

        if(Parameters::nb_ingredient == 8)
        {
            _combo_ing_7->setDisabled(false);
            _combo_ing_8->setDisabled(false);
        }
    }
    else
    {
        _combo_ing_5->setDisabled(true);
        _combo_ing_6->setDisabled(true);
        _combo_ing_7->setDisabled(true);
        _combo_ing_8->setDisabled(true);
    }

    _textedit_display->clear();
    _textedit_display->insertPlainText("Please input your combinaison, and press \"Input Combination \".\n");
}

void MainWindow::inputCombination()
{
    QList <int> list_ind_ingredient;

    //Save index of ingredient (input user)
    for(int index_combo = 0 ; index_combo < Parameters::nb_ingredient; index_combo++)
    {

        //On parcours la liste des entrées utilisateurs (combo box) et on récupère les index des choix
        int ind_ingredient = _list_combo_ing.at(index_combo)->currentIndex();

        //On vérifie que le joueur a choisi un ingrédient
        if(ind_ingredient != -1)
        {
            //On enregistre les index dans la liste
            list_ind_ingredient.append(ind_ingredient);
        }
    }


    if(list_ind_ingredient.size() == Parameters::nb_ingredient)
    {
        //Si le joueur a rentré suffisement d'ingrédients pour jouer
        _masterraclette->setPlayerCombination(list_ind_ingredient);

        _textedit_display->clear();

        _masterraclette->launchGame();

    }
    else
    {
        _textedit_display->insertPlainText("Oh noooo! ! You don't have enough ingredients to eat a raclette. Your friends are gone :(\n");
        _textedit_display->insertPlainText("Please choose many ingredients !\n");

    }
}

void MainWindow::changeInformationDisplayed(int mode)
{
    //Clear Layout
    if(_grbox_game_info->layout())
    {
        while(_grbox_game_info->layout()->count() > 0)
        {
            QLayoutItem *item = _grbox_game_info->layout()->takeAt(0);
            QWidget *widget = item->widget();

            if(widget)
            {
                delete widget;
            }

            delete item;
        }
    }

    delete _grbox_game_info->layout();

    //Set a new layout
    if(mode == 0)
    {
        //Player Vs IA
        _grbox_game_info = playerVsIaInfo(_grbox_game_info);
    }

    else if(mode == 1)
    {
        //IA vs Player (Génétique)
        _grbox_game_info = IaVsPlayerInfo(_grbox_game_info);
    }

    _widget_ui->update();
}

void MainWindow::enablePlayButton(int mode)
{
    _ui_play->setDisabled(!mode);
}

void MainWindow::enableChangeModeButton(int mode)
{
    _ui_change_mode->setDisabled(!mode);
}

//Mode : Player Vs IA
void MainWindow::displayResult(int nb_good_ing, int nb_bad_ing)
{
    _textedit_display->insertPlainText("Trials Number : " + QString::number(_masterraclette->nb_try(), 10)+"\n");

    _textedit_display->insertPlainText("Number of good ingredient : ");
    _textedit_display->insertPlainText(QString::number(nb_good_ing, 10)+"\n");

    _textedit_display->insertPlainText("Number of bad ingredient : ");
    _textedit_display->insertPlainText(QString::number(nb_bad_ing, 10)+"\n");

    _textedit_display->insertPlainText("Combination = " + _masterraclette->player_combination()->toString() + "\n");

}

void MainWindow::refreshGameInfo(int mode, int value)
{
    if(mode == 0)
    {
        _line_nb_try_player->setText(QString::number(value, 10));
    }
    else if (mode == 1)
    {
        //Nothing to do
    }
}

void MainWindow::refreshGenetiqueDisplay(QString data)
{
    _textedit_display->insertPlainText(data);

    _line_best_fitness->setText(QString::number(Parameters::best_fitness));
    _line_nb_gen->setText(QString::number(Parameters::nb_generation));
}

void MainWindow::setMaxGenerationNumber(QString value)
{
    bool str_to_int = false;

    int temp_value = value.toInt(&str_to_int, 10);

    //Verify Int conversion
    if(str_to_int)
    {
        Parameters::max_generation = temp_value;
    }
}

void MainWindow::setNumberOfIndividu(QString value)
{
    bool str_to_int = false;

    int temp_value = value.toInt(&str_to_int, 10);

    //Verify Int conversion
    if(str_to_int)
    {
        Parameters::nb_individu = temp_value;
    }
}

void MainWindow::setTournamentSize(QString value)
{
    bool str_to_int = false;

    int temp_value = value.toInt(&str_to_int, 10);

    //Verify Int conversion
    if(str_to_int)
    {
        Parameters::tournament_size = temp_value;
    }
}

void MainWindow::setCrosssoverRate(QString value)
{
    bool str_to_double = false;

    double temp_value = value.toDouble(&str_to_double);

    //Verify Int conversion
    if(str_to_double)
    {
        Parameters::crossover_rate = temp_value;
    }
}
