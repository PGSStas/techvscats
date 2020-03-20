#ifndef CONTROLLER_CONTROLLER_H_
#define CONTROLLER_CONTROLLER_H_

#include <vector>
#include <memory>

#include "abstract_controller.h"
#include "View/view.h"
#include "Model/model.h"

// This class controls the interaction between objects.
class Controller : public AbstractController {
 public:
  Controller();
  ~Controller() override = default;

  void StartGame(int level) override;
  void Tick() override;

 private:
  std::unique_ptr<Model> model_;
  std::unique_ptr<View> view_;
};

#endif  // CONTROLLER_CONTROLLER_H_
