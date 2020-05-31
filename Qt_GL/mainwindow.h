#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include "glwidget.h"
#include "addtoupie.h"
#include "sauvegarde.h"
#include "information.h"


class Mainwindow : public QMainWindow
{
    Q_OBJECT

public:
    Mainwindow();

signals:
   void delClicked(size_t id); //est lié a GLWidget::delToupie et supprime donc une toupie quand est emis

public slots:
    void fullWindow(); //Active desactive le mode plein ecran
    void newForm(); //Affiche un nouveau formulaire addToupie
    void newInfo(); //Affiche une nouvelle fenetre Information
    void actualDelBtn(); //Actualise le nombre de bouton de suppression des toupies
    void del1(); //emet delClicked(1)
    void del2(); //emet delClicked(2)
    void del3(); //...
    void del4();
    void del5();
    void del6();
    void del7();
    void del8();
    void del9();
    void del10();
    void popWarning(); //affiche un message d'erreur quand le fichier lie a sauvegarde est mal lu

private:
    GLWidget* w;
    AddToupie* formulaire;

    QMenu* menuSupp;
    std::vector<QAction*> delBouton;

    QAction* charger;
    QAction* sauvegarder;
    Sauvegarde* saveObject;

    Information* dataScreen;
    bool windowsState;
};

#endif // MAINWINDOW_H
