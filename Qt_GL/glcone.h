#ifndef GLCONE_H
#define GLCONE_H
#include <vector>
#include <cmath>
#include <QOpenGLShaderProgram>

class Glcone
{
public:
  Glcone(std::size_t nb_coins = 60); //calcule toutes les coordonnees d'un cone
  void draw(QOpenGLShaderProgram& prog, std::vector<double> rvb); //dessine le cone

private:
 std::vector<double> coordX, coordY;

};

#endif // GLCONE_H
