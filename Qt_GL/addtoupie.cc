#include "addtoupie.h"



AddToupie::AddToupie(size_t nb):id(nb)
{
    QString theta = QChar(0xb8, 0x03);
    QString psi = QChar(0xc8, 0x03);
    QString phi = QChar(0xc6, 0x03);


    QGridLayout *layout = new QGridLayout;
    QLabel* titre = new QLabel(QString("Toupie N°") + QString::number(id+1));
    titre->setFont(QFont("Courrier", 20, QFont::Bold, true));
    QFormLayout* form = new QFormLayout;
    type = new QComboBox(this);
    type->addItem("Cone Simple");
    type->addItem("Toupie Chinoise");
    type->addItem("Cone Général");
    type->addItem("Cone Energétique");
    QObject::connect(type, SIGNAL(currentIndexChanged(int)), this, SLOT(adaptInit()));

    integrateur = new QComboBox(this);
    integrateur->addItem("Euler-Cromer");
    integrateur->addItem("Newmark");
    integrateur->addItem("Runge-Kutta");


    QGroupBox *groupbox = new QGroupBox("Données :");

    QGridLayout *initcondi = new QGridLayout;

    for (size_t i(0); i<5; i++) {
        coord.push_back(new QDoubleSpinBox);
        coord[i]->setDecimals(2);
        coord[i]->setRange(0.0, 2*3.14);
        coord[i]->setSingleStep(0.1);
        coord[i]->setFixedWidth(100);
        initcondi->addWidget(coord[i], 0, 1+i*2);
    }
    coord[3]->setRange(-10,10);
    coord[3]->setSingleStep(1.0);
    coord[4]->setRange(-10,10);
    coord[4]->setSingleStep(1.0);
    coord[0]->setValue(0.);
    coord[1]->setValue(0.2);
    coord[2]->setValue(0.);
    coord[3]->setValue(0.);
    coord[4]->setValue(0.);


    for (size_t i(0); i<3; i++) {
        vit.push_back(new QDoubleSpinBox);
        vit[i]->setDecimals(2);
        vit[i]->setRange(0.0,500.0);
        vit[i]->setSingleStep(0.1);
        vit[i]->setFixedWidth(100);
        initcondi->addWidget(vit[i], 1,  1+i*2);
    }
    vit[0]->setValue(0.);
    vit[1]->setValue(0.);
    vit[2]->setValue(40.);


    for (size_t i(0); i<3; i++) {
        caract.push_back(new QDoubleSpinBox);
        caract[i]->setDecimals(3);
        caract[i]->setSingleStep(0.1);
        caract[i]->setFixedWidth(100);
        initcondi->addWidget(caract[i], 2,  1+i*2);
    }
    caract[0]->setValue(1.0);
    caract[1]->setValue(1.1);
    caract[2]->setValue(1.0);



    initcondi->addWidget(new QLabel(psi + QString(" :")), 0,0);
    initcondi->addWidget(new QLabel(theta + QString(" :")), 0,2);
    initcondi->addWidget(new QLabel(phi + QString(" :")), 0,4);
    initcondi->addWidget(new QLabel("X :"), 0,6);
    initcondi->addWidget(new QLabel("Y :"), 0,8);

    initcondi->addWidget(new QLabel(QString("d") + psi + QString("/dt :")), 1,0);
    initcondi->addWidget(new QLabel(QString("d") + theta + QString("/dt :")), 1,2);
    initcondi->addWidget(new QLabel(QString("d") + phi + QString("/dt :")), 1,4);


    initcondi->addWidget(new QLabel("MasseVol. :"), 2,0);
    initcondi->addWidget(new QLabel("Hauteur :"), 2,2);
    initcondi->addWidget(new QLabel("Rayon :"), 2,4);

    groupbox->setLayout(initcondi);
    form->addRow("Type de Toupie :", type);
    form->addRow("Integrateur :", integrateur);

    QLabel *image =new QLabel;
    image->setPixmap(QPixmap("toupie.png"));
    layout->addWidget(titre,0,0);
    layout->addLayout(form,1,0);
    layout->addWidget(image, 0,2, 2,1);
    layout->addWidget(groupbox,2,0, 1, 3);

    QPushButton* valid = new QPushButton("VALIDER");
    layout->addWidget(valid, 3,2);
    QObject::connect(valid, SIGNAL(clicked()), this, SLOT(getData()));
    this->setLayout(layout);
    this->move(1080,0);
}

AddToupie::~AddToupie(){
    delete type;
    delete integrateur;
    for(auto i: coord){
        delete i;
    }
    for(auto i: vit){
        delete i;
    }
    for(auto i: caract){
        delete i;
    }
}


void AddToupie::getData(){
    std::vector<double>data;
    data.push_back(type->currentIndex());
    data.push_back(integrateur->currentIndex());
    for (size_t i(0); i<5; i++) {
        data.push_back(coord[i]->value());
    }
    for (size_t i(0); i<3 ; i++) {
        data.push_back(vit[i]->value());
    }
    for (size_t i(0); i<3; i++) {
        data.push_back(caract[i]->value());
    }

    emit dataSend(data);
    this->close();
    delete this;
}
void AddToupie::adaptInit(){
    switch (type->currentIndex()) {
    case 1:
        coord[0]->setValue(0.);
        coord[1]->setValue(0.2);
        coord[2]->setValue(0.);
        coord[3]->setValue(0.);
        coord[4]->setValue(0.);
        vit[0]->setValue(3.);
        vit[1]->setValue(0.3);
        vit[2]->setValue(4.);
        caract[0]->setValue(1.0);
        caract[1]->setValue(0.5);
        caract[2]->setValue(1.0);
        integrateur->clear();
        integrateur->addItem("Euler-Cromer (Ne marche pas)");
        integrateur->addItem("Newmark");
        integrateur->addItem("Runge-Kutta");
        integrateur->setCurrentIndex(1);
        break;
    default:
        coord[0]->setValue(0.);
        coord[1]->setValue(0.2);
        coord[2]->setValue(0.);
        coord[3]->setValue(0.);
        coord[4]->setValue(0.);
        vit[0]->setValue(0.);
        vit[1]->setValue(0.);
        vit[2]->setValue(40.);
        caract[0]->setValue(1.0);
        caract[1]->setValue(1.1);
        caract[2]->setValue(1.0);
        integrateur->clear();
        integrateur->addItem("Euler-Cromer");
        integrateur->addItem("Newmark");
        integrateur->addItem("Runge-Kutta");
        break;

    }



}
