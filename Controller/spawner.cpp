#include "spawner.h"
#include <QDebug>
Spawner::Spawner(const Road* road_to_spawn,
                 const Wave* wave_to_spawn,
                 int current_time) {
  if (wave_to_spawn->enemies.size() == 0) {
    is_dead_ = true;
    return;
  }
  is_ready_to_spawn_ = false;
  road_to_spawn_ = road_to_spawn;
  wave_to_spawn_ = wave_to_spawn;
  last_time_enemy_spawn_ = current_time;
  current_enemy_number = wave_to_spawn->enemies[current_pack_number].times;
}

void Spawner::Tick(int current_time) {
  if (current_time - last_time_enemy_spawn_ < wave_to_spawn_->frequency) {
    return;
  }
  qDebug() << road_to_spawn_ << "this road";

  is_ready_to_spawn_ = true;
  last_time_enemy_spawn_ = current_time;
  enemy_to_spawn_ = &wave_to_spawn_->enemies[current_pack_number].enemy;
  current_enemy_number--;
  if (current_enemy_number != 0) {
    return;
  }
  current_pack_number++;
  current_enemy_number = wave_to_spawn_->enemies[current_pack_number].times;
  if (current_pack_number == wave_to_spawn_->enemies.size()) {
    is_dead_ = true;
  }
}

bool Spawner::IsDead() const {
  return is_dead_;
}

bool Spawner::IsReadyToSpawn() const {
  return is_ready_to_spawn_;
}

const Enemy* Spawner::GetEnemy() {
  is_ready_to_spawn_ = false;
  return enemy_to_spawn_;
}


