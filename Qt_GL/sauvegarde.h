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
    void dataLoaded(std::vector<double>);
    void errorFile();


public slots:
    void sauvegarder(std::vector<std::vector<double>> data);
    void charger();



private:
    std::string fileName;
    bool loadFile();
    std::string dataToString(std::vector<std::vector<double>> data);
    size_t hashData(std::string data);


};

#endif // SAUVEGARDE_H
