#ifndef SAUVEGARDE_H
#define SAUVEGARDE_H
#include <QString>
#include <QtWidgets>
#include <QFileDialog>
#include <fstream>
#include <string>
#include <iomanip>
#include <unordered_map>


class Sauvegarde : public QWidget
{
    Q_OBJECT

public:    

    Sauvegarde();

signals:
    void dataLoaded(std::vector<double>); //Est emis des qu'une nouvelle toupie est chargée
    void errorFile(); //Est émis si il y a une erreur de chargement de fichier


public slots:
    void sauvegarder(std::vector<std::vector<double>> data); //Est appelé lorsque l'utilisateur veut sauvegarder, sauvegarder recoit toutes les données des toupies
    void charger(); //Est appelé lorsque l'utilisateur demande de charger un  fichier



private:
    std::string fileName;
    bool loadFile(int type); //Permet a l'utilisateur de selectionner un fichier, le int correspond au mode sauvegarde(0) charge(1)
    std::string dataToString(std::vector<std::vector<double>> data); //Convertit les data du systeme en une string a ecrire dans le fichier .txt
    size_t hashData(std::string data); //retourne le hash associe a une string


};

#endif // SAUVEGARDE_H
