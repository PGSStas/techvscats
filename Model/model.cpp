#include "model.h"

Model::Model() {
  current_round_number_ = 0;
  LoadDatabase();
}

void Model::SetGameLevel(int level_id) {
  LoadLevel(level_id);
  InitializeTowerSlots();
}

void Model::AddSpawner(const EnemyGroup& enemy_group) {
  spawners_.emplace_back(enemy_group);
}

void Model::AddTextNotification(const TextNotification& text_notification) {
  text_notifications_.push_back(text_notification);
}

void Model::AddEnemyFromInstance(const Enemy& enemy_instance) {
  enemies_.push_back(std::make_shared<Enemy>(enemy_instance));
}

void Model::CreateBuildingAtIndex(int i, int id) {
  Coordinate position = buildings_[i]->GetPosition();
  // Create new building by id
  int sell_cost = buildings_[i]->GetTotalCost() + id_to_building_[id].GetCost();
  buildings_[i]->GetParticleHandler()->PlayOwnerDeath();
  CreateParticles(buildings_[i]->GetParticleHandler()->GetParticlesQueue());
  buildings_[i] = std::make_shared<Building>(id_to_building_[id]);
  if (id != 0) {
    buildings_[i]->SetTotalCost(sell_cost);
  }
  buildings_[i]->SetPosition(position);
}

