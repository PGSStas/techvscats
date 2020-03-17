#ifndef VIEW_H
#define VIEW_H

#include <QObject>
#include <Controller/controller.h>

class Controller;
class Enemy;
class MainWindow;

class View {
 public:
  View(MainWindow*, Controller*);
  Controller* controller;
  MainWindow* main_window;
  ~View();
 private:
};

#endif // VIEW_H
