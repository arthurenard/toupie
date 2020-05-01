#include "vue_opengl.h"
#include "vertex_shader.h" // Identifiants Qt de nos différents attributs

// ======================================================================
void VueOpenGL::dessine(Systeme const& systeme)
{
   // Dessine le 1er cube (à l'origine)
  //dessineCube();
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  dessinePlan();
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  dessineRepere();
  QMatrix4x4 matricecone;
  matricecone.translate(systeme.getCone()->get_vect_P()[3],systeme.getCone()->get_vect_P()[4]);
  matricecone.rotate(systeme.getCone()->get_vect_P()[0] *180/pi, 0.0,0.0,1.0);
  matricecone.rotate(systeme.getCone()->get_vect_P()[1] *180/pi, 1.0,0.0,0.0);
  matricecone.rotate(systeme.getCone()->get_vect_P()[2] *180/pi, 0.0,0.0,1.0);
  matricecone.scale(systeme.getCone()->getRayon(),systeme.getCone()->getRayon(), systeme.getCone()->getHauteur());
  dessineCone(matricecone);

  QMatrix4x4 matricecone2;
  matricecone2.translate(systeme.getCone2()->get_vect_P()[3],systeme.getCone2()->get_vect_P()[4]);
  matricecone2.rotate(systeme.getCone2()->get_vect_P()[0] *180/pi, 0.0,0.0,1.0);
  matricecone2.rotate(systeme.getCone2()->get_vect_P()[1] *180/pi, 1.0,0.0,0.0);
  matricecone2.rotate(systeme.getCone2()->get_vect_P()[2] *180/pi, 0.0,0.0,1.0);
  matricecone2.scale(systeme.getCone2()->getRayon(),systeme.getCone2()->getRayon(), systeme.getCone2()->getHauteur());
  dessineCone(matricecone2);
  matricecone2.setToIdentity();
 // matricecone2.translate(systeme.getChinois()->get_vect_P()[3],systeme.getChinois()->get_vect_P()[4]);
  matricecone2.rotate(systeme.getChinois()->get_vect_P()[0] *180/pi, 0.0,0.0,1.0);
  matricecone2.rotate(systeme.getChinois()->get_vect_P()[1] *180/pi, 1.0,0.0,0.0);
  matricecone2.rotate(systeme.getChinois()->get_vect_P()[2] *180/pi, 0.0,0.0,1.0);
  //matricecone2.scale(systeme.getChinois()->getRayon(),systeme.getChinois()->getRayon(), systeme.getCone2()->getHauteur());
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  dessineSphere(matricecone2);

 /* for(size_t i(0); i < systeme.nbToupies(); i++){
      dessineToupie(systeme.getToupie(i));
  }*/

}

// ======================================================================
void VueOpenGL::init()
{
  /* Initialise notre vue OpenGL.
   * Dans cet exemple, nous créons et activons notre shader.
   *
   * En raison du contenu des fichiers *.glsl, le shader de cet exemple
   * NE permet QUE de dessiner des primitives colorées
   * (pas de textures, brouillard, reflets de la lumière ou autres).
   *
   * Il est séparé en deux parties VERTEX et FRAGMENT.
   * Le VERTEX :
   * - récupère pour chaque sommet des primitives de couleur (dans
   *     l'attribut couleur) et de position (dans l'attribut sommet)
   * - multiplie l'attribut sommet par les matrices 'vue_modele' et
   *     'projection' et donne le résultat à OpenGL
   *   - passe la couleur au shader FRAGMENT.
   *
   * Le FRAGMENT :
   *   - applique la couleur qu'on lui donne
   */

  prog.addShaderFromSourceFile(QOpenGLShader::Vertex,   ":/vertex_shader.glsl");
  prog.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fragment_shader.glsl");

  /* Identifie les deux attributs du shader de cet exemple
   * (voir vertex_shader.glsl).
   *
   * L'attribut identifié par 0 est particulier, il permet d'envoyer un
   * nouveau "point" à OpenGL
   *
   * C'est pourquoi il devra obligatoirement être spécifié et en dernier
   * (après la couleur dans cet exemple, voir plus bas).
   */

  prog.bindAttributeLocation("sommet",  SommetId);
  prog.bindAttributeLocation("couleur", CouleurId);

  // Compilation du shader OpenGL
  prog.link();

  // Activation du shader
  prog.bind();

  /* Activation du "Test de profondeur" et du "Back-face culling"
   * Le Test de profondeur permet de dessiner un objet à l'arrière-plan
   * partielement caché par d'autres objets.
   *
   * Le Back-face culling consiste à ne dessiner que les face avec ordre
   * de déclaration dans le sens trigonométrique.
   */
  glEnable(GL_DEPTH_TEST);
  //glEnable(GL_CULL_FACE);

  sphere.initialize();                                      // initialise la sphère

  initializePosition();
}