void Model::CreateProjectile(const std::shared_ptr<Enemy>& aim,
                             const Building& building) {
  int id = building.GetProjectileId();
  if (const auto& casted =
        std::dynamic_pointer_cast<HomingProjectile>(id_to_projectile_[id]);
      casted != nullptr) {
    projectiles_.push_back(std::make_shared<HomingProjectile>(*casted));
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

void Model::CreateParticles(const std::list<ParticleParameters>& parameters) {
  for (const auto& particle_parameters : parameters) {
    particles_.push_back(id_to_particle_[particle_parameters.particle_id]);
    particles_.back().SetIfEmpty(particle_parameters.size,
                                 particle_parameters.position,
                                 particle_parameters.animation_times);
  }
}

void Model::RescaleDatabase(const SizeHandler& size_handler) {
  for (auto& enemy : enemies_) {
    enemy->Rescale(size_handler.GameToWindowSize(enemy->GetSize()));
  }
  for (auto& building : buildings_) {
    building->Rescale(size_handler.GameToWindowSize(building->GetSize()));
  }
  for (auto& projectile : projectiles_) {
    projectile->Rescale(size_handler.GameToWindowSize(projectile->GetSize()));
  }
  for (auto& particle : particles_) {
    particle.Rescale(size_handler.GameToWindowSize(particle.GetSize()));
  }
  for (auto& enemy : id_to_enemy_) {
    enemy.Rescale(size_handler.GameToWindowSize(enemy.GetSize()));
  }
  for (auto& building : id_to_building_) {
    building.Rescale(size_handler.GameToWindowSize(building.GetSize()));
  }
  for (auto& projectile : id_to_projectile_) {
    projectile->Rescale(size_handler.GameToWindowSize(projectile->GetSize()));
  }
  for (auto& particle : id_to_particle_) {
    particle.Rescale(size_handler.GameToWindowSize(particle.GetSize()));
  }
  if (base_ != nullptr) {
    base_->Rescale(size_handler.GameToWindowSize(base_->GetSize()));
  }
  for (auto& animaion : backgrounds_) {
    animaion.Rescale(size_handler.GameToWindowSize(size_handler.GetGameSize()));
  }
  interface_.Rescale(size_handler.GameToWindowSize(size_handler.GetGameSize()));
  Effect::Rescale(size_handler.GameToWindowSize(Effect::GetSize()));
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
  particles_.clear();
  text_notifications_.clear();
  spawners_.clear();
  enemy_groups_.clear();
  roads_.clear();
  empty_places_for_towers_.clear();
}

Base* Model::GetBase() {
  return base_.get();
}

std::list<Spawner>* Model::GetSpawners() {
  return &spawners_;
}

std::list<Particle>* Model::GetParticles() {
  return &particles_;
}

std::list<std::shared_ptr<Enemy>>* Model::GetEnemies() {
  return &enemies_;
}

std::list<std::shared_ptr<AbstractProjectile>>* Model::GetProjectiles() {
  return &projectiles_;
}

std::list<TextNotification>* Model::GetTextNotifications() {
  return &text_notifications_;
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

  // Reading information about the base.
  QJsonObject json_base = json_object["base"].toObject();
  QJsonObject json_base_position = json_base["position"].toObject();
  QJsonObject json_base_size = json_base["size"].toObject();
  base_ = std::make_shared<Base>(json_object["gold"].toInt(),
                                 Size(json_base_size["width"].toDouble(),
                                      json_base_size["height"].toDouble()),
                                 Coordinate(json_base_position["x"].toDouble(),
                                            json_base_position["y"].toDouble()),
                                 json_base["max_health"].toDouble());
  auto json_animation = json_base["animation"].toObject();
  SetAnimationToGameObject(base_.get(),
                           {json_animation["timing"].toInt()},
                           {json_animation["path"].toString()});
  SetParticlesToGameObject(base_.get(), json_base);
  base_->GetParticleHandler()->SetEvents({-1, -1, 2}, 0);
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

  // Map
  backgrounds_[3] = AnimationPlayer(
      GetImagesByFramePath("backgrounds/map_level_" +
          QString::number(level) + "_1"));

  empty_zone_texture_[3] = QImage(":resources/images/backgrounds/texture_level_"
                                      + QString::number(level) + ".png");
}

const AnimationPlayer& Model::GetBackGround(int background_id) const {
  return backgrounds_[background_id];
}

const AnimationPlayer& Model::GetInterface() const {
  return interface_;
}

const QImage& Model::GetEmptyZoneTexture(int index) const {
  return empty_zone_texture_[index];
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
    Size size = Size(enemy["size"].toObject()["width"].toInt(),
                     enemy["size"].toObject()["height"].toInt());
    id_to_enemy_.emplace_back(enemy["speed"].toInt(), enemy["damage"].toInt(),
                              enemy["armor"].toInt(), enemy["reward"].toInt(),
                              enemy["max_health"].toInt(),
                              size, enemy["priority"].toInt(), aura);
    SetAnimationToGameObject(
        &id_to_enemy_.back(),
        {enemy["animation"].toObject()["timing"].toInt()},
        {enemy["animation"].toObject()["path"].toString()});
    SetParticlesToGameObject(&id_to_enemy_.back(),
                             enemy["particles"].toObject());
  }

  SetAnimationToGameObject(&id_to_enemy_[0], {400}, {"enemies/toster_3"});
  SetAnimationToGameObject(&id_to_enemy_[2], {550}, {"enemies/toster_3"});
  SetAnimationToGameObject(&id_to_enemy_[3], {600}, {"enemies/mouse_3"});
  SetAnimationToGameObject(&id_to_enemy_[4], {800}, {"enemies/mouse_3"});

  // backgrounds
  backgrounds_.emplace_back(
      GetImagesByFramePath("backgrounds/main_background_1"));
  backgrounds_.emplace_back(
      GetImagesByFramePath("backgrounds/settings_background_1"));
  backgrounds_.emplace_back(
      GetImagesByFramePath("backgrounds/pause_menu_background_1"));
  backgrounds_.emplace_back(
      GetImagesByFramePath("error"));
  // interface
  interface_ = AnimationPlayer(GetImagesByFramePath("interface/interface_1"));

  // Loading Buildings
  QJsonArray json_buildings = json_object["buildings"].toArray();
  int buildings_count = json_buildings.count();
  id_to_building_.clear();
  id_to_building_.reserve(buildings_count);
  upgrades_tree_.clear();
  upgrades_tree_.reserve(buildings_count);
  QJsonObject json_building;
  for (int i = 0; i < buildings_count; i++) {
    json_building = json_buildings[i].toObject();
    AuricField aura;
    if (json_building.contains("auric_field")) {
      aura = AuricField(
          json_building["auric_field"].toObject()["radius"].toInt(),
          json_building["auric_field"].toObject()["effect_id"].toInt());
    }

    Building building(i, json_building["settle_cost"].toInt(), aura);
    if (json_building.contains("projectile")) {
      auto json_projectile = json_building["projectile"].toObject();
      building.SetProjectile(json_projectile["projectile_id"].toInt(),
                             json_projectile["attack_damage"].toDouble(),
                             json_projectile["attack_range"].toInt(),
                             json_projectile["max_aims"].toInt());
    }
    auto json_timings = json_building["action_time"].toArray();
    auto json_paths = json_building["animation_path"].toArray();
    SetAnimationToGameObject(&building, {
        json_timings[0].toInt(),
        json_timings[1].toInt(),
        json_timings[2].toInt()}, {
                                 json_paths[0].toString(),
                                 json_paths[1].toString(),
                                 json_paths[2].toString()});

    auto json_upgrade_tree = json_building["upgrade_tree"].toArray();
    int upgrade_tree_count = json_upgrade_tree.size();
    std::vector<int> upgrade_tree;
    upgrade_tree.reserve(upgrade_tree_count);
    for (int j = 0; j < upgrade_tree_count; j++) {
      upgrade_tree.push_back(json_upgrade_tree[j].toInt());
    }
    building.SetInfo(json_building["header"].toString(),
                     json_building["description"].toString());
    upgrades_tree_.push_back(std::move(upgrade_tree));
    id_to_building_.push_back(std::move(building));
    SetParticlesToGameObject(&id_to_building_.back(),
                             json_building["particles"].toObject());
  }


  // Loading Projectiles
  QJsonArray json_projectiles = json_object["projectiles"].toArray();
  int projectiles_count = json_projectiles.count();
  id_to_projectile_.clear();
  id_to_projectile_.reserve(projectiles_count);
  QJsonObject json_projectile;
  for (int i = 0; i < projectiles_count; i++) {
    json_projectile = json_projectiles[i].toObject();
    auto json_size = json_projectile["size"].toObject();
    Size size(json_size["width"].toDouble(), json_size["height"].toDouble());
    int type = json_projectile["type"].toInt();

    switch (type) {
      case 0: {
        double speed = json_projectile["speed"].toDouble();
        HomingProjectile projectile(size, speed);
        id_to_projectile_.push_back(
            std::make_shared<HomingProjectile>(projectile));
        break;
      }
      case 1: {
        double speed = json_projectile["speed"].toDouble();
        double effect_radius = json_projectile["effect_radius"].toDouble();
        double up_force = json_projectile["up_force"].toDouble();
        BombProjectile projectile(size, speed, effect_radius, up_force);
        id_to_projectile_.push_back(
            std::make_shared<BombProjectile>(projectile));
        break;
      }
      case 2: {
        LaserProjectile projectile(size);
        id_to_projectile_.push_back(
            std::make_shared<LaserProjectile>(projectile));
        break;
      }
      default:break;
    }
    auto json_animation = json_projectile["animation"].toObject();
    SetAnimationToGameObject(
        id_to_projectile_.back().get(),
        {json_animation["timing"].toInt()},
        {json_animation["path"].toString()});
    SetParticlesToGameObject(id_to_projectile_.back().get(),
                             json_projectile["particles"].toObject());
  }

  // Loading Particles
  QJsonArray json_particles = json_object["particles"].toArray();
  int particles_count = json_particles.count();
  id_to_particle_.clear();
  id_to_particle_.reserve(particles_count);
  QJsonObject json_particle;
  for (int i = 0; i < particles_count; i++) {
    json_particle = json_particles[i].toObject();
    Size size = {-1, -1};
    if (json_particle.contains("size")) {
      auto json_size = json_particle["size"].toObject();
      size =
          Size(json_size["width"].toDouble(), json_size["height"].toDouble());
    }
    int repeat_number = -1;
    if (json_particle.contains("repeat_number")) {
      repeat_number = json_particle["repeat_number"].toInt();
    }
    id_to_particle_.emplace_back(size, repeat_number);
    auto json_animation = json_particle["animation"].toObject();
    SetAnimationToGameObject(
        &id_to_particle_.back(),
        {json_animation["timing"].toInt()},
        {json_animation["path"].toString()});
  }

  // backgrounds
  backgrounds_.emplace_back(
      GetImagesByFramePath("backgrounds/main_background_1"));
  backgrounds_.emplace_back(
      GetImagesByFramePath("backgrounds/settings_background_1"));
  backgrounds_.emplace_back(
      GetImagesByFramePath("backgrounds/pause_menu_background_1"));
  backgrounds_.emplace_back(GetImagesByFramePath("error"));

  // Effects
  std::vector<EffectVisualization> effect_visualization =
      {{GetImagesByFramePath("icons/slow_1"),
        GetImagesByFramePath("icons/fast_1")},
       {GetImagesByFramePath("icons/less_armor_1"),
        GetImagesByFramePath("icons/more_armor_1")},
       {GetImagesByFramePath("icons/less_damage_1"),
        GetImagesByFramePath("icons/more_damage_1")},
       {GetImagesByFramePath("icons/slow_attack_1"),
        GetImagesByFramePath("icons/fast_attack_1")},
       {GetImagesByFramePath("icons/less_range_1"),
        GetImagesByFramePath("icons/more_range_1")},
      };

  Effect::SetEffectVisualizations(effect_visualization);

  // Load fonts
  QFontDatabase::addApplicationFont(":resources/fonts/gui_font.ttf");
  QFontDatabase::addApplicationFont(":resources/fonts/comics.ttf");

  // Empty zone
  empty_zone_texture_.push_back(
      QImage(":resources/images/backgrounds/cloud.png"));
  empty_zone_texture_.push_back(
      QImage(":resources/images/backgrounds/cloud.png"));
  empty_zone_texture_.push_back(
      QImage(":resources/images/backgrounds/cloud.png"));
  empty_zone_texture_.push_back(
      QImage(":resources/images/backgrounds/cloud.png"));
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

void Model::SetParticlesToGameObject(GameObject* p_enemy, QJsonObject object) {
  int at_creation = -1;
  int at_death = -1;
  if (object.contains("at_death")) {
    at_death = object["at_death"].toInt();
  }
  if (object.contains("at_creation")) {
    at_creation = object["at_creation"].toInt();
  }
  // for example, if there is no parameter, you leave the default value
  // that is valid for you
  int while_alive = -1;
  int period = 0;

  if (object.contains("while_alive")) {
    while_alive = object["while_alive"].toInt();
    period = object["period"].toInt();
  }
  p_enemy->GetParticleHandler()->SetEvents({at_creation, at_death, while_alive},
                                           period);
}
