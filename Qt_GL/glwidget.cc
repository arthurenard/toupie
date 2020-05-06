#include <QKeyEvent>
#include <QTimerEvent>
#include <QMatrix4x4>
#include "glwidget.h"

// ======================================================================
void GLWidget::initializeGL()
{
  vue.init();
  timerId = startTimer(20);
  pause();
 // this->resize(1920, 1080);

}

// ======================================================================
void GLWidget::resizeGL(int width, int height)
{
  /* On commance par dire sur quelle partie de la 
   * fenêtre OpenGL doit dessiner.
   * Ici on lui demande de dessiner sur toute la fenêtre.
   */
  glViewport(0, 0, width, height);

  /* Puis on modifie la matrice de projection du shader.
   * Pour ce faire on crée une matrice identité (constructeur 
   * par défaut), on la multiplie par la droite par une matrice
   * de perspective.
   * Plus de détail sur cette matrice
   *     http://www.songho.ca/opengl/gl_projectionmatrix.html
   * Puis on upload la matrice sur le shader à l'aide de la
   * méthode de la classe VueOpenGL
   */
  QMatrix4x4 matrice;
  matrice.perspective(70.0, qreal(width) / qreal(height ? height : 1.0), 1e-3, 1e5);
  vue.setProjection(matrice);
}

// ======================================================================
void GLWidget::paintGL()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  c.dessine();
}


// ======================================================================
void GLWidget::keyPressEvent(QKeyEvent* event)
{
  constexpr double petit_angle(2.5); // en degrés
  constexpr double petit_pas(0.1);

  switch (event->key()) {

  case Qt::Key_Left:
    vue.turnAround(petit_angle, 0.0, 0.0, 1.0);
    break;

  case Qt::Key_Right:
    vue.turnAround(-petit_angle, 0.0, 0.0, 1.0);
    break;

  case Qt::Key_Up:
    vue.turnAround(petit_angle, +1.0, 0.0, 0.0);
    break;

  case Qt::Key_Down:
    vue.turnAround(-petit_angle, +1.0, 0.0, 0.0);
    break;

  case Qt::Key_PageUp:
  case Qt::Key_Z:
    vue.move(petit_pas);
    break;

  case Qt::Key_PageDown:
  case Qt::Key_S:
    vue.move(-petit_pas);
    break;

  case Qt::Key_Q:
    vue.rotateCamera(-petit_angle, 0.0, 0.0, 1.0);
    break;

  case Qt::Key_D:
    vue.rotateCamera(petit_angle, 0.0, 0.0, 1.0);
    break;

  case Qt::Key_H:
    vue.initializePosition();
    break;
  case Qt::Key_Escape:
      close();
      break;

  case Qt::Key_F1:
      toggleFullWindow();
      break;

  case Qt::Key_Space:
	pause();
	break;

  case Qt::Key_O:
    speed-=1;
    if(speed < 1)
        speed=1;
    break;

    case Qt::Key_P:
      speed+= 1;
     break;
   };

  update(); // redessine
}
void GLWidget::mousePressEvent(QMouseEvent* event)
{
  lastMousePosition = event->pos();
}


void GLWidget::mouseMoveEvent(QMouseEvent* event)
{
  /* If mouse tracking is disabled (the default), the widget only receives
   * mouse move events when at least one mouse button is pressed while the
   * mouse is being moved.
   *
   * Pour activer le "mouse tracking" if faut lancer setMouseTracking(true)
   * par exemple dans le constructeur de cette classe.
   */

  if (event->buttons() & Qt::LeftButton) {
    constexpr double petit_angle(.4); // en degrés

    // Récupère le mouvement relatif par rapport à la dernière position de la souris
    QPointF d = event->pos() - lastMousePosition;
    lastMousePosition = event->pos();

    vue.rotateCamera(petit_angle * d.manhattanLength(), d.y(), d.x(), 0);

    update();
  }


}
// ======================================================================
void GLWidget::timerEvent(QTimerEvent* event)
{
  Q_UNUSED(event);

  double dt = chronometre.restart() / 1000.0;
  for (int i(1);i<=speed;i++) {
      c.evolue(dt/speed);//*360);
  }

  update();
}

// ======================================================================
void GLWidget::pause()
{
  if (timerId == 0) {
	// dans ce cas le timer ne tourne pas alors on le lance
    timerId = startTimer(20);
	chronometre.restart();
  } else {
	// le timer tourne alors on l'arrête
	killTimer(timerId);
	timerId = 0;
  }
}

void GLWidget::toggleFullWindow()
{
    if(b_Fullscreen)
    {
        showNormal();
        b_Fullscreen = false;
    }
    else
    {
        showFullScreen();
        b_Fullscreen = true;
    }
}
size_t GLWidget::nb_toupie(){
    return c.nbToupies();
}
void GLWidget::addToupie(std::vector<double> data){
    c.addToupie(data);
}
void GLWidget::delToupie(size_t id){
    c.delToupie(id);
    emit toupieDeleted();
}
