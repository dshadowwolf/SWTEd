#include <QApplication>
#include "include/mainwindow.h"

int main(int argc, char *argv[])
{
  Q_INIT_RESOURCE(swted);

  QApplication app(argc, argv);
  MainWindow mainWin;
  mainWin.show();
  return app.exec();
}
