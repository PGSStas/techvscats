#include "spawner.h"

Spawner::Spawner(const Road& road_to_spawn,
                 const Wave& wave_to_spawn,
                 int current_time) {
  if (wave_to_spawn.enemies.size() == 0) {
    is_dead_ = true;
    return;
  }
  road_to_spawn_ = road_to_spawn;
  wave_to_spawn_ = wave_to_spawn;
  last_time_spawn_ = current_time;
  current_enemy_count = wave_to_spawn.enemies[current_pack_number].times;
}

void Spawner::Tick(int current_time) {
  if (current_time - last_time_spawn_ < wave_to_spawn_.frequency) {
    return;
  }
  qDebug() << &road_to_spawn_ << "this road";

  is_ready_to_spawn_ = true;
  last_time_spawn_ = current_time;
  enemy_to_spawn_ = wave_to_spawn_.enemies[current_pack_number].enemy;
  current_enemy_count--;

  // Start spawning from next pack
  if (current_enemy_count == 0) {
    current_pack_number++;
    if (current_pack_number
        == static_cast<int>(wave_to_spawn_.enemies.size())) {
      is_dead_ = true;
    } else {
      current_enemy_count = wave_to_spawn_.enemies[current_pack_number].times;
    }
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
  return enemy_to_spawn_;
}



