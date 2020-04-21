#include "model.h"

Model::Model() {
  current_round_number_ = 0;
  LoadDatabase();
}

void Model::SetGameLevel(int level_id) {
  LoadLevel(level_id);

  AimedProjectile projectile_instance_aimed(Size(10, 20), 66);
  projectile_instance_aimed.SetAnimationParameters(Qt::darkRed, 100);

  BombProjectile projectile_instance_bomb(Size(10, 20), 45, 52, 120);
  projectile_instance_bomb.SetAnimationParameters(Qt::darkGreen, 100);

  LaserProjectile projectile_instance_lazer(Size(10, 20));
  projectile_instance_lazer.SetAnimationParameters(Qt::cyan, 160);

  id_to_projectile_.push_back(std::make_shared<AimedProjectile>(
      projectile_instance_aimed));
  id_to_projectile_.push_back(std::make_shared<BombProjectile>(
      projectile_instance_bomb));
  id_to_projectile_.push_back(std::make_shared<LaserProjectile>(
      projectile_instance_lazer));

  Building building_instance(0, 0);
  SetAnimationToGameObject(&building_instance, {500, 0, 0}, {
      "towers/default_tower_reload_4",
      "towers/default_tower_reload_4",
      "towers/default_tower_reload_4"});

  upgrades_tree_.push_back({1, 2});

  Building building_instance2(1, 24);
  building_instance2.SetProjectile(0, 10, 175, 2);
  SetAnimationToGameObject(&building_instance2, {1000, 300, 300}, {
      "towers/default_tower_reload_4",
      "towers/default_tower_pre_3",
      "towers/default_tower_post_3",
  });
  upgrades_tree_.push_back({3, 0});

  Building building_instance3(2, 24, Size(185, 185), AuricField(200, 2));
  building_instance3.SetProjectile(2, 3, 215, 3);
  SetAnimationToGameObject(&building_instance3, {100, 50, 10}, {
      "towers/default_tower_reload_4",
      "towers/default_tower_pre_3",
      "towers/default_tower_post_3",
  });
  upgrades_tree_.push_back({3, 1, 0});

  Building building_instance4(3, 24);
  building_instance4.SetProjectile(1, 54, 275, 1);
  SetAnimationToGameObject(&building_instance4, {1000, 600, 600}, {
      "towers/default_tower_reload_4",
      "towers/default_tower_pre_3",
      "towers/default_tower_post_3",
  });

  upgrades_tree_.push_back({1, 0});
  id_to_building_.push_back(building_instance);
  id_to_building_.push_back(building_instance2);
  id_to_building_.push_back(building_instance3);
  id_to_building_.push_back(building_instance4);

  InitializeTowerSlots();
}

void Model::AddSpawner(const EnemyGroup& enemy_group) {
  spawners_.emplace_back(enemy_group);
}

void Model::AddEnemyFromInstance(const Enemy& enemy_instance) {
  enemies_.push_back(std::make_shared<Enemy>(enemy_instance));
}

void Model::CreateBuildingAtIndex(int i, int id) {
  Coordinate position = buildings_[i]->GetPosition();
  // Create new building by id
  buildings_[i] = std::make_shared<Building>(id_to_building_[id]);
  buildings_[i]->SetPosition(position);
}

void Model::CreateProjectile(const std::shared_ptr<Enemy>& aim,
                             const Building& building) {
  int id = building.GetProjectileId();
  if (const auto& casted =
        std::dynamic_pointer_cast<AimedProjectile>(id_to_projectile_[id]);
      casted != nullptr) {
    projectiles_.push_back(std::make_shared<AimedProjectile>(*casted));
  }
  if (const auto& casted =
        std::dynamic_pointer_cast<BombProjectile>(id_to_projectile_[id]);
      casted != nullptr) {
    projectiles_.push_back(std::make_shared<BombProjectile>(*casted));
  }
  if (const auto& casted =
        std::dynamic_pointer_cast<LaserProjectile>(id_to_projectile_[id]);
      casted != nullptr) {
    projectiles_.push_back(std::make_shared<LaserProjectile>(*casted));
  }
  projectiles_.back()->SetParameters(aim, building.GetPosition(),
                                     building.GetProjectileSpeedCoefficient(),
                                     building.GetDamage());
}

void Model::RescaleDatabase(const SizeHandler& size_handler) {
  for (auto& enemy : enemies_) {
    enemy->Rescale(size_handler.GameToWindowSize(enemy->GetSize()));
  }
  for (auto& building : buildings_) {
    building->Rescale(size_handler.GameToWindowSize(building->GetSize()));
  }
  for (auto& enemy : id_to_enemy_) {
    enemy.Rescale(size_handler.GameToWindowSize(enemy.GetSize()));
  }
  for (auto& building : id_to_building_) {
    building.Rescale(size_handler.GameToWindowSize(building.GetSize()));
  }
  map_.Rescale(size_handler.GameToWindowSize(size_handler.GetGameSize()));
}

void Model::IncreaseCurrentRoundNumber() {
  current_round_number_++;
}

void Model::ClearGameModel() {
  current_round_number_ = 0;
  rounds_count_ = 0;
  enemies_.clear();
  buildings_.clear();
  projectiles_.clear();
  spawners_.clear();
  enemy_groups_.clear();
  roads_.clear();
  empty_places_for_towers_.clear();
}

Base* Model::GetBase() {
  return &base_;
}

std::list<Spawner>* Model::GetSpawners() {
  return &spawners_;
}

std::list<std::shared_ptr<Enemy>>* Model::GetEnemies() {
  return &enemies_;
}

std::list<std::shared_ptr<AbstractProjectile>>* Model::GetProjectiles() {
  return &projectiles_;
}

