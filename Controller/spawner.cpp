#include "spawner.h"
#include <QDebug>
Spawner::Spawner(Road* road_to_spawn, Wave* wave_to_spawn, int current_time) {
  if (wave_to_spawn->enemies.size() == 0) {
    is_dead_ = true;
    return;
  }
  road_to_spawn_ = road_to_spawn_;
  wave_to_spawn_ = wave_to_spawn;
  last_time_enemy_spawn_ = current_time;
}

void Spawner::Tick(int current_time) {
  if (current_time - last_time_enemy_spawn_ < wave_to_spawn_->frequency) {
    return;
  }
  qDebug()<<this<<"this spawner";

  is_ready_to_spawn_ = true;
  last_time_enemy_spawn_ = current_time;
  enemy_to_spawn_ = &wave_to_spawn_->enemies[current_pack_number].enemy;
  wave_to_spawn_->enemies[current_pack_number].times--;
  if (wave_to_spawn_->enemies[current_pack_number].times != 0) {
    return;
  }
  current_pack_number++;
  if (current_pack_number == wave_to_spawn_->enemies.size()) {
    is_dead_ = true;
  }
}

bool Spawner::IsDead() {
  return is_dead_;

}

bool Spawner::IsReadyToSpawn() {
  return is_ready_to_spawn_;
}
Enemy* Spawner::GetEnemy() {
  is_ready_to_spawn_ = false;
  return enemy_to_spawn_;
}


