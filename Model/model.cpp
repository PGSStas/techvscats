#include "model.h"
#include "QDebug"
void Model::SetGameModel(int level_id) {
  current_round_number_ = 0;
  gold_ = 100;
  score_ = 0;

  switch (level_id) {
    case 0:
      // To be changed. All this is need to be downloaded form file.
      Enemy temporary_enemy;
      EnemyPack temporary_enemy_pack;
      temporary_enemy_pack.enemy = temporary_enemy;
      temporary_enemy_pack.times = 2;

      Wave temporary_wave;
      temporary_wave.frequency = 2000;
      temporary_wave.enemies.push_back(temporary_enemy_pack);

      roads_count_ = 2;
      rounds_count_ = 2;
      time_between_waves_ = 5000;
      rounds_.resize(rounds_count_, std::vector<Wave>(roads_count_));

      rounds_[0][0] = temporary_wave;
      rounds_[0][1] = temporary_wave;
      rounds_[1][1] = temporary_wave;

      roads_.resize(roads_count_);
      std::vector<Coordinate> nodes = {{0, 0}, {100, 100}};
      Road temporary_road(nodes);
      roads_[0] = temporary_road;
      // 2 road , 2 round
      // 5 sec between waves, 2 sec between enemy spawn.
      // 1 round 2 enemies on each road
      // 2 round 2 enemies on second road
  }
}

int Model::GetTimeBetweenWaves() {
  return time_between_waves_;
}

int Model::GetRoundsCount() {
  return rounds_count_;
}

int Model::GetCurrentRoundNumber() {
  return current_round_number_;
}

void Model::IncrementCurrentRoundNumber() {
  current_round_number_++;
}

void Model::AddSpawner(int road_number, Wave* wave, int current_time) {
  spawners_.emplace_back(GetRoad(road_number), wave, current_time);
}

Road* Model::GetRoad(int i) {
  return &roads_[i];
}

Wave* Model::GetWave(int round_number, int road_number) {
  return &rounds_[round_number][road_number];
}

std::list<Spawner>* Model::GetSpawners() {
  return &spawners_;
}

int Model::GetRoadsCount() {
  return roads_count_;
}

void Model::AddEnemy(Enemy* enemy_instance) {
  enemies_.push_back(std::make_shared<Enemy>(new Enemy()));
}