// ======================================================================
void VueOpenGL::initializePosition()
{
  // position initiale
    rho = -2.0;
    psi= -65;
    omega = 20;
  matrice_position.setToIdentity();
  matrice_position.translate(0.0, 0.0, rho);
  matrice_position.rotate(psi, 1.0, 0.0, 0.0);
  matrice_position.rotate(omega, 0.0, 0.0, 1.0);
  matrice_camera.setToIdentity();
  matrice_vue = matrice_camera * matrice_position;
}

// ======================================================================
void VueOpenGL::translate(double x, double y, double z)
{
  /* Multiplie la matrice de vue par LA GAUCHE.
   * Cela fait en sorte que la dernière modification apportée
   * à la matrice soit appliquée en dernier (composition de fonctions).
   */
  QMatrix4x4 translation_supplementaire;
  translation_supplementaire.translate(x, y, z);
  matrice_position = translation_supplementaire * matrice_position;
  matrice_vue = matrice_camera * matrice_position;
}

void VueOpenGL::move(double pas){
    rho += pas;
    updatePosition();
}

// ======================================================================
void VueOpenGL::rotateCamera(double angle, double dir_x, double dir_y, double dir_z)
{
  // Multiplie la matrice de vue par LA GAUCHE
  QMatrix4x4 rotation_supplementaire;
  rotation_supplementaire.rotate(angle, dir_x, dir_y, dir_z);
  matrice_camera = rotation_supplementaire * matrice_camera;
  matrice_vue = matrice_camera * matrice_position;
}

void VueOpenGL::turnAround(double angle, double dir_x, double dir_y, double dir_z)
{
    psi += angle * dir_x;
    omega += angle * dir_z;
    updatePosition();
}


void VueOpenGL::updatePosition(){
    matrice_position.setToIdentity();
    matrice_position.translate(0.0,0.0,rho); //rho negatif
    matrice_position.rotate(psi, 1.0, 0.0, 0.0);
    matrice_position.rotate(omega, 0.0, 0.0, 1.0);

    matrice_vue = matrice_camera * matrice_position;
}

// ======================================================================
void VueOpenGL::dessineCube (QMatrix4x4 const& point_de_vue)
{
  prog.setUniformValue("vue_modele", matrice_vue * point_de_vue);

  glBegin(GL_QUADS);
  // face coté X = +1
  prog.setAttributeValue(CouleurId, 1.0, 0.0, 0.0); // rouge
  prog.setAttributeValue(SommetId, +1.0, -1.0, -1.0);
  prog.setAttributeValue(SommetId, +1.0, +1.0, -1.0);
  prog.setAttributeValue(SommetId, +1.0, +1.0, +1.0);
  prog.setAttributeValue(SommetId, +1.0, -1.0, +1.0);

  // face coté X = -1
  prog.setAttributeValue(CouleurId, 0.0, 1.0, 0.0); // vert
  prog.setAttributeValue(SommetId, -1.0, -1.0, -1.0);
  prog.setAttributeValue(SommetId, -1.0, -1.0, +1.0);
  prog.setAttributeValue(SommetId, -1.0, +1.0, +1.0);
  prog.setAttributeValue(SommetId, -1.0, +1.0, -1.0);

  // face coté Y = +1
  prog.setAttributeValue(CouleurId, 0.0, 0.0, 1.0); // bleu
  prog.setAttributeValue(SommetId, -1.0, +1.0, -1.0);
  prog.setAttributeValue(SommetId, -1.0, +1.0, +1.0);
  prog.setAttributeValue(SommetId, +1.0, +1.0, +1.0);
  prog.setAttributeValue(SommetId, +1.0, +1.0, -1.0);

  // face coté Y = -1
  prog.setAttributeValue(CouleurId, 0.0, 1.0, 1.0); // cyan
  prog.setAttributeValue(SommetId, -1.0, -1.0, -1.0);
  prog.setAttributeValue(SommetId, +1.0, -1.0, -1.0);
  prog.setAttributeValue(SommetId, +1.0, -1.0, +1.0);
  prog.setAttributeValue(SommetId, -1.0, -1.0, +1.0);

  // face coté Z = +1
  prog.setAttributeValue(CouleurId, 1.0, 1.0, 0.0); // jaune
  prog.setAttributeValue(SommetId, -1.0, -1.0, +1.0);
  prog.setAttributeValue(SommetId, +1.0, -1.0, +1.0);
  prog.setAttributeValue(SommetId, +1.0, +1.0, +1.0);
  prog.setAttributeValue(SommetId, -1.0, +1.0, +1.0);

  // face coté Z = -1
  prog.setAttributeValue(CouleurId, 1.0, 0.0, 1.0); // magenta
  prog.setAttributeValue(SommetId, -1.0, -1.0, -1.0);
  prog.setAttributeValue(SommetId, -1.0, +1.0, -1.0);
  prog.setAttributeValue(SommetId, +1.0, +1.0, -1.0);
  prog.setAttributeValue(SommetId, +1.0, -1.0, -1.0);

  glEnd();
}

