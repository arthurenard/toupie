#include <QApplication>
#include "glwidget.h"
#include "configuration.h"
#include <QPushButton>

int main(int argc, char* argv[])
{
  QApplication a(argc, argv);
  //GLWidget w;
  Configuration config;
  config.show();

  //w.show();

  return a.exec();
}
