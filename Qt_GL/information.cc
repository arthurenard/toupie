#include "information.h"

Information::Information()
{   nbToupies=0;
    this->resize(300, 400);
    this->move(1100, 400);
    select = new QComboBox();
    list.push_back(new QLabel("Type : "));
    list.push_back(new QLabel("Integrateur : "));
    list.push_back(new QLabel(psi + QString(" :")));
    list.push_back(new QLabel(theta + QString(" :")));
    list.push_back(new QLabel(phi + QString(" :")));
    list.push_back(new QLabel("X : "));
    list.push_back(new QLabel("Y : "));
    list.push_back(new QLabel(psi + QString("-point :")));
    list.push_back(new QLabel(theta + QString("-point :")));
    list.push_back(new QLabel(phi + QString("-point :")));
    list.push_back(new QLabel("Energie : "));
    list.push_back(new QLabel("Vect. Rotation Rg3 : "));
    list.push_back(new QLabel("Moment Cinetique A3 : "));
    list.push_back(new QLabel("Moment Cinetique AZ : "));
    list.push_back(new QLabel("Coplanaire : "));



    QVBoxLayout* box = new QVBoxLayout;
    box->addWidget(select);
    for (size_t i(0); i < 15; i++) {
        box->addWidget(list[i]);
    }
    this->setLayout(box);

}

void Information::actuNbToupie(size_t nb){
    select->clear();
    for(size_t i(0); i < nb; i++){
        select->addItem("Toupie N°"+ QString::number(i+1));
    }
    nbToupies=nb;
}

void Information::actuData(std::vector<double> data){
    int type(data[0]), integrateur(data[1]);
    switch (type) {
        case 0:
        list[0]->setText("Type : Cone Simple");
    break;
        case 1:
        list[0]->setText("Type : Toupie Chinoise");
    break;
        case 2:
        list[0]->setText("Type : Cone Général");
    break;
        case 3:
        list[0]->setText("Type : Cone Energétique");
    break;

    }
    switch (integrateur) {
        case 0:
        list[1]->setText("Integrateur : Euler-Cromer");
    break;
        case 1:
        list[1]->setText("Integrateur : Newmark");
    break;
        case 2:
        list[1]->setText("Integrateur : Runge-Kutta");
    break;

    }


    list[2]->setText(psi + QString(" :") + QString::number(data[2]));
    list[3]->setText(theta + QString(" :") + QString::number(data[3]));
    list[4]->setText(phi + QString(" :") + QString::number(data[4]));
    list[5]->setText("X : " + QString::number(data[5]));
    list[6]->setText("Y : " + QString::number(data[6]));
    list[7]->setText(psi + QString("-point :") + QString::number(data[7]));
    list[8]->setText(theta + QString("-point :") + QString::number(data[8]));
    list[9]->setText(phi + QString("-point :") + QString::number(data[9]));
    list[10]->setText("Energie : " + QString::number(data[13]));
    list[11]->setText("Vect. Rotation Rg3 : " + QString::number(data[14]));
    list[12]->setText("Moment Cinetique A3 : " + QString::number(data[15]));
    list[13]->setText("Moment Cinetique AZ : " + QString::number(data[16]));
    list[14]->setText("Coplanaire : " + QString::number(data[17]));

}

void Information::treatData(std::vector<std::vector<double>> data){
    if(data.size() != nbToupies)
    actuNbToupie(data.size());

    if(data.size() != 0)
    actuData(data[select->currentIndex()]);
}
