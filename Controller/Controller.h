#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include <vector>

#include "View/View.h"
#include "Model/Model.h"

class Controller : public AbstractController {
 public:
  Controller();
  ~Controller() override = default;
  void StartGame(int lvl) override;
  void Tick() override;
 private:
  Model* model_;
  View* view_;
};

#endif  // CONTROLLER_H
