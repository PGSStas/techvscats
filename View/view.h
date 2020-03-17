#ifndef VIEW_H
#define VIEW_H

#include <QObject>
#include <Controller/controller.h>

class Controller;

class View {
 public:
  View(MainWindow*, Controller*);
  Controller* controller;
  MainWindow* main_window;
  ~View();
};

#endif // VIEW_H
