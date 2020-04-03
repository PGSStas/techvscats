#include "model.h"

void Model::SetGameLevel(int level_id) {
  Enemy temporary_enemy;
  temporary_enemy.SetParameters(1);
  id_to_enemy_.push_back(temporary_enemy);
  temporary_enemy.SetParameters(4);
  id_to_enemy_.push_back(temporary_enemy);
  LoadLevelFromJson(level_id);

  empty_towers_ = {{100, 100}, {200, 100}, {500, 100}};
  Building temporary_building_instance;
  temporary_building_instance.SetParameters(0, QColor(Qt::gray), 0, 0);
  buildings_tree_.push_back({1, 2});

  MultiTower temporary_multi_tower_instance1;
  temporary_multi_tower_instance1.SetParameters(1, Qt::white, 2, 75);
  buildings_tree_.push_back({3, 0});

  DefaultTower temporary_default_tower_instance1;
  temporary_default_tower_instance1.SetParameters(2, Qt::darkRed, 3, 100);
  buildings_tree_.push_back({1, 3, 0});

  DefaultTower temporary_default_tower_instance2;
  temporary_default_tower_instance2.SetParameters(3, Qt::darkBlue, 4, 150);
  buildings_tree_.push_back({0});

  id_to_building_.push_back(temporary_building_instance);
  id_to_building_.push_back(temporary_multi_tower_instance1);
  id_to_building_.push_back(temporary_default_tower_instance1);
  id_to_building_.push_back(temporary_default_tower_instance2);

  InitialiseTowerSlots();
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

void Model::AddSpawner(const EnemyGroup& enemy_group) {
  spawners_.emplace_back(enemy_group);
}

const Road& Model::GetRoad(int i) const {
  return roads_.at(i);
}

const std::vector<Road>& Model::GetRoads() const {
  return roads_;
}

std::list<Spawner>* Model::GetSpawners() {
  return &spawners_;
}

const std::list<std::shared_ptr<Enemy>>& Model::GetEnemies() {
  return enemies_;
}

Enemy Model::GetEnemyById(int id) const {
  return id_to_enemy_[id];
}

const std::vector<EnemyGroup>& Model::GetEnemyGroupsPerRound(int round) const {
  return enemy_groups_[round];
}

int Model::GetRoadsCount() const {
  return roads_count_;
}

void Model::AddEnemyFromInstance(const Enemy& enemy_instance) {
  enemies_.push_back(std::make_shared<Enemy>(enemy_instance));
}

void Model::ClearGameModel() {
  current_round_number_ = 0;
  roads_count_ = 0;
  rounds_count_ = 0;
  enemies_.clear();
  buildings_.clear();
  projectiles_.clear();
  spawners_.clear();
  enemy_groups_.clear();
  roads_.clear();
  empty_towers_.clear();
  qDebug() << "Clear Model";
}

void Model::InitialiseTowerSlots() {
  for (Coordinate coordinate : empty_towers_) {
    auto empty_place = std::make_shared<Building>(id_to_building_[0]);
    empty_place->SetPosition(coordinate);
    buildings_.push_back(empty_place);
  }
}

const std::vector<std::shared_ptr<Building>>& Model::GetBuildings() const {
  return buildings_;
}

void Model::SetBuildingAtIndex(int i, int id) {
  qDebug() << "set b" << i << " " << id;
  Coordinate position = buildings_[i]->GetPosition();
  buildings_[i] = GetNewBuildingById(id);
  buildings_[i]->SetPosition(position);
}

void Model::UpgradeBuildingAtIndex(int i) {
  buildings_[i]->Upgrade();
}

std::shared_ptr<Building> Model::GetNewBuildingById(int id) const {
  const auto& instance = id_to_building_[id];
  switch (instance.GetTowerType()) {
    case 0:
      return std::make_shared<Building>(instance);

    case 1:
      return std::make_shared<DefaultTower>(instance);

    case 2:
      return std::make_shared<MultiTower>(instance);

    default:
      return nullptr;
  }
}

const std::vector<std::vector<int>>& Model::GetBuildingsTree() const {
  return buildings_tree_;
}

void Model::RemoveDeadSpawners() {
  spawners_.remove_if([](const Spawner& sp) { return sp.IsDead(); });
}

void Model::LoadLevelFromJson(int level) {
  QFile level_file(":resources/levels/level_"
                       + QString::number(level) + ".json");
  if (!level_file.open(QFile::ReadOnly)) {
    qDebug() << "ERROR! Missing level file";
    return;
  }
  QJsonObject json_object =
      QJsonDocument::fromJson(level_file.readAll()).object();

  time_between_ronds_ = json_object["time_between_rounds"].toInt();
  gold_ = json_object["gold"].toInt();
  score_ = json_object["score"].toInt();

  roads_.clear();
  QJsonArray json_roads = json_object["roads"].toArray();
  roads_count_ = json_roads.size();
  roads_.reserve(roads_count_);

  QJsonArray json_road_nodes;
  QJsonObject json_node;
  for (int i = 0; i < roads_count_; i++) {
    json_road_nodes = json_roads[i].toArray();

    int node_count = json_road_nodes.size();
    std::vector<Coordinate> nodes;
    nodes.reserve(node_count);
    for (int j = 0; j < node_count; j++) {
      json_node = json_road_nodes[j].toObject();
      nodes.emplace_back(json_node["x"].toDouble(),
                         json_node["y"].toDouble());
    }
    roads_.emplace_back(nodes);
  }

  enemy_groups_.clear();
  QJsonArray json_rounds = json_object["rounds"].toArray();
  rounds_count_ = json_rounds.size();
  enemy_groups_.reserve(rounds_count_);

  QJsonArray json_enemy_groups;
  QJsonObject json_enemy_group;
  for (int i = 0; i < rounds_count_; i++) {
    json_enemy_groups = json_rounds[i].toArray();

    int group_count = json_enemy_groups.size();
    std::vector<EnemyGroup> groups;
    groups.reserve(group_count);
    for (int j = 0; j < group_count; j++) {
      json_enemy_group = json_enemy_groups[j].toObject();
      groups.emplace_back(json_enemy_group["spawn_period"].toInt(),
                          json_enemy_group["enemy_id"].toInt(),
                          json_enemy_group["time_of_next_spawn"].toInt(),
                          json_enemy_group["group_size"].toInt(),
                          json_enemy_group["road_to_spawn"].toInt());
    }
    enemy_groups_.push_back(std::move(groups));
  }
}
