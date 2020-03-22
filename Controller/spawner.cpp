#include "spawner.h"

Spawner::Spawner(int road_number_,
                 const Wave& wave_to_spawn,
                 int current_time)
    : last_time_spawn_(current_time),
      wave_to_spawn_(wave_to_spawn),
      road_to_spawn_number_(road_number_){
  if (wave_to_spawn_.enemies.empty()) {
    is_dead_ = true;
    return;
  }

}

void Spawner::Tick(int current_time) {
  if (current_time - last_time_spawn_ < wave_to_spawn_.frequency) {
    return;
  }
  qDebug() << road_to_spawn_number_ << "this road";

  is_ready_to_spawn_ = true;
  last_time_spawn_ = current_time;
  enemy_to_spawn_ = wave_to_spawn_.enemies.begin()->enemy;
  if (--wave_to_spawn_.enemies.begin()->times != 0) {
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
  return is_ready_to_spawn_;
}

const Enemy& Spawner::GetEnemy() {
  is_ready_to_spawn_ = false;
  return enemy_to_spawn_;
}

int Spawner::GetRoadNumber() const {
  return road_to_spawn_number_;
}



