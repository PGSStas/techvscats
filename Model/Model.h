#ifndef MODEL_MODEL_H_
#define MODEL_MODEL_H_

#include <vector>

// Game objects, that Model stores.
#include "GameObject/Enemy.h"
#include "GameObject/ActiveTower.h"
#include "GameObject/Building.h"
#include "GameObject/Projectile.h"

// The auxiliary model classes
#include "Controller/Spawner.h"
#include "Wave.h"
#include "Road.h"

class Model {
 public:
  Model() = default;
  ~Model() = default;

  void SetGameModel(int level);

 private:
  // Database which is loaded in SetGameModel and updated by Controller
  std::vector<GameObject> objects_;
  std::vector<Building*> buildings_;
  std::vector<Enemy*> enemies_;
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
