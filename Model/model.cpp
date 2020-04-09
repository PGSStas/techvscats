#include "model.h"

void Model::SetGameLevel(int level_id) {
  LoadLevelFromJson(level_id);

  Building building_instance;
  building_instance.SetParameters(0, QColor(Qt::gray), 0, 0);
  upgrades_tree_.push_back({1, 2});

  Building building_instance2;
  building_instance2.SetParameters(1, Qt::white, 2, 75);
  upgrades_tree_.push_back({3, 0});

  Building building_instance3;

  building_instance3.GetAuricField()->SetParameters(200, 2);

  building_instance3.SetParameters(2, Qt::darkRed, 3, 100);
  upgrades_tree_.push_back({1, 3, 0});

  Building building_instance4;
  building_instance4.SetParameters(3, Qt::darkBlue, 4, 150);
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

  base_ = std::make_shared<Base>(
      json_object["base"].toObject()["max_health"].toDouble());

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

  empty_towers_.clear();
  QJsonArray json_empty_towers = json_object["empty_towers"].toArray();
  int empty_towers_count = json_empty_towers.size();
  empty_towers_.reserve(empty_towers_count);

  QJsonObject json_empty_tower;
  for (int i = 0; i < empty_towers_count; i++) {
    json_empty_tower = json_empty_towers[i].toObject();
    empty_towers_.emplace_back(json_empty_tower["x"].toDouble(),
                               json_empty_tower["y"].toDouble());
  }
}

void Model::LoadDatabaseFromJson() {
  QFile level_file(":resources/database/database.json");
  if (!level_file.open(QFile::ReadOnly)) {
    qDebug() << "ERROR! Missing database file";
    return;
  }

  QJsonObject json_object =
      QJsonDocument::fromJson(level_file.readAll()).object();

  QJsonArray effects = json_object["effects"].toArray();
  int effects_count = effects.size();
  id_to_effect_.reserve(effects_count);

  QJsonObject effect;
  for (int i = 0; i < effects_count; i++) {
    effect = effects[i].toObject();
    id_to_effect_.emplace_back(
        static_cast<EffectTarget>(effect["effect_target"].toInt()),
        effect["speed_coefficient"].toDouble(),
        effect["armor_coefficient"].toDouble(),
        effect["damage_coefficient"].toDouble(),
        effect["attack_rate_coefficient"].toDouble(),
        effect["range_coefficient"].toDouble());
  }

  QJsonArray enemies = json_object["enemies"].toArray();
  int enemies_count = enemies.size();
  id_to_enemy_.reserve(enemies_count);

  QJsonObject enemy;
  for (int i = 0; i < enemies_count; i++) {
    enemy = enemies[i].toObject();
    Enemy new_enemy(enemy["damage"].toInt(),
                    enemy["armor"].toInt(),
                    enemy["reward"].toInt(),
                    enemy["speed"].toInt(),
                    enemy["max_health"].toInt());
    if (enemy.contains("aura")) {
      new_enemy.GetAuricField()->SetParameters(
          enemy["aura"].toObject()["radius"].toInt(),
          enemy["aura"].toObject()["effect_id"].toInt());
    }
    id_to_enemy_.push_back(new_enemy);
  }
}

Model::Model() {
  current_round_number_ = 0;
  LoadDatabaseFromJson();
}

const Effect& Model::GetEffectById(int id) const {
  return id_to_effect_[id];
}

std::shared_ptr<Base> Model::GetBase() const {
  return base_;
}
