#ifndef CONTROLLER_SPAWNER_H_
#define CONTROLLER_SPAWNER_H_

#include <memory>

#include "GameObject/enemy.h"
#include "Model/enemy_group.h"
#include "Model/road.h"

// The Spawner is installed on the road, and creates enemies from wave.
// It does not process or edit the Game data it received, working only with
// time and Wave/Road, which are also available to the controller
class Spawner {
 public:
  explicit Spawner(const EnemyGroup& wave);

  void Tick(int current_time);
  int PrepareNextEnemyId();
  int GetRoad() const;
  bool IsReadyToSpawn() const;
  bool IsDead() const;

 private:
  bool unit_pending_ = false;
  bool is_dead_ = false;
  EnemyGroup group_to_spawn_;
};

#endif  // CONTROLLER_SPAWNER_H_
