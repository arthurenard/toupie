#include "configuration.h"

Configuration::Configuration()
{
    fenetre = new QGridLayout(this);


    // Construction du bouton


    nbPlanete = new QSpinBox;
    QFormLayout* first = new QFormLayout;
    first->addRow("Nombre de planete", nbPlanete);
    fenetre->addLayout(first, 0,0);
fenetre->removeItem(first);


    bouton = new QPushButton("Lancer la simulation");
    bouton->setCursor(Qt::PointingHandCursor);
    fenetre->addWidget(bouton, 0,1);
    HyperVitesse = new QSound("321HYPERVITESSE.wav");


    simulation = new GLWidget;

    QObject::connect(bouton, SIGNAL(clicked()), HyperVitesse, SLOT(play()));
    QObject::connect(bouton, SIGNAL(clicked()), simulation, SLOT(show()));
    QObject::connect(nbPlanete, SIGNAL(valueChanged(int)), this, SLOT(actualiser()));

}

Configuration::~Configuration()
{
    delete bouton;
    delete simulation;
}


void Configuration::addPlanete(size_t nb){

    planete.push_back(new QGroupBox("Planete N°" ));

    masses.push_back(new QLineEdit);
    tailles.push_back(new QLineEdit);
    coordsX.push_back(new QLineEdit);
    coordsY.push_back(new QLineEdit);
    vitsX.push_back(new QLineEdit);
    vitsY.push_back(new QLineEdit);


    QGridLayout* layout = new QGridLayout;

    QFormLayout* masse = new QFormLayout;
    QFormLayout* taille = new QFormLayout;
    QFormLayout* X = new QFormLayout;
    QFormLayout* Y = new QFormLayout;
    QFormLayout* Vx = new QFormLayout;
    QFormLayout* Vy = new QFormLayout;

    masse->addRow("Masse : ", masses[nb]);
    taille->addRow("Taille : ", tailles[nb]);
    X->addRow("X : ", coordsX[nb]);
    Y->addRow("Y : ", coordsY[nb]);
    Vx->addRow("Vx : ", vitsX[nb]);
    Vy->addRow("Vy : ", vitsY[nb]);


    layout->addLayout(masse, 0, 0);
    layout->addLayout(taille, 0, 1);
    layout->addLayout(X, 1, 0);
    layout->addLayout(Y, 1, 1);
    layout->addLayout(Vx, 2, 0);
    layout->addLayout(Vy, 2, 1);

    planete[nb]->setLayout(layout);
    fenetre->addWidget(planete[nb], nb + 1, 0);


}

void Configuration::actualiser(){
    size_t nb = nbPlanete->value();
    for(auto planet : planete){
    fenetre->removeWidget(planet);
    }
    for(auto masse : masses){
    fenetre->removeWidget(masse);
    }

    planete.clear();
    masses.clear();
    tailles.clear();
    coordsX.clear();
    coordsY.clear();
    vitsX.clear();
    vitsY.clear();



    for (size_t i(0) ; i < nb ; i++) {
        addPlanete(i);
    }
}
