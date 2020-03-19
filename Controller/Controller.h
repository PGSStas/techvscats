#ifndef CONTROLLER_CONTROLLER_H_
#define CONTROLLER_CONTROLLER_H_

#include <vector>
#include "AbstractController.h"

#include "View/View.h"
#include "Model/Model.h"

// This class controls the interaction between objects.
class Controller : public AbstractController {
 public:
  Controller();
  ~Controller() override = default;

  void StartGame(int level) override;
  void Tick() override;

 private:
  Model* model_;
  View* view_;
};

#endif  // CONTROLLER_CONTROLLER_H_
