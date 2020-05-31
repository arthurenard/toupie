#include "vue_opengl.h"
#include "vertex_shader.h" // Identifiants Qt de nos différents attributs


// ======================================================================
VueOpenGL::~VueOpenGL()
{
  // Libère la mémoire des textures
  QGLContext* context =  const_cast<QGLContext*>(QGLContext::currentContext());
  context->deleteTexture(textureDeChat);
  context->deleteTexture(textureBlanche);
  context->deleteTexture(texturenous);
  context->deleteTexture(epfl);
}

void VueOpenGL::dessine(Systeme const& systeme)
{
  loadWhiteTexture();
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  dessineRepere();
  dessineContour();

  for(size_t i(0); i < systeme.nbToupies(); i++){
    dessineToupie(systeme.getToupie(i));
    if(systeme.getTrace()){
        dessineTrace(systeme.getToupie(i), i);
    }
  }

  for(size_t i(0); i < systeme.nbBalles(); i++){
    dessineBalle(systeme.getBalle(i));
  }

  if(systeme.getWTF()){
      drawJCC(0,0,systeme.getNyan());
      drawNousWTF();
  }
  else{
      dessinePlan();
      drawBY();
  }
}

// ======================================================================
void VueOpenGL::init()
{
  initializeOpenGLFunctions();

  prog.addShaderFromSourceFile(QOpenGLShader::Vertex,   ":/vertex_shader.glsl");
  prog.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fragment_shader.glsl");

  prog.bindAttributeLocation("sommet",  SommetId);
  prog.bindAttributeLocation("coordonnee_texture", CoordonneeTextureId);
  prog.bindAttributeLocation("couleur", CouleurId);

  prog.link();
  prog.bind();

  glEnable(GL_DEPTH_TEST);
  //glEnable(GL_CULL_FACE);

  QGLContext* context =  const_cast<QGLContext*>(QGLContext::currentContext());
  textureDeChat = context->bindTexture(QPixmap(":/nyan.png"), GL_TEXTURE_2D);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

  textureBlanche = context->bindTexture(QPixmap(":/whitetexture.jpg"), GL_TEXTURE_2D);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

  texturenous = context->bindTexture(QPixmap(":/by.png"), GL_TEXTURE_2D);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  epfl = context->bindTexture(QPixmap(":/logoepfl.jpg"), GL_TEXTURE_2D);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  sphere.initialize();
  chinoise = GlChinoise();
  cone = Glcone();

  initializePosition();
}

// ======================================================================
void VueOpenGL::initializePosition()
{
  // position initiale
    rho = -10.0;
    psi= -65;
    omega = 30;
  matrice_position.setToIdentity();
  matrice_position.translate(0.0, 0.0, rho);
  matrice_position.rotate(psi, 1.0, 0.0, 0.0);
  matrice_position.rotate(omega, 0.0, 0.0, 1.0);
  matrice_camera.setToIdentity();
  matrice_camera.rotate(-5,1.,0.,0.);
  matrice_vue = matrice_camera * matrice_position;
}

void VueOpenGL::loadWhiteTexture(){
    prog.setUniformValue("textureId", 0);
    QOpenGLFunctions *glFuncs = QOpenGLContext::currentContext()->functions();
    glFuncs->glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureBlanche);
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


