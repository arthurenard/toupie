#include "glcone.h"
#include "vertex_shader.h"


Glcone::Glcone(std::size_t nb_coins){
    double pi(3.1416);
    double a(2*pi/nb_coins);
    for(std::size_t i(0); i < nb_coins ; i++){
        coordX.push_back(cos(i * a));
        coordY.push_back(sin(i * a));
    }
}

void Glcone::draw(QOpenGLShaderProgram& prog, std::vector<double> rvb){
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBegin(GL_POLYGON);
    prog.setAttributeValue(CouleurId, rvb[0], rvb[1], rvb[2]);
    for(size_t i(0); i<coordX.size(); i++){
    prog.setAttributeValue(SommetId, coordX[i],coordY[i], 1.0);
    }
    glEnd();
    glBegin(GL_TRIANGLES);
    for(size_t i(0); i<coordX.size()-1; i++ ){
        prog.setAttributeValue(CouleurId, i%3, (i+1)%3, (i+2)%3);
        prog.setAttributeValue(SommetId, coordX[i],coordY[i], 1.0);
        prog.setAttributeValue(SommetId, coordX[i+1],coordY[i+1], 1.0);
        prog.setAttributeValue(SommetId,0.0,0.0, 0.0);
    }
    prog.setAttributeValue(CouleurId, (coordX.size()-1)%3, (coordX.size())%3, (coordX.size()+1)%3);
    prog.setAttributeValue(SommetId, coordX[coordX.size()-1],coordY[coordX.size()-1], 1.0);
    prog.setAttributeValue(SommetId, coordX[0],coordY[0], 1.0);
    prog.setAttributeValue(SommetId,0.0,0.0, 0.0);
    glEnd();

    glBegin(GL_QUADS);
    for(size_t i(0); i<coordX.size()-1; i++ ){
        prog.setAttributeValue(CouleurId, i%3, (i+1)%3, (i+2)%3);
        prog.setAttributeValue(SommetId,0.15 * coordX[i],0.15 * coordY[i], 1.0);
        prog.setAttributeValue(SommetId,0.15 * coordX[i+1],0.15 * coordY[i+1], 1.0);
        prog.setAttributeValue(SommetId,0.15 * coordX[i+1],0.15 * coordY[i+1], 1.5);
        prog.setAttributeValue(SommetId,0.15 * coordX[i],0.15 * coordY[i], 1.5);
    }
    prog.setAttributeValue(CouleurId, (coordX.size()-1)%3, (coordX.size())%3, (coordX.size()+1)%3);
    prog.setAttributeValue(SommetId,0.15 * coordX[coordX.size()-1],0.15 * coordY[coordX.size()-1], 1.0);
    prog.setAttributeValue(SommetId,0.15 *  coordX[0],0.15 * coordY[0], 1.0);
    prog.setAttributeValue(SommetId,0.15 * coordX[0],0.15 * coordY[0], 1.5);
    prog.setAttributeValue(SommetId,0.15 * coordX[coordX.size()-1],0.15 * coordY[coordX.size()-1], 1.5);
    glEnd();

    glBegin(GL_POLYGON);
    prog.setAttributeValue(CouleurId,  rvb[0], rvb[1], rvb[2]);
    for(size_t i(0); i<coordX.size(); i++){
    prog.setAttributeValue(SommetId,0.15 * coordX[i],0.15 * coordY[i], 1.5);
    }
    glEnd();
}
