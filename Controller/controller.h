#ifndef CONTROLLER_H
#define CONTROLLER_H

#include<mainwindow.h>
#include<Model/model.h>
#include<View/view.h>
#include <vector>

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
