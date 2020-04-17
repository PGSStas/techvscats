#include "spawner.h"

Spawner::Spawner(const EnemyGroup& group_to_spawn) :
    group_to_spawn_(group_to_spawn) {}

void Spawner::Tick(int current_time) {
  if (current_time < group_to_spawn_.time_of_next_spawn) {
    return;
  }
  unit_pending_ = true;
  group_to_spawn_.time_of_next_spawn += group_to_spawn_.spawn_period;
  group_to_spawn_.group_size--;
  if (group_to_spawn_.group_size == 0) {
    is_dead_ = true;
  }
}

int Spawner::PrepareNextEnemyId() {
  unit_pending_ = false;
  return group_to_spawn_.enemy_id;
}

int Spawner::GetRoad() const {
  return group_to_spawn_.road_to_spawn;
}

bool Spawner::IsReadyToSpawn() const {
  return unit_pending_;
}

bool Spawner::IsDead() const {
  return is_dead_;
}
