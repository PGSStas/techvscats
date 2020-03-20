#include "controller.h"

Controller::Controller() : model_(std::make_unique<Model>()),
                           view_(std::make_unique<View>(this)) {
}

void Controller::StartGame(int level) {
  // model_->SetDataBase(lvl_id);
}

void Controller::Tick() {
}

