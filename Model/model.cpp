#include "model.h"

void Model::SetGameLevel(int level_id) {
  LoadDatabase();

  Enemy temporary_enemy;
  temporary_enemy.SetParameters(1);
  temporary_enemy.SetAnimationParameters(std::shared_ptr<QPixmap>(&enemy_images_[0]));
  id_to_enemy_.push_back(temporary_enemy);
  temporary_enemy.SetParameters(4);
  temporary_enemy.SetAnimationParameters(std::shared_ptr<QPixmap>(&enemy_images_[0]));
  id_to_enemy_.push_back(temporary_enemy);
  LoadLevelFromJson(level_id);

  empty_towers_ = {{420, 310}, {720, 330}, {480, 675}, {480, 800},
                   {775, 565}, {940, 565}, {1105, 565}, {765, 775},
                   {1225, 775}, {1570, 775}, {1730, 600}, {1400, 540},
                   {1430, 310}};
  Building building_instance;
  building_instance.SetParameters(0, QColor(Qt::gray), 0, 0);
  upgrades_tree_.push_back({1, 2});

  Building building_instance2;
  building_instance2.SetParameters(1, Qt::white, 2, 175);
  upgrades_tree_.push_back({3, 0});

  Building building_instance3;
  building_instance3.SetParameters(2, Qt::darkRed, 3, 215);
  upgrades_tree_.push_back({1, 3, 0});

  Building building_instance4;
  building_instance4.SetParameters(3, Qt::darkBlue, 4, 275);
  upgrades_tree_.push_back({0});

  id_to_building_.push_back(building_instance);
  id_to_building_.push_back(building_instance2);
  id_to_building_.push_back(building_instance3);
  id_to_building_.push_back(building_instance4);

  InitializeTowerSlots();
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

std::list<std::shared_ptr<Enemy>>* Model::GetEnemies() {
  return &enemies_;
}

Enemy Model::GetEnemyById(int id) const {
  return id_to_enemy_[id];
}

const std::vector<EnemyGroup>& Model::GetEnemyGroupsPerRound(int round) const {
  return enemy_groups_[round];
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

void Model::InitializeTowerSlots() {
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
  // Create new building by id
  buildings_[i] = std::make_shared<Building>(id_to_building_[id]);
  buildings_[i]->SetPosition(position);
}

void Model::UpgradeBuildingAtIndex(int i) {
  buildings_[i]->Upgrade();
}

const Building& Model::GetBuildingById(int id) const {
  return id_to_building_[id];
}

const std::vector<std::vector<int>>& Model::GetUpgradesTree() const {
  return upgrades_tree_;
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

  time_between_rounds_ = json_object["time_between_rounds"].toInt();
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

  map_ = QPixmap(":resources/levels/map_level_" +
      QString::number(level) + ".png");
}

const QPixmap& Model::GetMapImage() const {
  return map_;
}

void Model::LoadDatabase() {
  enemy_images_.emplace_back(":resources/database/enemy.png");
}
