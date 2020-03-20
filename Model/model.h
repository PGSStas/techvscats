#ifndef MODEL_MODEL_H_
#define MODEL_MODEL_H_

#include <vector>
#include <memory>

#include "GameObject/enemy.h"
//#include "GameObject/active_tower.h"
//#include "GameObject/building.h"
//#include "GameObject/projectile.h"

//#include "Controller/spawner.h"
//#include "wave.h"
//#include "road.h"

class Model {
 public:
  Model() = default;
  ~Model() = default;

  void SetGameModel(int level);

 private:
  // Database which is updated by Controller all time
/*  std::vector<std::shared_ptr<Projectile>> projectiles_;
  std::vector<std::shared_ptr<Building>> buildings_;
  std::vector<std::shared_ptr<Enemy>> enemies_;
  int current_round_number_;
  int gold_;
  int score_;

  //Database which is loaded in SetGameModel once
  std::vector<std::vector<Wave>> rounds_;
  std::vector<Road> roads_;
  std::vector<Spawner> spawners_;
  int time_between_waves_;
  int rounds_count_;
  int roads_count_;

  // Database of GameObject's instances, that is used to create GameObjects.
  std::vector<Enemy> id_to_enemy_;
  std::vector<Building> id_to_building_;*/
};

#endif  // MODEL_MODEL_H_
