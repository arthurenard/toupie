#ifndef ADDTOUPIE_H
#define ADDTOUPIE_H
#include <QWidget>
#include <QComboBox>
#include <QGridLayout>
#include <vector>
#include <QObject>
#include <QDoubleSpinBox>
#include <QLabel>
#include <QGroupBox>
#include <QFormLayout>
#include <QPushButton>

class AddToupie:public QWidget
{
    Q_OBJECT

public:
    AddToupie(size_t nb=0);

signals:
    void dataSend(std::vector<double>data);
public slots:
    void getData();

private:
    //QWidget *onglet;
    QComboBox *type;
    QComboBox *integrateur;
    size_t id;

    std::vector<QDoubleSpinBox *>coord;
    std::vector<QDoubleSpinBox *>vit;
    std::vector<QDoubleSpinBox *>caract;


};

#endif // ADDTOUPIE_H