void VueOpenGL::dessinePlan (QMatrix4x4 const& point_de_vue)
{
    prog.setUniformValue("vue_modele", matrice_vue * point_de_vue);

    glBegin(GL_QUADS);


    prog.setAttributeValue(CouleurId, 0.8, 0.8, 0.8);
    prog.setAttributeValue(SommetId, -2.0, +2.0, 0.0);
    prog.setAttributeValue(SommetId, -2.0, -2.0, 0.0);
    prog.setAttributeValue(SommetId, +2.0, -2.0, 0.0);
    prog.setAttributeValue(SommetId, +2.0, +2.0, 0.0);
    glEnd();

}

void VueOpenGL::dessineRepere (QMatrix4x4 const& point_de_vue)
{
    prog.setUniformValue("vue_modele", matrice_vue * point_de_vue);

    glBegin(GL_LINES);
    prog.setAttributeValue(CouleurId, 1.0, 0.0, 0.0);
    prog.setAttributeValue(SommetId, 0.0, 0.0, 0.0);
    prog.setAttributeValue(SommetId, +1.0, 0.0, 0.0);

    prog.setAttributeValue(CouleurId, 0.0, 1.0, 0.0);
    prog.setAttributeValue(SommetId, 0.0, 0.0, 0.0);
    prog.setAttributeValue(SommetId, 0.0, +1.0, 0.0);

    prog.setAttributeValue(CouleurId, 0.0, 0.0, 1.0);
    prog.setAttributeValue(SommetId, 0.0, 0.0, 0.0);
    prog.setAttributeValue(SommetId, 0.0, 0.0, +1.0);

    glEnd();



}



void VueOpenGL::dessineSphere (QMatrix4x4 const& point_de_vue,
                               double rouge, double vert, double bleu)
{
  prog.setUniformValue("vue_modele", matrice_vue * point_de_vue);
  prog.setAttributeValue(CouleurId, rouge, vert, bleu);  // met la couleur
  sphere.draw(prog, SommetId);                           // dessine la sphère
}
void VueOpenGL::dessineCone (QMatrix4x4 const& point_de_vue)
{
  prog.setUniformValue("vue_modele", matrice_vue * point_de_vue);
  cone.draw(prog);                           // dessine la sphère
}

/*void VueOpenGL::dessineToupie(Toupie* toupie){
    QMatrix4x4 matricecone;
    matricecone.rotate(toupie->getP()[0] *180/pi, 0.0,0.0,1.0);
    matricecone.rotate(toupie->getP()[1] *180/pi, 1.0,0.0,0.0);
    matricecone.rotate(toupie->getP()[2] *180/pi, 0.0,0.0,1.0);
    dessineSphere(matricecone);
}

void VueOpenGL::dessineToupie(ConeSimple* toupie){
    QMatrix4x4 matricecone;
    matricecone.rotate(toupie->getP()[0] *180/pi, 0.0,0.0,1.0);
    matricecone.rotate(toupie->getP()[1] *180/pi, 1.0,0.0,0.0);
    matricecone.rotate(toupie->getP()[2] *180/pi, 0.0,0.0,1.0);
    matricecone.scale(toupie->getRayon(), toupie->getHauteur(), 1.0);
    dessineCone(matricecone);
}
void VueOpenGL::dessineToupie(ToupieChinoise* toupie){
    QMatrix4x4 matricecone;
    matricecone.rotate(toupie->getP()[0] *180/pi, 0.0,0.0,1.0);
    matricecone.rotate(toupie->getP()[1] *180/pi, 1.0,0.0,0.0);
    matricecone.rotate(toupie->getP()[2] *180/pi, 0.0,0.0,1.0);
    dessineCone(matricecone);
}
*/
