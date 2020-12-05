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
    _grid_window->addWidget(_grbox_combination, 1, 1);
    _grid_window->addWidget(_grbox_game_info, 2, 0);
    _grid_window->addLayout(_hbox_ui_button, 3, 0, 1, 2);

    _widget_ui->setLayout(_grid_window);

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
    QPushButton *button_play = new QPushButton("Play !");
    button_play->setFixedHeight(50);

    //Row : 0 (Game mode)
    grid->addWidget(label_game_mode, 0, 0);
    grid->addWidget(combo_game_mode, 0, 1);

    //Row : 1 (Ingredient Number)
    grid->addWidget(label_nb_ingredient, 1, 0);
    grid->addWidget(radio_4_ingredient, 1, 1);
    grid->addWidget(radio_6_ingredient, 1, 2);
    grid->addWidget(radio_8_ingredient, 1, 3);

    //Play Button
    grid->addWidget(button_play, 0, 4, 2, 1);

    group_box->setMaximumHeight(100);
    group_box->setLayout(grid);

    //Signal
    connect(combo_game_mode, QOverload<int>::of(&QComboBox::currentIndexChanged), [=](int const index){_masterraclette->setGameMode(index);});
    connect(combo_game_mode, QOverload<int>::of(&QComboBox::currentIndexChanged), [=](int const index){changeInformationDisplayed(index);});

    connect(radio_4_ingredient, &QRadioButton::toggled, [=](){_masterraclette->setNumberIngredient(4);});
    connect(radio_6_ingredient, &QRadioButton::toggled, [=](){_masterraclette->setNumberIngredient(6);});
    connect(radio_8_ingredient, &QRadioButton::toggled, [=](){_masterraclette->setNumberIngredient(8);});
    connect(button_play, &QPushButton::clicked, [this](){enableCombinationGroup(false);});

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

    QLabel *label_nb_try = new QLabel("Number Try :");
    _line_nb_try = new QLineEdit();
    _line_nb_try->setReadOnly(true);
    _line_nb_try->setText("It's a try");

    grid->addWidget(label_nb_try, 0, 0);
    grid->addWidget(_line_nb_try, 0, 1);

    group_box->setLayout(grid);

    return group_box;
}

QGroupBox *MainWindow::IaVsPlayerInfo(QGroupBox *group_box)
{
    QGridLayout *grid = new QGridLayout();

    QLabel *label_nb_gen = new QLabel("Generation Number :");
    _line_nb_gen = new QLineEdit();
    _line_nb_gen->setReadOnly(true);

    grid->addWidget(label_nb_gen, 0, 0);
    grid->addWidget(_line_nb_gen, 0, 1);

    group_box->setLayout(grid);

    return group_box;
}

QHBoxLayout *MainWindow::createUIButtonGroup()
{
    QHBoxLayout *hbox_layout = new QHBoxLayout();

    _ui_change_mode = new QPushButton("Change Game Mode");
    _ui_quit = new QPushButton("Quit Game");

    _ui_change_mode->setFixedHeight(50);
    _ui_quit->setFixedHeight(50);

    hbox_layout->addWidget(_ui_change_mode);
    hbox_layout->addWidget(_ui_quit);

    _ui_change_mode->setDisabled(true);

    //Signal
    connect(_ui_quit, &QPushButton::clicked, this, &QWidget::close);


    return hbox_layout;
}

MainWindow::~MainWindow()
{
    delete ui;
}

/* ############################ SLOTS #######################################*/
void MainWindow::enableCombinationGroup(bool mode)
{
    _grbox_combination->setDisabled(mode);

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
    _textedit_display->insertPlainText("Please input your combinaison ! \n");

}

void MainWindow::inputCombination()
{
    QList <int> list_ind_ingredient;

    for(int index_combo = 0 ; index_combo < Parameters::nb_ingredient; index_combo++)
    {

        //On parcours la liste des entrées utilisateurs (combo box) et on récupère les index des choix
        int ind_ingredient = _list_combo_ing.at(index_combo)->currentIndex();

        //On vérifie que le joueur a choisi un ingrédient
        if(ind_ingredient != -1)
        {
            //On enregistre less index dans la liste
            list_ind_ingredient.append(ind_ingredient);
        }
    }

    if(list_ind_ingredient.size() == Parameters::nb_ingredient)
    {
        //Si le joueur a rentré suffisement d'ingrédients pour jouer
        _masterraclette->setPlayerCombination(list_ind_ingredient);

        _textedit_display->insertPlainText("So Great !\n");
    }
    else
    {
        _textedit_display->insertPlainText("Oh noooo! ! You don't have enough ingredients to eat a raclette. Your friends are gone :(\n");
        _textedit_display->insertPlainText("Please choose many ingredients !\n");
    }
}

void MainWindow::changeInformationDisplayed(int mode)
{

}

