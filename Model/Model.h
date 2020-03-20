#ifndef MODEL_MODEL_H_
#define MODEL_MODEL_H_

#include <vector>

// Game objects, that Model stores.
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

  void SetGameModel(int level);

 private:
  // Database which is loaded in SetGameModel and updated by Controller
  std::vector<std::shared_ptr<GameObject>> objects_;
  std::vector<std::shared_ptr<Building>> buildings_;
  std::vector<std::shared_ptr<Enemy>> enemies_;
  std::vector<std::vector<Wave>> rounds_;
  std::vector<Road> roads_;
  std::vector<Spawner> spawners_;
  int gold_;
  int score_;

  // Database of GameObject's instances, that is used to create GameObjects.
  std::vector<Enemy> id_to_Enemy_;
  std::vector<Building> id_to_Building_;
};

#endif  // MODEL_MODEL_H_
