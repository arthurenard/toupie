#include "mainwindow.h"

Mainwindow::Mainwindow()
{
    resize(1080, 1080);
    this->move(0,0);
    windowsState = false;

    w = new GLWidget;
    w->setFocusPolicy(Qt::StrongFocus);
    setCentralWidget(w);


    QObject::connect(w, SIGNAL(fullWindow()), this, SLOT(fullWindow()));
    QObject::connect(w, SIGNAL(closeAll()), this, SLOT(close()));

    QObject::connect(this, SIGNAL(delClicked(size_t)), w, SLOT(delToupie(size_t)));
    QObject::connect(this, SIGNAL(delClicked(size_t)), this, SLOT(actualDelBtn()));



       QMenu* menuAdd = menuBar()->addMenu("&Ajouter une Toupie");
       QAction* addTopAction = new QAction("&Ajouter une Toupie");
       menuAdd -> addAction(addTopAction);
       QObject::connect(addTopAction, SIGNAL(triggered()), this, SLOT(newForm()));

       menuSupp = menuBar()->addMenu("&Supprimer une Toupie");
       for (size_t i(0); i < 10 ;i++) {
           delBouton.push_back(new QAction("Supprimer Toupie N°" + QString::number(i+1)));
       }
       delBouton.push_back(new QAction("Tout Supprimer"));
       QObject::connect(delBouton[0], SIGNAL(triggered()), this, SLOT(del1()));
       QObject::connect(delBouton[1], SIGNAL(triggered()), this, SLOT(del2()));
       QObject::connect(delBouton[2], SIGNAL(triggered()), this, SLOT(del3()));
       QObject::connect(delBouton[3], SIGNAL(triggered()), this, SLOT(del4()));
       QObject::connect(delBouton[4], SIGNAL(triggered()), this, SLOT(del5()));
       QObject::connect(delBouton[5], SIGNAL(triggered()), this, SLOT(del6()));
       QObject::connect(delBouton[6], SIGNAL(triggered()), this, SLOT(del7()));
       QObject::connect(delBouton[7], SIGNAL(triggered()), this, SLOT(del8()));
       QObject::connect(delBouton[8], SIGNAL(triggered()), this, SLOT(del9()));
       QObject::connect(delBouton[9], SIGNAL(triggered()), this, SLOT(del10()));
       QObject::connect(delBouton[10], SIGNAL(triggered()), w, SLOT(delAll()));



       saveObject = new Sauvegarde;
       QMenu *menuSave = menuBar()->addMenu("Sauvegarde");
       charger = new QAction("Charger un systeme");
       sauvegarder = new QAction("&Sauvegarder le systeme");
       menuSave->addAction(charger);
       menuSave->addAction(sauvegarder);


       QObject::connect(charger, SIGNAL(triggered()), saveObject, SLOT(charger()));
       QObject::connect(saveObject, SIGNAL(dataLoaded(std::vector<double>)), w, SLOT(addToupie(std::vector<double>)));
       QObject::connect(saveObject, SIGNAL(dataLoaded(std::vector<double>)), this, SLOT(actualDelBtn()));


       QObject::connect(sauvegarder, SIGNAL(triggered()), w, SLOT(sauvegarder()));
       QObject::connect(w, SIGNAL(allDataSend(std::vector<std::vector<double>>)), saveObject, SLOT(sauvegarder(std::vector<std::vector<double>>)));

       QObject::connect(saveObject, SIGNAL(errorFile()), this, SLOT(popWarning()));

       newForm();


       QMenu* info = menuBar()->addMenu("Informations");
       QAction* openInfo = new QAction("Fenetre d'information");
       info -> addAction(openInfo);
       QObject::connect(openInfo, SIGNAL(triggered()), this, SLOT(newInfo()));
}

void Mainwindow::newForm(){
    formulaire = new AddToupie(w->nb_toupie());
    formulaire->show();
    QObject::connect(formulaire, SIGNAL(dataSend(std::vector<double>)), w, SLOT(addToupie(std::vector<double>)));
    QObject::connect(formulaire, SIGNAL(dataSend(std::vector<double>)), this, SLOT(actualDelBtn()));
    QObject::connect(w, SIGNAL(closeAll()), formulaire, SLOT(close()));
    QObject::connect(saveObject, SIGNAL(errorFile()), formulaire, SLOT(close()));
}
void Mainwindow::newInfo(){

    dataScreen = new Information;
    dataScreen->show();
    QObject::connect(w, SIGNAL(sendEverySecond(std::vector<std::vector<double>>)), dataScreen, SLOT(treatData(std::vector<std::vector<double>>)));
    QObject::connect(w, SIGNAL(closeAll()), dataScreen, SLOT(close()));
    QObject::connect(saveObject, SIGNAL(errorFile()), dataScreen, SLOT(close()));
}

void Mainwindow::actualDelBtn(){
   size_t nb(w->nb_toupie());
   for (size_t i(0); i < 11 ;i++) {
    menuSupp->removeAction(delBouton[i]);
   }
   for (size_t i(0); i < nb ;i++) {
    menuSupp->addAction(delBouton[i]);
   }
   if(nb>1)
   menuSupp->addAction(delBouton[10]);

}



void Mainwindow::del1(){
    emit delClicked(1);
}
void Mainwindow::del2(){
    emit delClicked(2);
}
void Mainwindow::del3(){
    emit delClicked(3);
}
void Mainwindow::del4(){
    emit delClicked(4);
}
void Mainwindow::del5(){
    emit delClicked(5);
}
void Mainwindow::del6(){
    emit delClicked(6);
}
void Mainwindow::del7(){
    emit delClicked(7);
}
void Mainwindow::del8(){
    emit delClicked(8);
}
void Mainwindow::del9(){
    emit delClicked(9);
}
void Mainwindow::del10(){
    emit delClicked(10);
}
void Mainwindow::fullWindow(){
    if(!windowsState)
    {showFullScreen();}
    else
    {showNormal();}
    windowsState = !windowsState;
}

void Mainwindow::popWarning(){
    QMessageBox::critical(this, "Erreur", "Fichier corrompu ou illisible, le programme va s'éteindre");
    this->close();
}
