#ifndef CONTROLLER_SPAWNER_H_
#define CONTROLLER_SPAWNER_H_

#include "Model/Wave.h"
#include "GameObject/Enemy.h"

// The Spawner is installed on the road, and creates enemies from
// Controller checks if ready_to_spawn, and if true, then it creates
// next_enemy_to_spawn on road_num_ and call NextEnemy (), so that the road
// can load an enemy from the wave.
class Spawner {
 public:
  Spawner(int road_number, Wave* wave);

  ~Spawner() = default;

  //
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
