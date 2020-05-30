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
   void delClicked(size_t id);

public slots:
    void fullWindow();
    void newForm();
    void newInfo();
    void actualDelBtn();
    void del1();
    void del2();
    void del3();
    void del4();
    void del5();
    void del6();
    void del7();
    void del8();
    void del9();
    void del10();
    void popWarning();

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
