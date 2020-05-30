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
    AddToupie(size_t nb=0); //Constructeur du formulaire AddToupie, nb = index +1 de la nouvelle toupie
    ~AddToupie();

signals:
    void dataSend(std::vector<double>data); // Signal émis lorsque le getData() s'est execute, il transmet un vector<double> qui contient tout
public slots:
    void getData(); //est appele lorsque le formulaire est valide, getData recupere toutes les valeurs inscrites et emet dataSend
    void adaptInit(); //est appele lorsque la valeur de type est change, adaptIit adapte le formulaire ne fonction de la toupie choisie

private:
    size_t id;

    QComboBox *type;                        //Ces attributs correspondent aux QObject dans lesquelles l'utilisateurs entre des données
    QComboBox *integrateur;
    std::vector<QDoubleSpinBox *>coord;
    std::vector<QDoubleSpinBox *>vit;
    std::vector<QDoubleSpinBox *>caract;


};

#endif // ADDTOUPIE_H
