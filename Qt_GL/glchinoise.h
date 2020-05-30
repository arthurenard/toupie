#ifndef GLCHINOISE_H
#define GLCHINOISE_H
#include <vector>
#include <cmath>
#include <QOpenGLShaderProgram>

class GlChinoise
{
public:
    GlChinoise(size_t slices = 20, size_t stacks = 20); //calcule toutes les coordonnees
    void draw(QOpenGLShaderProgram& prog, double hauteurNorm ,std::vector<double> rvb); //dessine la figure geometrique

  private:
    std::vector<std::vector<double>> coordZ;
   std::vector<std::vector<double>> coordPlat;
};

#endif // GLCHINOISE_H
