#include <QApplication>
#include <QPushButton>
#include <QtWidgets>
#include "mainwindow.h"
#include "glwidget.h"
#include "Erreur.h"

int main(int argc, char* argv[])
{
    try {
        QApplication a(argc, argv);

        Mainwindow window;

        window.show();
        return a.exec();
    } catch (Erreur probleme) {
        std::cerr << probleme;
    }
}