const std::vector<EnemyGroup>& Model::GetEnemyGroupsPerRound(int round) const {
  return enemy_groups_[round];
}

const std::vector<std::vector<int>>& Model::GetUpgradesTree() const {
  return upgrades_tree_;
}

const std::vector<std::shared_ptr<Building>>& Model::GetBuildings() const {
  return buildings_;
}

const Road& Model::GetRoad(int i) const {
  return roads_[i];
}

const Enemy& Model::GetEnemyById(int id) const {
  return id_to_enemy_[id];
}

const Effect& Model::GetEffectById(int id) const {
  return id_to_effect_[id];
}

const Building& Model::GetBuildingById(int id) const {
  return id_to_building_[id];
}

int Model::GetRoundsCount() const {
  return rounds_count_;
}

int Model::GetPrepairTimeBetweenRounds() const {
  return prepair_time_between_rounds_;
}

int Model::GetCurrentRoundNumber() const {
  return current_round_number_;
}

void Model::LoadLevel(int level) {
  QFile level_file(":resources/levels/level_"
                       + QString::number(level) + ".json");
  if (!level_file.open(QFile::ReadOnly)) {
    qDebug() << "ERROR! Missing level file";
    return;
  }
  QJsonObject json_object =
      QJsonDocument::fromJson(level_file.readAll()).object();

  prepair_time_between_rounds_ =
      json_object["prepair_time_between_rounds_"].toInt();
  gold_ = json_object["gold"].toInt();
  score_ = json_object["score"].toInt();

  // Reading information about the base.
  QJsonObject json_base = json_object["base"].toObject();
  QJsonObject json_base_position = json_base["position"].toObject();
  base_ = Base(json_base["max_health"].toDouble(),
               {json_base_position["x"].toDouble(),
                json_base_position["y"].toDouble()});

  // Reading information about the roads.
  roads_.clear();
  QJsonArray json_roads = json_object["roads"].toArray();
  int roads_count = json_roads.size();
  roads_.reserve(roads_count);

  QJsonArray json_road_nodes;
  QJsonObject json_node;
  for (int i = 0; i < roads_count; i++) {
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

  // Reading information about the enemy groups.
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

  // Reading information about the empty towers.
  empty_places_for_towers_.clear();
  QJsonArray json_empty_towers = json_object["empty_towers"].toArray();
  int empty_towers_count = json_empty_towers.size();
  empty_places_for_towers_.reserve(empty_towers_count);

  QJsonObject json_empty_tower;
  for (int i = 0; i < empty_towers_count; i++) {
    json_empty_tower = json_empty_towers[i].toObject();
    empty_places_for_towers_.emplace_back(json_empty_tower["x"].toDouble(),
                                          json_empty_tower["y"].toDouble());
  }
  map_ = AnimationPlayer(
      GetImagesByFramePath("map_level_" +
          QString::number(level) + "_1"));
}

const AnimationPlayer& Model::GetMap() const {
  return map_;
}

void Model::LoadDatabase() {
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
    AuricField aura;
    if (enemy.contains("aura")) {
      aura = AuricField(enemy["aura"].toObject()["radius"].toInt(),
                        enemy["aura"].toObject()["effect_id"].toInt());
    }
    // TODO(PGS): size of enemy please. Also i put speed on the second place.
    id_to_enemy_.emplace_back(enemy["speed"].toInt(),
                              enemy["damage"].toInt(),
                              enemy["armor"].toInt(),
                              enemy["reward"].toInt(),
                              enemy["max_health"].toInt(),
                              Size(
                                  enemy["size"].toObject()["width"].toInt(),
                                  enemy["size"].toObject()["height"].toInt()),
                              aura);
  }

  SetAnimationToGameObject(&id_to_enemy_[0], {400}, {"enemies/toster_3"});
  SetAnimationToGameObject(&id_to_enemy_[2], {550}, {"enemies/toster_3"});
  SetAnimationToGameObject(&id_to_enemy_[3], {600}, {"enemies/mouse_3"});
  SetAnimationToGameObject(&id_to_enemy_[4], {800}, {"enemies/mouse_3"});

  // Temporary part
  std::vector<EffectVisualization>
      effect_visualization = {{Qt::cyan, Qt::black},
                              {Qt::gray, Qt::darkGreen},
                              {Qt::blue, Qt::darkBlue},
                              {Qt::darkRed, Qt::magenta},
                              {Qt::white, Qt::yellow}};
  Effect::SetEffectVisualizations(effect_visualization);
}

void Model::InitializeTowerSlots() {
  buildings_.reserve(empty_places_for_towers_.size());
  for (Coordinate coordinate : empty_places_for_towers_) {
    auto empty_place = std::make_shared<Building>(id_to_building_[0]);
    empty_place->SetPosition(coordinate);
    buildings_.push_back(empty_place);
  }
}

void Model::SetAnimationToGameObject(
    GameObject* object, std::vector<int> timmings,
    std::vector<QString> paths) {
  std::vector<AnimationPlayer> animations;
  for (uint i = 0; i < timmings.size(); i++) {
    animations.emplace_back(GetImagesByFramePath(paths[i]), timmings[i]);
  }
  object->SetAnimationPlayers(animations);
}

std::shared_ptr<std::vector<QImage>> Model::GetImagesByFramePath(
    QString animation_last_frames, QString picture_type) const {

  QString clear_path = ":resources/images/" + animation_last_frames;
  QStringList splitted_path = clear_path.split("_");

  auto images = std::make_shared<std::vector<QImage>>();
  int count = splitted_path.back().toInt();

  for (int i = 1; i <= count; i++) {
    splitted_path.back() = QString::number(i);
    images->emplace_back(splitted_path.join("_") + picture_type);
  }

  return images;
}
