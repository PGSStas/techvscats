#include "spawner.h"

#include <utility>

Spawner::Spawner(const Road& road,
                 Wave wave_to_spawn,
                 int current_time)
    : last_time_spawn_(current_time),
      wave_to_spawn_(std::move(wave_to_spawn)),
      spawning_road_(road) {
  if (wave_to_spawn_.enemies.empty()) {
    is_dead_ = true;
    return;
  }
}

void Spawner::Tick(int current_time) {
  if (current_time - last_time_spawn_ < wave_to_spawn_.frequency) {
    return;
  }
  // qDebug() << "road" << road_to_spawn_number_;

  unit_pending_ = true;
  last_time_spawn_ = current_time;
  enemy_to_spawn_ = wave_to_spawn_.enemies.begin()->enemy;
  enemy_to_spawn_.SetRoad(spawning_road_);
  wave_to_spawn_.enemies.begin()->times--;
  if (wave_to_spawn_.enemies.begin()->times != 0) {
    return;
  }
  // Start spawning from next pack
  wave_to_spawn_.enemies.pop_front();
  if (wave_to_spawn_.enemies.empty()) {
    is_dead_ = true;
  }
}

bool Spawner::IsDead() const {
  return is_dead_;
}

bool Spawner::IsReadyToSpawn() const {
  return unit_pending_;
}

const Enemy& Spawner::GetEnemy() {
  unit_pending_ = false;
  return enemy_to_spawn_;
}

/*int Spawner::GetRoadNumber() const {
  return spawning_road_;
}*/



