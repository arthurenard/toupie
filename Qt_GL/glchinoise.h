#ifndef GLCHINOISE_H
#define GLCHINOISE_H
#include <vector>
#include "QVector2D"
#include <cmath>
#include <iostream>


#include <QOpenGLShaderProgram>

class GlChinoise
{
public:
    GlChinoise(size_t slices = 40, size_t stacks = 40);
    void draw(QOpenGLShaderProgram& prog, double hauteurNorm ,std::vector<double> rvb);

  private:
    std::vector<std::vector<double>> coordZ;
   std::vector<std::vector<double>> coordPlat;
};

#endif // GLCHINOISE_H
