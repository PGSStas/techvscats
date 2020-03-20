#include "model.h"

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
      temporary_enemy_pack.times = 3;

      Wave temporary_wave;
      temporary_wave.frequency = 1000;
      temporary_wave.road_number = 0;
      temporary_wave.enemies = temporary_enemy_pack;

      roads_count_ = 1;
      rounds_count_ = 1;
      time_between_waves_ = 10000;
      rounds_.resize(rounds_count_, std::vector<Wave>(roads_count_));

      rounds_[0][0] = temporary_wave;

      roads_.resize(roads_count_);
      std::vector<Coordinate> nodes = {{0, 0}, {100, 100}};
      Road temporary_road(nodes);
      roads_[0] = temporary_road;
      // 1 road , 1 round , 1 enemy(no params) , nodes 0,0->100,100
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

std::vector<std::shared_ptr<Projectile>> Model::GetProjectiles() {
  return projectiles_;
}

std::vector<std::shared_ptr<Building>> Model::GetBuildings() {
  return buildings_;
}

std::vector<std::shared_ptr<Enemy>> Model::GetEnemies() {
  return enemies_;
}

std::vector<std::vector<Wave>> Model::GetRounds() {
  return rounds_;
}

std::vector<Road> Model::GetRoads() {
  return roads_;
}

std::vector<Spawner> Model::GetSpawners() {
  return spawners_;
}

void Model::CreateSpawner(int road_number, Wave wave) {
  spawners_.emplace_back(road_number, wave);
}
