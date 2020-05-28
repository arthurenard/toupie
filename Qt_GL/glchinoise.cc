#include "glchinoise.h"
#include "vertex_shader.h"


GlChinoise::GlChinoise(size_t slices , size_t stacks )
{
    double pi(3.1416);
    double a(2*pi/slices);
    double b(2*pi/stacks);


    for(size_t i(0) ; i < slices ; i++){
        coordZ.push_back(std::vector<double>{cos(i *a ), sin(i * a)});
    }
    for(size_t j(0) ; j < stacks ; j++){
        coordPlat.push_back(std::vector<double>{cos(j*b), sin(j*b)});
    }
}

void GlChinoise::draw(QOpenGLShaderProgram &prog, double hauteurNorm, std::vector<double> rvb){
    double pi(3.1416);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    size_t Zmax;
    Zmax = floor(coordZ.size()/2 - acos(1 - hauteurNorm) * coordZ.size()/(2.*pi));

    glBegin(GL_TRIANGLES);
    for(size_t i(0) ; i < coordPlat.size() - 1 ; i++){
        prog.setAttributeValue(CouleurId, i%3, (i+1)%3, (i+2)%3);
        prog.setAttributeValue(SommetId, coordZ[1][1] * coordPlat[i][0], coordZ[1][1] * coordPlat[i][1], 1.0 - coordZ[1][0]);
        prog.setAttributeValue(SommetId, coordZ[1][1] * coordPlat[i+1][0],coordZ[1][1] * coordPlat[i+1][1], 1.0 - coordZ[1][0]);
        prog.setAttributeValue(SommetId,0.0,0.0, 0.0);
    }
        prog.setAttributeValue(CouleurId, (coordPlat.size() - 1)%3, (coordPlat.size())%3, (coordPlat.size()+1)%3);
        prog.setAttributeValue(SommetId, coordZ[1][1] * coordPlat[coordPlat.size() - 1][0],coordZ[1][1] * coordPlat[coordPlat.size() - 1][1], 1.0 - coordZ[1][0]);
        prog.setAttributeValue(SommetId, coordZ[1][1] * coordPlat[0][1],coordZ[1][0] * coordPlat[0][1], 1.0 - coordZ[1][0]);
        prog.setAttributeValue(SommetId,0.0,0.0, 0.0);
    glEnd();

    glBegin(GL_QUADS);
    for(size_t i(1); i < Zmax - 1; i++ ){
        for(size_t j(0); j < coordPlat.size()- 1; j++){
          prog.setAttributeValue(CouleurId, j%3, (j+1)%3, (j+2)%3);
          prog.setAttributeValue(SommetId, coordZ[i][1] * coordPlat[j][0],coordZ[i][1] * coordPlat[j][1], 1.0 - coordZ[i][0]);
          prog.setAttributeValue(SommetId, coordZ[i][1] * coordPlat[j+1][0],coordZ[i][1] * coordPlat[j+1][1], 1.0 - coordZ[i][0]);
          prog.setAttributeValue(SommetId, coordZ[i+1][1] * coordPlat[j+1][0],coordZ[i+1][1] * coordPlat[j+1][1], 1.0 - coordZ[i+1][0]);
          prog.setAttributeValue(SommetId, coordZ[i+1][1] * coordPlat[j][0],coordZ[i+1][1] * coordPlat[j][1], 1.0 - coordZ[i+1][0]);
        }
        prog.setAttributeValue(CouleurId, (coordPlat.size()- 1)%3, (coordPlat.size())%3, (coordPlat.size() +1)%3);
        prog.setAttributeValue(SommetId, coordZ[i][1] * coordPlat[coordPlat.size()- 1][0],coordZ[i][1] * coordPlat[coordPlat.size()- 1][1], 1.0 - coordZ[i][0]);
        prog.setAttributeValue(SommetId, coordZ[i][1] * coordPlat[0][0],coordZ[i][1] * coordPlat[0][1], 1.0 - coordZ[i][0]);
        prog.setAttributeValue(SommetId, coordZ[i+1][1] * coordPlat[0][0],coordZ[i+1][1] * coordPlat[0][1], 1.0 - coordZ[i+1][0]);
        prog.setAttributeValue(SommetId, coordZ[i+1][1] * coordPlat[coordPlat.size()- 1][0],coordZ[i+1][1] * coordPlat[coordPlat.size()- 1][1], 1.0 - coordZ[i+1][0]);
    }
    glEnd();
    glBegin(GL_POLYGON);
    prog.setAttributeValue(CouleurId, rvb[0], rvb[1], rvb[2]);
    for(size_t i(0); i<coordPlat.size(); i++){
    prog.setAttributeValue(SommetId, coordZ[Zmax-1][1] * coordPlat[i][0], coordZ[Zmax-1][1] * coordPlat[i][1], 1.0 - coordZ[Zmax-1][0]);
    }
    glEnd();
    glBegin(GL_POLYGON);
    prog.setAttributeValue(CouleurId, rvb[0], rvb[1], rvb[2]);
    for(size_t i(0); i<coordPlat.size(); i++){
    prog.setAttributeValue(SommetId,0.15 * coordPlat[i][0],0.15 * coordPlat[i][1], 1.7);
    }
    glEnd();

    glBegin(GL_QUADS);
    for(size_t i(0); i<coordPlat.size()-1; i++ ){
        prog.setAttributeValue(CouleurId, i%3, (i+1)%3, (i+2)%3);
        prog.setAttributeValue(SommetId,0.15 * coordPlat[i][0],0.15 * coordPlat[i][1], 1.0 - coordZ[Zmax-1][0]);
        prog.setAttributeValue(SommetId,0.15 * coordPlat[i+1][0],0.15 * coordPlat[i+1][1], 1.0 - coordZ[Zmax-1][0]);
        prog.setAttributeValue(SommetId,0.15 * coordPlat[i+1][0],0.15 * coordPlat[i+1][1], 1.7);
        prog.setAttributeValue(SommetId,0.15 * coordPlat[i][0],0.15 * coordPlat[i][1], 1.7);
    }
    prog.setAttributeValue(CouleurId, (coordPlat.size()-1)%3, (coordPlat.size())%3, (coordPlat.size()+1)%3);
    prog.setAttributeValue(SommetId,0.15 * coordPlat[coordPlat.size()-1][0],0.15 * coordPlat[coordPlat.size()-1][1],1.0 - coordZ[Zmax-1][0]);
    prog.setAttributeValue(SommetId,0.15 *  coordPlat[0][0],0.15 * coordPlat[0][1], 1.0 - coordZ[Zmax-1][0]);
    prog.setAttributeValue(SommetId,0.15 * coordPlat[0][0],0.15 * coordPlat[0][1], 1.7);
    prog.setAttributeValue(SommetId,0.15 * coordPlat[coordPlat.size()-1][0],0.15 * coordPlat[coordPlat.size()-1][1], 1.7);
    glEnd();

}

