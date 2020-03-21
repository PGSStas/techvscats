#ifndef CONTROLLER_SPAWNER_H_
#define CONTROLLER_SPAWNER_H_

#include <memory>

#include "Model/wave.h"
#include "Model/road.h"
#include "GameObject/enemy.h"
// The Spawner is installed on the road, and creates enemies from wave.
class Spawner {
 public:
  Spawner(const Road& road_to_spawn_, const Wave& wave, int current_time);
  ~Spawner() = default;
  bool IsReadyToSpawn() const;
  bool IsDead() const;
  void Tick(int current_time);
  const Enemy& GetEnemy();

 private:
  int last_time_enemy_spawn_;
  bool is_ready_to_spawn_ = false;
  bool is_dead_ = false;
  const Enemy* enemy_to_spawn_ = nullptr;
  const Wave* wave_to_spawn_;
  const Road* road_to_spawn_;
  int current_pack_number = 0;
  int current_enemy_number = 0;
};

#endif  // CONTROLLER_SPAWNER_H_
