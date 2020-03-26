#include "model.h"

void Model::SetGameModel(int level_id) {
  // To be changed. All this is need to be downloaded form file.
  current_round_number_ = 0;
  EnemyPack temporary_enemy_pack;
  EnemyPack temporary_enemy_pack2;
  Enemy temporary_enemy;
  Wave temporary_wave;
  Wave temporary_wave2;

  std::vector<Coordinate> nodes;

  // To be changed. All this is need to be downloaded form file.
  temporary_enemy.SetParametres(1);
  gold_ = 100;
  score_ = 0;
  // Pack with enemies
  temporary_enemy_pack.enemy = temporary_enemy;
  temporary_enemy_pack.times = 6;

  temporary_enemy.SetParametres(3);
  temporary_enemy_pack2.enemy = temporary_enemy;
  temporary_enemy_pack2.times = 7;

  // Wave, that holds some packs.
  temporary_wave.enemies.push_back(temporary_enemy_pack);
  // Set roads and rounds
  roads_count_ = 2;
  rounds_count_ = 2;
  rounds_.resize(rounds_count_);
  // Put wave to rounds[round_number][waves_count]
  temporary_wave.period = 2400;
  temporary_wave.road_number = 0;
  rounds_[0].push_back(temporary_wave);
  temporary_wave.period = 1000;
  temporary_wave.road_number = 1;
  rounds_[1].push_back(temporary_wave);
  temporary_wave2.period = 600;
  temporary_wave2.road_number = 1;
  temporary_wave2.enemies.push_back(temporary_enemy_pack2);
  rounds_[1].push_back(temporary_wave2);

  nodes = {{800, 1000}, {570, 840}, {600, 800}, {1500, 660}};
  Road temporary_road(nodes);
  roads_.push_back(temporary_road);
  nodes = {{100, 150}, {400, 300}, {500, 500}, {1500, 660}};

  Road temporary_road2(nodes);
  roads_.push_back(temporary_road2);

  time_between_rounds_ = 4000;

  tower_slots_ = {{100, 100}, {200, 100}, {500, 100}};
  InitialiseTowerSlots();
  building_count_ = 3;

  /* id_to_building_ =
      {std::make_shared<TowerSlot>(Coordinate(0, 0)),
       std::make_shared<FastTower>(Coordinate(0, 0)),
       std::make_shared<SlowTower>(Coordinate(0, 0))}; */

  // At the end we have : 2 roads , 2 rounds
  // 5 sec between rounds, 2 sec between enemy spawn in each wave.
  // 1 round 2 enemies on each road
  // 2 round 2 enemies on the second road
}

int Model::GetTimeBetweenWaves() const {
  return time_between_rounds_;
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

void Model::AddSpawner(const Wave& wave, int current_time) {
  spawners_.emplace_back(GetRoad(wave.road_number), wave, current_time);
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

int Model::GetWavesCount(int round_number) const {
  return rounds_[round_number].size();
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
  tower_slots_.clear();
}

const std::vector<Coordinate>& Model::GetTowerSlots() const {
  return tower_slots_;
}

void Model::InitialiseTowerSlots() {
  for (Coordinate c : tower_slots_) {
    buildings_.push_back(std::make_shared<TowerSlot>(c));
  }
}

const std::vector<std::shared_ptr<Building>>& Model::GetBuildings() const {
  return buildings_;
}

void Model::SetBuildingAt(int i, int id) {
  qDebug() << "set b" << i << " " << id;
  Coordinate pos = buildings_[i]->GetPosition();
  buildings_[i] = GetBuildingById(id);
  buildings_[i]->SetPosition(pos);
}

void Model::UpgradeBuildingAt(int i) {
  buildings_[i]->Upgrade();
}

std::shared_ptr<Building> Model::GetBuildingById(int id) {
  // See: problem with vector id_to_building_ in Model
  switch (id) {
    case 0:
      return std::make_shared<TowerSlot>();

    case 1:
      return std::make_shared<FastTower>();

    case 2:
      return std::make_shared<SlowTower>();
  }
}

int Model::GetBuildingCount() {
  return building_count_;
}

