#include "information.h"

Information::Information()
{   nbToupies=0;
    this->resize(300, 300);
    this->move(1100, 400);
    select = new QComboBox();
    list.push_back(new QLabel(psi + QString(" :")));
    list.push_back(new QLabel(theta + QString(" :")));
    list.push_back(new QLabel(phi + QString(" :")));
    list.push_back(new QLabel("X : "));
    list.push_back(new QLabel("Y : "));
    list.push_back(new QLabel(psi + QString("-point :")));
    list.push_back(new QLabel(theta + QString("-point :")));
    list.push_back(new QLabel(phi + QString("-point :")));

    QVBoxLayout* box = new QVBoxLayout;
    box->addWidget(select);
    for (size_t i(0); i < 8; i++) {
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
    list[0]->setText(psi + QString(" :") + QString::number(data[2]));
    list[1]->setText(theta + QString(" :") + QString::number(data[3]));
    list[2]->setText(phi + QString(" :") + QString::number(data[4]));
    list[3]->setText("X : " + QString::number(data[5]));
    list[4]->setText("Y : " + QString::number(data[6]));
    list[5]->setText(psi + QString("-point :") + QString::number(data[7]));
    list[6]->setText(theta + QString("-point :") + QString::number(data[8]));
    list[7]->setText(phi + QString("-point :") + QString::number(data[9]));
}

void Information::treatData(std::vector<std::vector<double>> data){
    if(data.size() != nbToupies)
    actuNbToupie(data.size());

    if(data.size() != 0)
    actuData(data[select->currentIndex()]);
}
