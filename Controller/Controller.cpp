#include "Controller.h"

Controller::Controller() : model_(new Model()), view_(new View(this)) {
}

void Controller::StartGame(int level) {
  // model_->SetDataBase(lvl_id);
}

void Controller::Tick() {
}

