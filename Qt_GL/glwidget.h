#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLWidget>
#include <QTime>
#include <QSound>
#include "vue_opengl.h"
#include "Systeme.h"

//Cette classe est construite a partir de l'exemple 5 de QT

class GLWidget : public QOpenGLWidget
{
    Q_OBJECT //Permet d'utiliser les signaux et slots

public:
  GLWidget(QWidget* parent = nullptr);
  virtual ~GLWidget() {}

  void toggleFullWindow(); //Permet le mode plein ecran en inversant un bool et emetant un signal
  size_t nb_toupie(); //Retourne le nombre de toupies du systeme, est utile car Mainwindow n'a pas d'acces direct au systeme

public slots:
    void addToupie(std::vector<double> data);//Transmet les données de AddToupie vers le systeme
    void delToupie(size_t nb);//Permet a mainwindow de supprimer la toupie d'index nb
    void delAll(); //Permet a mainwindow de supprimer toutes les toupies
    void sauvegarder(); //est appele lorsque l'utilisateur sauvegarde, permet de demander au systeme d'emettre le signal avec toutes les données

signals:
    void fullWindow(); //Envoie le signal de l'inversion de l'ecran a MainWindow
    void allDataSend(std::vector<std::vector<double>>); //Est emis quand on a recupere toutes les données du systeme
    void closeAll(); //est emis lorsque l'utilisateur appuie sur ECHAP
    void sendEverySecond(std::vector<std::vector<double>>);// ESt emis regulierement pour Information

private:
  // Les 3 méthodes clés de la classe QOpenGLWidget à réimplémenter
  virtual void initializeGL()                  override; //initialise la vue et le timer
  virtual void resizeGL(int width, int height) override; //est appele lorsque l'ecran est resize
  virtual void paintGL()                       override; //est appele lorsque l'ordinateur update le l'ecran

  // Méthodes de gestion d'évènements
  virtual void keyPressEvent(QKeyEvent* event) override; //Permet de gerer les evenements claviers
  virtual void timerEvent(QTimerEvent* event)  override; //Permet de gerer le temps, appelle Systeme::evolue(dt)
  virtual void mousePressEvent(QMouseEvent* event) override; //repris d'un exemple du cours
  virtual void mouseMoveEvent(QMouseEvent* event)  override; //repris d'un exemple du cours

  void pause(); //Coupe les evenement timer, met donc sur pause le systeme

  Systeme systeme; //Le dessinable
  VueOpenGL vue; //et son support

  size_t compteur; //permet de controler la frequence d'emission de données vers Information
  bool b_Fullscreen, WTF; //bool d'etat d'ecran, bool SURPRISE !!!!
  int speed; //Correspond au nombre d'appel de Systeme::evolue(dt) par image, augmente ou baisse la fiabilite de la simulation
  QSound* music; //Variable correspondant a du son

   //attributs liés a la gestion du temps et de la souris
  int timerId;
  QTime chronometre;
  QPoint lastMousePosition;
};

#endif // GLWIDGET_H
