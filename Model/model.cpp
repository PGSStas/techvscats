#include "model.h"

void Model::SetGameLevel(int level_id) {
  Enemy temporary_enemy;
  temporary_enemy.SetParameters(1);

  id_to_enemy_.push_back(temporary_enemy);
  temporary_enemy.SetParameters(4);
  id_to_enemy_.push_back(temporary_enemy);
  LoadLevelFromJson(level_id);

  empty_towers_ = {{540, 700}, {200, 100}, {500, 100}};

  Building building_instance(0, 0, 0, 0, Size(33,33), enemies_);
  building_instance.SetParameters();
  building_instance.SetAnimationParameters(Qt::gray,
                                           1000);

  upgrades_tree_.push_back({1, 2});

  Building building_instance2(1, 4, 10, 24, Size(40,20), enemies_);
  building_instance2.SetParameters(1, 340, 3, 0);
  building_instance2.SetAnimationParameters(Qt::blue, 1000,
                                            Qt::red, 300,
                                            Qt::darkBlue, 100);
  upgrades_tree_.push_back({3, 0});

  Building building_instance3(2, 4, 10, 24, Size(30,50), enemies_);
  building_instance3.SetParameters(11, 240, 1, 0);
  building_instance3.SetAnimationParameters(Qt::yellow, 400,
                                            Qt::red, 100,
                                            Qt::darkYellow, 100);
  upgrades_tree_.push_back({3, 1, 0});

  Building building_instance4(3, 4, 10, 24, Size(14,32), enemies_);
  building_instance4.SetParameters(1, 140, 1, 0);
  building_instance4.SetAnimationParameters(Qt::green, 1000,
                                            Qt::red, 300,
                                            Qt::darkGreen, 100);
  upgrades_tree_.push_back({1, 0});
  Projectile projectile_instance(Size(10,20),7,100);
  projectile_instance.SetAnimationParameters(Qt::darkRed);
  id_to_projectile_.push_back(projectile_instance);

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

const Enemy& Model::GetEnemyById(int id) const {
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

std::vector<std::shared_ptr<Building>>* Model::GetBuildings() {
  return &buildings_;
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

}

void Model::InitializeTowerSlots() {
  for (Coordinate coordinate : empty_towers_) {
    auto empty_place = std::make_shared<Building>(id_to_building_[0]);
    empty_place->SetPosition(coordinate);
    buildings_.push_back(empty_place);
  }
}

std::list<std::shared_ptr<Projectile>>* Model::GetProjectiles() {
  return &projectiles_;
}

const Projectile& Model::GetProjectileById(int id) const {
  return id_to_projectile_[id];
}

void Model::CreateProjectiles(const std::vector<Projectile>& projectiles) {
  for (auto& projectile:projectiles) {
    switch (projectile.GetType()) {
      case ProjectileType::kDefault:
        projectiles_.push_back(std::make_shared<Projectile>(projectile));

    }
  }
}
