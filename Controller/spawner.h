#ifndef CONTROLLER_SPAWNER_H_
#define CONTROLLER_SPAWNER_H_

#include <memory>
#include <QDebug>

#include "Model/wave.h"
#include "Model/road.h"
#include "GameObject/enemy.h"

// The Spawner is installed on the road, and creates enemies from wave.
class Spawner {
 public:
  Spawner(const Road& road, Wave wave, int current_time);
  ~Spawner() = default;

  // int GetRoadNumber() const;
  bool IsReadyToSpawn() const;
  bool IsDead() const;
  const Enemy& GetEnemy();

  void Tick(int current_time);

 private:
  int last_time_spawn_;

  bool is_ready_to_spawn_ = false;
  bool is_dead_ = false;

  Wave wave_to_spawn_;
  const Road& road_to_spawn_;
  Enemy enemy_to_spawn_;

  int current_pack_number_ = 0;
};

#endif  // CONTROLLER_SPAWNER_H_