void VueOpenGL::dessinePlan (QMatrix4x4 const& point_de_vue)
{
    prog.setUniformValue("vue_modele", matrice_vue * point_de_vue);
    //glDisable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);
    prog.setAttributeValue(CouleurId, 0.8, 0.8, 0.8);
    prog.setAttributeValue(SommetId, -10.0, +10.0, 0.0);
    prog.setAttributeValue(SommetId, -10.0, -10.0, 0.0);
    prog.setAttributeValue(SommetId, +10.0, -10.0, 0.0);
    prog.setAttributeValue(SommetId, +10.0, +10.0, 0.0);
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

void VueOpenGL::dessineSphere (QMatrix4x4 const& point_de_vue, double rouge, double vert, double bleu)
{
  prog.setUniformValue("vue_modele", matrice_vue * point_de_vue);
  prog.setAttributeValue(CouleurId, rouge, vert, bleu);  // met la couleur
  sphere.draw(prog, SommetId);                           // dessine la sphère
}

void VueOpenGL::dessineCone (QMatrix4x4 const& point_de_vue, double paraColor)
{
  prog.setUniformValue("vue_modele", matrice_vue * point_de_vue);
  cone.draw(prog, gradColor(paraColor));
}

void VueOpenGL::dessineChinoise(const QMatrix4x4 &point_de_vue, double hauteurNorm,double paraColor){
    prog.setUniformValue("vue_modele", matrice_vue * point_de_vue);
    chinoise.draw(prog, hauteurNorm ,gradColor(paraColor));
}

void VueOpenGL::dessineToupie(Toupie* toupie){
    QMatrix4x4 matriceToupie;
    matriceToupie.translate(toupie->get_vect_dP()[3],toupie->get_vect_dP()[4]);

    matriceToupie.rotate(toupie->get_vect_P()[0] *180/pi, 0.0,0.0,1.0);
    matriceToupie.rotate(toupie->get_vect_P()[1] *180/pi, 1.0,0.0,0.0);
    matriceToupie.rotate(toupie->get_vect_P()[2] *180/pi, 0.0,0.0,1.0);

    if(toupie->getType()==CONIQUE || toupie->getType() == CONIQUEG){
    matriceToupie.scale(toupie->getRayon(), toupie->getRayon(), toupie->getHauteur());
    dessineCone(matriceToupie, toupie->get_vect_dP()[2]/5.);
    }
    if(toupie->getType()==CONIQUEE){
    matriceToupie.scale(toupie->getRayon(), toupie->getRayon(), toupie->getHauteur());
    dessineCone(matriceToupie, 1.0);
    }

    if(toupie->getType()==CHINOISE){
        matriceToupie.scale(toupie->getRayon());
        dessineChinoise(matriceToupie, toupie->getHauteur()/toupie->getRayon(), toupie->get_vect_dP()[2]/5.);
    }

}
void VueOpenGL::dessineBalle(Balle *balle){
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    QMatrix4x4 matriceBalle;
    matriceBalle.translate(balle->get_vect_P()[0],balle->get_vect_P()[1], balle->get_vect_P()[2]);
    matriceBalle.scale(balle->getRayon());

    dessineSphere(matriceBalle,balle->getRVB()[0],balle->getRVB()[1],balle->getRVB()[2]);
}

void VueOpenGL::dessineTrace(Toupie *toupie, size_t nb){
QMatrix4x4 position;
    prog.setUniformValue("vue_modele", matrice_vue * position);

    glBegin(GL_LINE_STRIP);
         if(nb%6 == 0){    prog.setAttributeValue(CouleurId, 1.0, 0.0, 1.0); }
    else if(nb%6 == 1){    prog.setAttributeValue(CouleurId, 1.0, 1.0, 1.0); }
    else if(nb%6 == 2){    prog.setAttributeValue(CouleurId, 0.0, 1.0, 0.0); }
    else if(nb%6 == 3){    prog.setAttributeValue(CouleurId, 0.0, 0.0, 1.0); }
    else if(nb%6 == 4){    prog.setAttributeValue(CouleurId, 1.0, 0.0, 0.0); }
    else {    prog.setAttributeValue(CouleurId, 0.0, 1.0, 1.0); }

    for(size_t i(0) ; i < toupie->nbVectTrace() ; i++){
        prog.setAttributeValue(SommetId, toupie->getVectNb(i)[0], toupie->getVectNb(i)[1], toupie->getVectNb(i)[2]);
    }
   glEnd();
}

void VueOpenGL::drawJCC(double x, double y, double z){
    QMatrix4x4 point_de_vue;
    point_de_vue.translate(x,y,z-3.);
    prog.setUniformValue("vue_modele", matrice_vue * point_de_vue);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      prog.setUniformValue("textureId", 0);

    QOpenGLFunctions *glFuncs = QOpenGLContext::currentContext()->functions();
    glFuncs->glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureDeChat);

    glBegin(GL_QUADS);
    // X+
    prog.setAttributeValue(CouleurId, 1, 1, 1);

    prog.setAttributeValue(CoordonneeTextureId, 1.0, 0.0);
    prog.setAttributeValue(SommetId, +20.0, -20.0, 0.0);
    prog.setAttributeValue(CoordonneeTextureId, 0.0, 0.0);
    prog.setAttributeValue(SommetId, +20.0, +20.0, 0.0);
    prog.setAttributeValue(CoordonneeTextureId, 0.0, 1.0);
    prog.setAttributeValue(SommetId, +20.0, +20.0, +15.0);
    prog.setAttributeValue(CoordonneeTextureId, 1.0, 1.0);
    prog.setAttributeValue(SommetId, +20.0, -20.0, +15.0);

    prog.setAttributeValue(CoordonneeTextureId, 0.0, 0.0);
    prog.setAttributeValue(SommetId, -20.0, -20.0, 0.0);
    prog.setAttributeValue(CoordonneeTextureId, 1.0, 0.0);
    prog.setAttributeValue(SommetId, -20.0, +20.0, 0.0);
    prog.setAttributeValue(CoordonneeTextureId, 1.0, 1.0);
    prog.setAttributeValue(SommetId, -20.0, +20.0, +15.0);
    prog.setAttributeValue(CoordonneeTextureId, 0.0, 1.0);
    prog.setAttributeValue(SommetId, -20.0, -20.0, +15.0);

    prog.setAttributeValue(CoordonneeTextureId, 0.0, 0.0);
    prog.setAttributeValue(SommetId, -20.0, +20.0, 0.0);
    prog.setAttributeValue(CoordonneeTextureId, 1.0, 0.0);
    prog.setAttributeValue(SommetId, +20.0, +20.0, 0.0);
    prog.setAttributeValue(CoordonneeTextureId, 1.0, 1.0);
    prog.setAttributeValue(SommetId, +20.0, +20.0, +15.0);
    prog.setAttributeValue(CoordonneeTextureId, 0.0, 1.0);
    prog.setAttributeValue(SommetId, -20.0, +20.0, +15.0);

    prog.setAttributeValue(CoordonneeTextureId, 1.0, 0.0);
    prog.setAttributeValue(SommetId, -20.0, -20.0, 0.0);
    prog.setAttributeValue(CoordonneeTextureId, 0.0, 0.0);
    prog.setAttributeValue(SommetId, +20.0, -20.0, 0.0);
    prog.setAttributeValue(CoordonneeTextureId, 0.0, 1.0);
    prog.setAttributeValue(SommetId, +20.0, -20.0, +15.0);
    prog.setAttributeValue(CoordonneeTextureId, 1.0, 1.0);
    prog.setAttributeValue(SommetId, -20.0, -20.0, +15.0);

    glFuncs->glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureBlanche);
    glEnd();
}

