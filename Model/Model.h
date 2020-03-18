#ifndef MODEL_MODEL_H_
#define MODEL_MODEL_H_

#include <vector>
#include "Controller/Enemy.h"
#include "Wave.h"
#include "Road.h"

struct Map {
  std::vector<GameObject*> obj_handler;
  std::vector<std::vector<Wave>> Rounds;
  std::vector<Road*> roads;
  // vector<Building*> buildings;
  std::vector<Enemy*> enemies;
};

class Model {
 public:
  // void SetDataBase(int level_id);
  // Wave GetWave(int wave_id, int road_id);
  // Wave SumWaves(Wave*, Wave*)
  ~Model() = default;
  Map map;
 private:
  int gold_{};
  int score_{};
};

#endif  // MODEL_MODEL_H_
