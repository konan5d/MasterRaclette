#include "ingredientbox.h"

IngredientBox::IngredientBox(int nb, QWidget *parent) : QWidget(parent)
{
    _number = nb;

    _label_ingredient = new QLabel("Ingredient ");
    _combo_ingredient = new QComboBox();

    _hbox_layout->addWidget(_label_ingredient);
    _hbox_layout->addWidget(_combo_ingredient);

    setLayout(_hbox_layout);
}

void IngredientBox::addComboList(QStringList *list)
{
    _combo_ingredient->addItems(*list);
    _combo_ingredient->setCurrentIndex(-1);
}