std::vector<double> VueOpenGL::gradColor(double x){
    double r,v,b;
    std::vector<double> RVB;
    x = 6 * fmod(abs(x), 1.0);
    if(x>=0. && x<1.){
        r=1.0;
        v=0.0;
        b=x;
    }
    if(x>=1. && x<2.){
        r=2.0-x;
        v=0.0;
        b=1.0;
    }
    if(x>=2. && x<3.){
        r=0.0;
        v=x - 2.0;
        b=1.0;
    }
    if(x>=3. && x<4.){
        r=0.0;
        v=1.0;
        b=4.0-x;
    }
    if(x>=4. && x<5.){
        r=x - 4.0;
        v=1.0;
        b=0.0;
    }
    if(x>=5. && x<=6.){
        r=1.0;
        v=6.0 - x;
        b=0.0;
    }
    RVB.push_back(r);
    RVB.push_back(v);
    RVB.push_back(b);
    return RVB;
}

void VueOpenGL::drawNousWTF(QMatrix4x4 const& point_de_vue){
    prog.setUniformValue("vue_modele", matrice_vue * point_de_vue);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      prog.setUniformValue("textureId", 0);

    QOpenGLFunctions *glFuncs = QOpenGLContext::currentContext()->functions();
    glFuncs->glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texturenous);

    glBegin(GL_QUADS);
    // X+
    prog.setAttributeValue(CouleurId, 1, 1, 1);
    prog.setAttributeValue(CoordonneeTextureId, 0.0, 0.0);
    prog.setAttributeValue(SommetId, -10.0, -10.0, 0.0);
    prog.setAttributeValue(CoordonneeTextureId, 0.0, 10.0);
    prog.setAttributeValue(SommetId, -10.0, +10.0, 0.0);
    prog.setAttributeValue(CoordonneeTextureId, 10.0, 10.0);
    prog.setAttributeValue(SommetId, +10.0, +10.0, +0.0);
    prog.setAttributeValue(CoordonneeTextureId, 10.0, 0.0);
    prog.setAttributeValue(SommetId, +10.0, -10.0, +0.0);

    glFuncs->glActiveTexture(GL_TEXTURE0); // On la lie à nouveau au numéro 0 (comme ca on a pas besoin de changer "textureId" du shader)
    glBindTexture(GL_TEXTURE_2D, textureBlanche);
    glEnd();
}
void VueOpenGL::dessineContour( QMatrix4x4 point_de_vue){
    dessineBarriere(point_de_vue);
    point_de_vue.rotate(90, 0.,0.,1.0);
    dessineBarriere(point_de_vue);
    point_de_vue.rotate(90, 0.,0.,1.0);
    dessineBarriere(point_de_vue);
    point_de_vue.rotate(90, 0.,0.,1.0);
    dessineBarriere(point_de_vue);

}
void VueOpenGL::dessineBarriere(const QMatrix4x4 &point_de_vue){
    prog.setUniformValue("vue_modele", matrice_vue * point_de_vue);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      prog.setUniformValue("textureId", 0);

    QOpenGLFunctions *glFuncs = QOpenGLContext::currentContext()->functions();
    glFuncs->glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, epfl);

    glBegin(GL_QUADS);
    prog.setAttributeValue(CouleurId, 1, 1, 1);

    prog.setAttributeValue(CoordonneeTextureId, 0.0, 0.0);
    prog.setAttributeValue(SommetId, -10.0, +10.0, 0.0);
    prog.setAttributeValue(CoordonneeTextureId, 10.0, 0.0);
    prog.setAttributeValue(SommetId, +10.0, +10.0, 0.0);
    prog.setAttributeValue(CoordonneeTextureId, 10.0, 1.0);
    prog.setAttributeValue(SommetId, +10.0, +10.0, +0.7);
    prog.setAttributeValue(CoordonneeTextureId, 0.0, 1.0);
    prog.setAttributeValue(SommetId, -10.0, +10.0, +0.7);

    glFuncs->glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureBlanche);
    glEnd();
}

void VueOpenGL::drawBY(QMatrix4x4 const& point_de_vue){
    prog.setUniformValue("vue_modele", matrice_vue * point_de_vue);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      prog.setUniformValue("textureId", 0);

    QOpenGLFunctions *glFuncs = QOpenGLContext::currentContext()->functions();
    glFuncs->glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texturenous);

    glBegin(GL_QUADS);
    // X+
    prog.setAttributeValue(CouleurId, 1, 1, 1);
    prog.setAttributeValue(CoordonneeTextureId, 0.0, 0.0);
    prog.setAttributeValue(SommetId, 10.0, 20.0, 0.0);
    prog.setAttributeValue(CoordonneeTextureId, 1.0, 0.0);
    prog.setAttributeValue(SommetId, 20.0, 10.0, 0.0);
    prog.setAttributeValue(CoordonneeTextureId, 1.0, 1.0);
    prog.setAttributeValue(SommetId, 20.0, 10.0, 12.0);
    prog.setAttributeValue(CoordonneeTextureId, 0.0, 1.0);
    prog.setAttributeValue(SommetId, 10.0, 20.0, 12.0);

    glFuncs->glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureBlanche);
    glEnd();
}
