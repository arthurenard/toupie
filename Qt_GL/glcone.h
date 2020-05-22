#ifndef GLCONE_H
#define GLCONE_H
#include <vector>
#include <cmath>

#include <QOpenGLShaderProgram>

class Glcone
{
public:
  Glcone(std::size_t nb_coins = 21);
  void draw(QOpenGLShaderProgram& prog);

private:
 std::vector<double> coordX, coordY;

};

#endif // GLCONE_H
