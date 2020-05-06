#include <QApplication>
#include <QPushButton>
#include <QtWidgets>
#include "mainwindow.h"
#include "glwidget.h"

int main(int argc, char* argv[])
{
  QApplication a(argc, argv);

  Mainwindow window;

  window.show();
  return a.exec();
}
