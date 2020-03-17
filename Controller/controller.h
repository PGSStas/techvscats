#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Model/model.h"
#include "View/view.h"
#include "enemy.h"
#include "mainwindow.h"

class Model;
class View;

class Controller {
 public:
  Controller(MainWindow*);
  void StartGame(int lvl = 1);
 private:
  Model* model_;
  View* view_;
  ~Controller();
};

#endif // CONTROLLER_H
