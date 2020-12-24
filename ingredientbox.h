#ifndef INGREDIENTBOX_H
#define INGREDIENTBOX_H

#include <QWidget>
#include <QLabel>
#include <QComboBox>
#include <QString>
#include <QStringList>
#include <QHBoxLayout>

class IngredientBox : public QWidget
{
    Q_OBJECT
private:
    QString _name;
    int _number = 0;


public:
    explicit IngredientBox(int nb, QWidget *parent = nullptr);

    void addComboList(QStringList *list);

    QLabel *_label_ingredient;
    QComboBox *_combo_ingredient;

    QHBoxLayout *_hbox_layout;
signals:

};

#endif // INGREDIENTBOX_H
