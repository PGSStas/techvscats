#ifndef CONTROLLER_SPAWNER_H_
#define CONTROLLER_SPAWNER_H_

#include "Model/Wave.h"
#include "GameObject/Enemy.h"

// Spawner installs on a road, and spawn enemy from the wave,
// as help-class for controller.
// Controller check if ready_to_spawn, and if true, than it spawn
// next_enemy_to_spawn on the road_num_ and call NextEnemy(), so road
// can load Enemy from Wave.
class Spawner {
 public:
  Spawner(int road_number, Wave* wave);

  // Set's ready_to_spawn.
  void Tick(int current_time);
  void NextEemy();

 private:
  bool ready_to_spawn_;
  int last_time_enemy_spawn_;
  Enemy* next_enemy_to_spawn_;
  Wave* wave_to_spawn_;
  int road_number_to_spawn_;
};

#endif  // CONTROLLER_SPAWNER_H_
