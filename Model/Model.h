#ifndef MODEL_MODEL_H_
#define MODEL_MODEL_H_

#include <vector>

// Game objects, that Model store.
#include "GameObject/Enemy.h"
#include "GameObject/ActiveTower.h"
#include "GameObject/Building.h"
#include "GameObject/Projectile.h"
#include "Controller/Spawner.h"
#include "Wave.h"
#include "Road.h"

class Model {
 public:
  ~Model() = default;

 private:
  // Data that update all time
  std::vector<GameObject> objects_;
  std::vector<Building*> buildings_;
  std::vector<Enemy*> enemies_;
  std::vector<std::vector<Wave>> rounds_;
  std::vector<Road> roads_;
  std::vector<Spawner> spawners_;
  int gold_;
  int score_;
  // Data that update ones
  std::vector<Enemy> id_to_Enemy_;
  std::vector<Building> id_to_Building_;
};

#endif  // MODEL_MODEL_H_
