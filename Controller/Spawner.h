#ifndef CONTROLLER_SPAWNER_H_
#define CONTROLLER_SPAWNER_H_

#include "Model/Wave.h"
#include "GameObject/Enemy.h"

// The Spawner is installed on the road, and creates enemies from wave.
class Spawner {
 public:
  Spawner(int road_number, Wave* wave);

  ~Spawner() = default;

  void Tick(int current_time);
  void NextEnemy();

 private:
  bool ready_to_spawn_;
  int last_time_enemy_spawn_;
  Enemy* next_enemy_to_spawn_;
  Wave* wave_to_spawn_;
  int road_number_to_spawn_;
};

#endif  // CONTROLLER_SPAWNER_H_
