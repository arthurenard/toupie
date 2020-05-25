#ifndef SAUVEGARDE_H
#define SAUVEGARDE_H
#include <QString>
#include <QtWidgets>
#include <QFileDialog>
#include <fstream>



class Sauvegarde : public QWidget
{
    Q_OBJECT

public:    

    Sauvegarde();

signals:
    void dataLoaded(std::vector<double>);


public slots:
    void sauvegarder(std::vector<std::vector<double>> data);
    void charger();



private:
    std::string fileName;
    bool loadFile();

};

#endif // SAUVEGARDE_H
