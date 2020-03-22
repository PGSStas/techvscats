#include "model.h"

void Model::SetGameModel(int level_id) {
  current_round_number_ = 0;
  EnemyPack temporary_enemy_pack;
  Enemy temporary_enemy;
  Wave temporary_wave;
  Road temporary_road;
  std::vector<Coordinate> nodes = {{0, 0}, {100, 100}};

  switch (level_id) {
    case 0:
      // To be changed. All this is need to be downloaded form file.
      //temporary_enemy.SetSpeed(1);
      gold_ = 100;
      score_ = 0;
      // Pack with enemies
      temporary_enemy_pack.enemy = temporary_enemy;
      temporary_enemy_pack.times = 2;
      // Wave, that holds some packs.
      temporary_wave.frequency = 2000;
      temporary_wave.enemies.push_back(temporary_enemy_pack);
      // Set roads and rounds
      roads_count_ = 2;
      rounds_count_ = 2;
      rounds_.resize(rounds_count_, std::vector<Wave>(roads_count_));
      // Put wave to rounds[round_number][road_number]
      rounds_[0][0] = temporary_wave;
      rounds_[0][1] = temporary_wave;
      rounds_[1][1] = temporary_wave;

      roads_.resize(roads_count_);
      nodes = {{400, 400}, {500, 700}};
      temporary_road.SetRoad(nodes);
      roads_[0] = temporary_road;
      nodes = {{700, 500}, {400, 340}};
      temporary_road.SetRoad(nodes);
      roads_[1] = temporary_road;

      time_between_ronds_ = 5000;
      // At the end we have : 2 roads , 2 rounds
      // 5 sec between rounds, 2 sec between enemy spawn in each wave.
      // 1 round 2 enemies on each road
      // 2 round 2 enemies on the second road
      break;
    case 1://
      // temporary_enemy.SetSpeed(1);
      temporary_enemy_pack.enemy = temporary_enemy;
      temporary_enemy_pack.times = 1;
      // Wave, that holds some packs.
      temporary_wave.frequency = 2000;
      temporary_wave.enemies.push_back(temporary_enemy_pack);
      // Set roads and rounds
      roads_count_ = 1;
      rounds_count_ = 1;
      rounds_.resize(rounds_count_, std::vector<Wave>(roads_count_));
      // Put wave to rounds[round_number][road_number]
      rounds_[0][0] = temporary_wave;

      roads_.resize(roads_count_);
      nodes = {{100, 100}, {100, 102}, {100, 103}};
      temporary_road.SetRoad(nodes);
      roads_[0] = temporary_road;

      time_between_ronds_ = 1000;
      break;
  }
}

int Model::GetTimeBetweenWaves() const {
  return time_between_ronds_;
}

int Model::GetRoundsCount() const {
  return rounds_count_;
}

int Model::GetCurrentRoundNumber() const {
  return current_round_number_;
}

void Model::IncrementCurrentRoundNumber() {
  current_round_number_++;
}

void Model::AddSpawner(int road_number, const Wave& wave, int current_time) {
  spawners_.emplace_back(GetRoad(road_number), wave, current_time);
}

const Road& Model::GetRoad(int i) const {
  return roads_[i];
}

const Wave& Model::GetWave(int round_number, int road_number) const {
  return rounds_[round_number][road_number];
}

std::list<Spawner>* Model::GetSpawners() {
  return &spawners_;
}

int Model::GetRoadsCount() const {
  return roads_count_;
}

void Model::AddEnemyFromInstance(const Enemy& enemy_instance) {
  enemies_.push_back(std::make_shared<Enemy>(enemy_instance));
}

void Model::ClearGameModel() {
  qDebug() << "Clear Model";
  // will this part of the code correctly destroy shared ptr?
  current_round_number_ = 0;
  roads_count_ = 0;
  rounds_count_ = 0;
  enemies_.clear();
  buildings_.clear();
  projectiles_.clear();
  spawners_.clear();
  rounds_.clear();
  roads_.clear();
}
