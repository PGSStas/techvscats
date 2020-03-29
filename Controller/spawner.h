#ifndef CONTROLLER_SPAWNER_H_
#define CONTROLLER_SPAWNER_H_

#include <memory>
#include <QDebug>

#include "Model/enemy_group.h"
#include "Model/road.h"
#include "GameObject/enemy.h"

// The Spawner is installed on the road, and creates enemies from wave.
// It does not process or edit the Game data it received, working only with
// time and Wave/Road, which are also available to the controller
class Spawner {
 public:
  explicit Spawner(const EnemyGroup& wave);
  ~Spawner() = default;

  // int GetRoadNumber() const;
  bool IsReadyToSpawn() const;
  bool IsDead() const;
  int PrepareNextEnemyId();
  int GetRoad() const;

  void Tick(int current_time);

 private:
  bool unit_pending_ = false;
  bool is_dead_ = false;

  EnemyGroup group_to_spawn_;
};

#endif  // CONTROLLER_SPAWNER_H_
