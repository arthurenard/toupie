#ifndef VUEOPENGL_H
#define VUEOPENGL_H

#include <QGLContext>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QMatrix4x4>
#include "support_a_dessin.h"
#include "glsphere.h"
#include "glcone.h"
#include "glchinoise.h"
#include "bases/Vecteur.h"
#include <cmath>
#include "support_a_dessin.h"
#include "Systeme.h"

//Cette classe est construite a partir de l'exemple 5 de QT

class VueOpenGL : public SupportADessin, protected QOpenGLFunctions {
 public:
    ~VueOpenGL();

  // méthode(s) de dessin (héritée(s) de SupportADessin)
  virtual void dessine(Systeme const& systeme) override;

  // méthodes de (ré-)initialisation
  void init(); //initialise le graphisme, charge les textures
  void initializePosition(); //permet de reinitialiser la position
  void loadWhiteTexture(); //charge une texture blanche pour corriger les couleurs (voir journal pour le pourquoi)

  void setProjection(QMatrix4x4 const& projection)
  { prog.setUniformValue("projection", projection); }

  void dessineToupie(Toupie* toupie); //methode de dessin des toupies, elle les positionne dans l'espace et dessine un cone ou une toupiechinoise
  void dessineTrace(Toupie* toupie, size_t nb); // permet de dessiner la trace d'une toupie d'index nb
  void dessineBalle(Balle* balle); // dessine la balle transmise en argument

  void dessineSphere(QMatrix4x4 const& point_de_vue, double rouge = 1.0, double vert = 1.0, double bleu = 1.0); //dessine une sphere
  void dessineCone(QMatrix4x4 const& point_de_vue = QMatrix4x4(), double paraColor= 1.); // dessine un cone
  void dessineChinoise(QMatrix4x4 const& point_de_vue = QMatrix4x4(), double hauteurNorm = 0.,double paraColor= 1.); //dessine la toupie chinoise


  // Méthodes liés au positionnement et a la camera
  void updatePosition();//recalcule la matrice_vue
  void move(double pas);//permet de modifier rho, zoomer dezoomer
  void translate(double x, double y, double z); // translate l'espace
  void turnAround(double angle, double dir_x, double dir_y, double dir_z);//permet de tourner autour de l'origine
  void rotateCamera(double angle, double dir_x, double dir_y, double dir_z);//permet de tourner la camera sur elle meme
  double getRho(){return rho;}
  double getOmega(){return omega*pi/180.;}
  double getPsi(){return psi*pi/180.;}


  //Methodes de dessins de l'environnement, elles recoivent un point de vue qui permet de positionner l'objet
  void dessinePlan(QMatrix4x4 const& point_de_vue = QMatrix4x4() ); //dessine le sol
  void dessineRepere(QMatrix4x4 const& point_de_vue = QMatrix4x4() ); //dessine les axes X Y Z
  void dessineBarriere(QMatrix4x4 const& point_de_vue = QMatrix4x4() ); //dessine une barriere EPFL
  void dessineContour(QMatrix4x4  point_de_vue = QMatrix4x4()); //dessine 4 barrieres EPFL
  void drawNousWTF(QMatrix4x4 const& point_de_vue = QMatrix4x4()); //SURPRISE
  void drawBY(QMatrix4x4 const& point_de_vue = QMatrix4x4()); //dessine nos magnifiques codeurs
  void drawJCC(double x, double y, double z); //SURPRISE

  std::vector<double> gradColor(double x); //retroingeniering du mouvement sur X dans la palette de couleur de Paint.exe, sort une couleur en fonction d'un double


 private:
  QOpenGLShaderProgram prog;

  // Attributs liés à la camera
  QMatrix4x4 matrice_vue;
  QMatrix4x4 matrice_position; //Matrice de "translation" elle permet d'adopter un mouvement spherique
  QMatrix4x4 matrice_camera; //Matrice qui permet de pivoter la camera sur elle meme
  double psi, omega, rho; //correspond aux coordonees spherique liées a la position de la camera

  //Objets de dessin de formes geometriques
  GLSphere sphere;
  Glcone cone;
  GlChinoise chinoise;

  //Textures
  GLuint textureDeChat;
  GLuint textureBlanche;
  GLuint texturenous;
  GLuint epfl;
};

#endif
