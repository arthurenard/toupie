#ifndef VUEOPENGL_H
#define VUEOPENGL_H

#include <QOpenGLShaderProgram> // Classe qui regroupe les fonctions OpenGL liées aux shaders
#include <QMatrix4x4>
#include "support_a_dessin.h"
#include "glsphere.h"
#include <cmath>


class VueOpenGL : public SupportADessin {
 public:
  // méthode(s) de dessin (héritée(s) de SupportADessin)
  virtual void dessine(Contenu const& a_dessiner) override;

  // méthodes de (ré-)initialisation
  void init();
  void initializePosition();

  // méthode set
  void setProjection(QMatrix4x4 const& projection)
  { prog.setUniformValue("projection", projection); }

  // Méthodes set
  void translate(double x, double y, double z);
  void turnAround(double angle, double dir_x, double dir_y, double dir_z);
  void rotateCamera(double angle, double dir_x, double dir_y, double dir_z);
  
  // méthode utilitaire offerte pour simplifier
  void dessineCube(QMatrix4x4 const& point_de_vue = QMatrix4x4() );

  void dessinePlan(QMatrix4x4 const& point_de_vue = QMatrix4x4() );
  void dessineRepere(QMatrix4x4 const& point_de_vue = QMatrix4x4() );
  void updatePosition();
  void move(double pas);
  void dessineSphere(QMatrix4x4 const& point_de_vue,
                   double rouge = 1.0, double vert = 1.0, double bleu = 1.0);

  void dessinePlanete(double X, double Y, double masse, double rayon);




 private:
  // Un shader OpenGL encapsulé dans une classe Qt
  QOpenGLShaderProgram prog;

  // Caméra
  QMatrix4x4 matrice_vue;
  QMatrix4x4 matrice_position;
  QMatrix4x4 matrice_camera;
  double psi, omega, rho;
  GLSphere sphere;

};

#endif
