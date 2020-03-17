#include "controller.h"

Controller::Controller() {
  model_ = new Model();
  view_ = new View();
}

Controller::~Controller() {
  delete model_;
  delete view_;
}
