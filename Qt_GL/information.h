#ifndef INFORMATION_H
#define INFORMATION_H
#include <QtWidgets>
#include <QComboBox>
#include <QVBoxLayout>



class Information : public QWidget
{
    Q_OBJECT

public:
    Information();

public slots:
    void treatData(std::vector<std::vector<double>> data); //Recoit les données et adapte la liste de QLabel en appelant actuData

private:
    QComboBox* select;
    std::vector<QLabel*> list;

    QString theta = QChar(0xb8, 0x03);
    QString psi = QChar(0xc8, 0x03);
    QString phi = QChar(0xc6, 0x03);

    void actuNbToupie(size_t nb); //Actualise la liste deroulante select en fonction du nombre de toupie
    void actuData(std::vector<double> data); //Actualise les QLabel
    size_t nbToupies;
};

#endif // INFORMATION_H
