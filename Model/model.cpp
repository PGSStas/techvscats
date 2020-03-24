#include "model.h"

void Model::SetGameModel(int level_id) {
  current_round_number_ = 0;
  EnemyPack temporary_enemy_pack;
  EnemyPack temporary_enemy_pack2;
  Enemy temporary_enemy;
  Wave temporary_wave;

  std::vector<Coordinate> nodes;

  switch (level_id) {
    case 0:
      // To be changed. All this is need to be downloaded form file.
      temporary_enemy.SetParametres(1);
      gold_ = 100;
      score_ = 0;
      // Pack with enemies
      temporary_enemy_pack.enemy = temporary_enemy;
      temporary_enemy_pack.times = 2;

      temporary_enemy.SetParametres(4);
      temporary_enemy_pack2.enemy = temporary_enemy;
      temporary_enemy_pack2.times = 7;


      // Wave, that holds some packs.
      temporary_wave.period = 2000;
      temporary_wave.enemies.push_back(temporary_enemy_pack);
      // Set roads and rounds
      roads_count_ = 2;
      rounds_count_ = 2;
      rounds_.resize(rounds_count_, std::vector<Wave>(roads_count_));
      // Put wave to rounds[round_number][road_number]
      rounds_[0][0] = temporary_wave;
      rounds_[0][1] = temporary_wave;
      temporary_wave.period = 100;
      temporary_wave.enemies.push_back(temporary_enemy_pack2);
      rounds_[1][1] = temporary_wave;

      nodes = {{800, 1000}, {600, 800}, {1060, 660}};
      Road temporary_road(nodes);
      roads_.push_back(temporary_road);
      nodes = {{100, 150}, {400, 150}, {500, 500}, {1060, 660}};

      Road temporary_road2(nodes);
      roads_.push_back(temporary_road2);

      time_between_ronds_ = 5000;
      // At the end we have : 2 roads , 2 rounds
      // 5 sec between rounds, 2 sec between enemy spawn in each wave.
      // 1 round 2 enemies on each road
      // 2 round 2 enemies on the second road
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

void Model::IncreaseCurrentRoundNumber() {
  current_round_number_++;
}

void Model::AddSpawner(int road_number, const Wave& wave, int current_time) {
  spawners_.emplace_back(GetRoad(road_number), wave, current_time);
}

const Road& Model::GetRoad(int i) const {
  return roads_.at(i);
}

const std::vector<Road>& Model::GetRoads() const {
  return roads_;
}

const Wave& Model::GetWave(int round_number, int road_number) const {
  return rounds_[round_number][road_number];
}

std::list<Spawner>* Model::GetSpawners() {
  return &spawners_;
}

std::list<std::shared_ptr<Enemy>>* Model::GetEnemies() {
  return &enemies_;
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
