#ifndef CONTROLLER_SPAWNER_H_
#define CONTROLLER_SPAWNER_H_

#include <memory>

#include "Model/wave.h"
#include "Model/road.h"
#include "GameObject/enemy.h"
// The Spawner is installed on the road, and creates enemies from wave.
class Spawner {
 public:
  Spawner(Road* road_to_spawn_, Wave* wave, int current_time);
  ~Spawner() = default;
  bool IsReadyToSpawn();
  bool IsDead();
  void Tick(int current_time);
  Enemy* GetEnemy();

 private:
  int last_time_enemy_spawn_;
  bool is_ready_to_spawn_;
  bool is_dead_ = false;
  Enemy* enemy_to_spawn_;
  Wave* wave_to_spawn_;
  Road* road_to_spawn_;
  int current_pack_number = 0;
};

#endif  // CONTROLLER_SPAWNER_H_
