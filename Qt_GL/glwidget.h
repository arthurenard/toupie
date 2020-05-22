#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLWidget>        // Classe pour faire une fenêtre OpenGL
#include <QTime>            // Classe pour gérer le temps
#include "vue_opengl.h"
#include "Systeme.h"
#include <QSound>


class GLWidget : public QOpenGLWidget
/* La fenêtre hérite de QOpenGLWidget ;
 * les événements (clavier, souris, temps) sont des méthodes virtuelles à redéfinir.
 */
{
    Q_OBJECT

public:
  GLWidget(QWidget* parent = nullptr)
    : QOpenGLWidget(parent)
    , c(&vue), speed(1)
  {this->resize(1920, 1080);
   music = new QSound("music.wav");
  }


  virtual ~GLWidget() {}
  void toggleFullWindow();
  size_t nb_toupie();

public slots:
    void addToupie(std::vector<double> data);
    void delToupie(size_t id);
signals:
    void fullWindow();

private:
  // Les 3 méthodes clés de la classe QOpenGLWidget à réimplémenter
  virtual void initializeGL()                  override;
  virtual void resizeGL(int width, int height) override;
  virtual void paintGL()                       override;

  // Méthodes de gestion d'évènements
  virtual void keyPressEvent(QKeyEvent* event) override;
  virtual void timerEvent(QTimerEvent* event)  override;
  virtual void mousePressEvent(QMouseEvent* event) override;
  virtual void mouseMoveEvent(QMouseEvent* event)  override;
  // Méthodes de gestion interne
  void pause();

  // Vue : ce qu'il faut donner au contenu pour qu'il puisse se dessiner sur la vue
  VueOpenGL vue;

  // Timer
  int timerId;
  // pour faire évoluer les objets avec le bon "dt"
  QTime chronometre;
  QPoint lastMousePosition;


  // objets à dessiner, faire évoluer
  Systeme c;
  bool b_Fullscreen, WTF;
  int speed;
  QSound* music;
};

#endif // GLWIDGET_H
