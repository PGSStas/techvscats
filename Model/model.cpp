#include "model.h"
#include "QDebug"
void Model::SetGameModel(int level_id) {
  current_round_number_ = 0;
  gold_ = 100;
  score_ = 0;

  switch (level_id) {
    case 0: int x;

      // To be changed. All this is need to be downloaded form file.
      Enemy temporary_enemy;
      EnemyPack temporary_enemy_pack;
      temporary_enemy_pack.enemy = temporary_enemy;
      temporary_enemy_pack.times = 2;

      Wave temporary_wave;
      temporary_wave.frequency = 2000;
      temporary_wave.road_number = 0;
      temporary_wave.enemies.push_back(temporary_enemy_pack);

      roads_count_ = 1;
      rounds_count_ = 2;
      time_between_waves_ = 5000;
      rounds_.resize(rounds_count_, std::vector<Wave>(roads_count_));

      rounds_[0][0] = temporary_wave;

      roads_.resize(roads_count_);
      std::vector<Coordinate> nodes = {{0, 0}, {100, 100}};
      Road temporary_road(nodes);
      roads_[0] = temporary_road;
      // 1 road , 2 round , 2 enemies(no params) , nodes 0,0->100,100
      // 5 sec between waves, 2 sec between enemy spawn.
  }
}

int Model::GetTimeBetweenWaves() {
  return time_between_waves_;
}

int Model::GetRoundsCount() {
  return roads_count_;
}

int Model::GetCurrentRoundNumber() {
  return current_round_number_;
}

void Model::IncrementCurrentRoundNumber() {
  current_round_number_++;
}

void Model::AddSpawner(int road_number, Wave* wave,int current_time) {
  spawners_.emplace_back(&roads_[road_number], wave,current_time);
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
