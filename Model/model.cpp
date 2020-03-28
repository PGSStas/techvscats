#include "model.h"

void Model::SetGameModel() {
  LoadDatabaseFromJson();
}

void Model::SetGameLevel(int level_id) {
  Enemy temporary_enemy;
  temporary_enemy.SetParametres(1);
  id_to_enemy_.push_back(temporary_enemy);
  temporary_enemy.SetParametres(4);
  id_to_enemy_.push_back(temporary_enemy);
  switch (level_id) {
    case 1:
      LoadLevelFromJson(1);
      break;
    default:
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
  return id_to_enemy_.at(id);
}

const std::vector<EnemyGroup>& Model::GetRound(int i) const {
  return rounds_.at(i);
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

void Model::LoadLevelFromJson(int level) {
  QDir level_directory = QCoreApplication::applicationDirPath();
  level_directory.cd("../Model/bin/levels");
  qDebug() << level_directory.path();

  QFile level_file(level_directory.path() +
      "/level_" + QString::number(level) + ".json");
  if (!level_file.open(QFile::ReadOnly)) {
    qDebug() << "ERROR! Missing level file";
    return;
  }
  QJsonObject json_object =
      QJsonDocument::fromJson(level_file.readAll()).object();

  if (json_object.contains("time_between_rounds")) {
    time_between_ronds_ = json_object["time_between_rounds"].toInt();
  }
  if (json_object.contains("gold")) {
    gold_ = json_object["gold"].toInt();
  }
  if (json_object.contains("score")) {
    score_ = json_object["score"].toInt();
  }

  if (json_object.contains("roads")) {
    QJsonArray json_roads = json_object["roads"].toArray();
    QJsonArray json_road_nodes;
    QJsonObject json_node;

    roads_count_ = json_roads.size();
    roads_.clear();
    roads_.reserve(roads_count_);
    for (int i = 0; i < roads_count_; i++) {
      json_road_nodes = json_roads[i].toObject()["road"].toArray();

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
  }

  if (json_object.contains("rounds")) {
    QJsonArray json_rounds = json_object["rounds"].toArray();
    QJsonArray json_enemy_groups;
    QJsonObject json_enemy_group;

    rounds_count_ = json_rounds.size();
    rounds_.clear();
    rounds_.reserve(rounds_count_);
    for (int i = 0; i < rounds_count_; i++) {
      json_enemy_groups = json_rounds[i].toObject()["round"].toArray();

      int group_count = json_enemy_groups.size();
      std::vector<EnemyGroup> groups;
      groups.reserve(group_count);
      for (int j = 0; j < group_count; j++) {
        json_enemy_group = json_enemy_groups[j].toObject();
        groups.emplace_back(json_enemy_group["spawn_frequency"].toInt(),
                            json_enemy_group["enemy_id"].toInt(),
                            json_enemy_group["time_of_next_spawn"].toInt(),
                            json_enemy_group["group_size"].toInt(),
                            json_enemy_group["road_to_spawn"].toInt());
      }
      rounds_.push_back(std::move(groups));
    }
  }
}

void Model::LoadDatabaseFromJson() {
  QDir level_directory = QCoreApplication::applicationDirPath();
  level_directory.cd("../Model/bin/database");
  qDebug() << level_directory.path();

  QFile level_file(level_directory.path() + "/database.json");
  if (!level_file.open(QFile::ReadOnly)) {
    qDebug() << "ERROR! Missing database file";
    return;
  }
  // TODO(PGSStas) Parser from json, after buildings and enemies will be written
  // QJsonDocument document(QJsonDocument::fromJson(level_file.readAll()));
  //
  // QJsonObject json_object = document.object();
  // if (json_object.contains("enemies")) {
  //   QJsonArray enemies = json_object["enemies"].toArray();
  //   QJsonObject enemy;
  //
  //   int n = enemies.size();
  //   std::vector<Enemy> enemies_instances;
  //   enemies_instances.reserve(n);
  //   for (int i = 0; i < n; i++) {
  //     enemy = enemies[i].toObject();
  //
  //
  //   }
  // }
}
