#include "spawner.h"

Spawner::Spawner(const Road& road_to_spawn,
                 const Wave& wave_to_spawn,
                 int current_time)
    : last_time_enemy_spawn_(current_time),
      wave_to_spawn_(wave_to_spawn),
      road_to_spawn_(road_to_spawn) {
  if (wave_to_spawn_.enemies.empty()) {
    is_dead_ = true;
    return;
  }

}

void Spawner::Tick(int current_time) {
  if (current_time - last_time_enemy_spawn_ < wave_to_spawn_.frequency) {
    return;
  }
  qDebug() << &road_to_spawn_ << "this road";

  is_ready_to_spawn_ = true;
  last_time_enemy_spawn_ = current_time;
  enemy_to_spawn_ = wave_to_spawn_.enemies.begin()->enemy;
  if (--wave_to_spawn_.enemies.begin()->times != 0) {
    return;
  }
  wave_to_spawn_.enemies.pop_front();
  if (wave_to_spawn_.enemies.empty()) {
    is_dead_ = true;
  }
}

bool Spawner::IsDead() const {
  return is_dead_;
}

bool Spawner::IsReadyToSpawn() const {
  return is_ready_to_spawn_;
}

const Enemy& Spawner::GetEnemy() {
  is_ready_to_spawn_ = false;
  enemy_to_spawn_.SetRoad(road_to_spawn_);
  return enemy_to_spawn_;
}



