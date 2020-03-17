#include "controller.h"

Controller::Controller(MainWindow* window) {
  model_ = new Model(this);
  view_ = new View(window, this);
}

void Controller::StartGame(int) {
  // model_->SetDataBase(lvl_id);
}

void Controller::Tick() {

}

