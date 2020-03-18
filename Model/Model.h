#ifndef MODEL_MODEL_H_
#define MODEL_MODEL_H_

#include <vector>
#include "GameObject/Enemy.h"
#include "Wave.h"
#include "Road.h"

class Model {
 public:
  ~Model() = default;
 private:
  // Data that update all time
  std::vector<GameObject*> obj_handler;
  std::vector<std::vector<Wave>> Rounds;
  std::vector<Road*> roads;
  // vector<Building*> buildings;
  std::vector<Enemy*> enemies;
  int gold_{};
  int score_{};
  // Data that update ones
};

#endif  // MODEL_MODEL_H_
