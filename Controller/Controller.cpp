#include "Controller.h"

Controller::Controller() {
  model_ = new Model(this);
  view_ = new View(this);
}

void Controller::StartGame(int) {
  // model_->SetDataBase(lvl_id);
}

void Controller::Tick() {
}

