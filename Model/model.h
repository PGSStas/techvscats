#ifndef MODEL_MODEL_H_
#define MODEL_MODEL_H_

#include <cassert>
#include <iostream>
#include <list>
#include <memory>
#include <utility>
#include <vector>

#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

#include "GameObject/enemy.h"
#include "GameObject/building.h"
#include "GameObject/projectile.h"

#include "Controller/spawner.h"
#include "enemy_group.h"
#include "road.h"

class Model {
 public:
  Model() = default;
  ~Model() = default;

  void SetGameLevel(int level);
  void ClearGameModel();

  void AddSpawner(const EnemyGroup& enemy_group);
  void AddEnemyFromInstance(const Enemy& enemy_instance);
  int GetTimeBetweenWaves() const;
  int GetRoundsCount() const;
  int GetRoadsCount() const;
  int GetCurrentRoundNumber() const;
  void IncreaseCurrentRoundNumber();
  std::list<Spawner>* GetSpawners();
  std::list<std::shared_ptr<Enemy>>* GetEnemies();
  Enemy GetEnemyById(int id) const;
  const std::vector<EnemyGroup>& GetEnemyGroupsPerRound(int i) const;
  const Road& GetRoad(int i) const;
  const std::vector<Road>& GetRoads() const;

 private:
  void LoadLevelFromJson(int level);

  // Database which is updated by Controller all time
  std::list<std::shared_ptr<Projectile>> projectiles_;
  std::list<std::shared_ptr<Building>> buildings_;
  std::list<std::shared_ptr<Enemy>> enemies_;
  int current_round_number_;
  int gold_;
  int score_;

  // Database which is loaded in SetGameLevel once
  std::vector<std::vector<EnemyGroup>> enemy_groups_;
  std::vector<Road> roads_;
  std::list<Spawner> spawners_;
  int time_between_ronds_;
  int rounds_count_;
  int roads_count_;

  // Database of GameObject's instances, that is used to create GameObjects.
  std::vector<Enemy> id_to_enemy_;
  std::vector<Building> id_to_building_;
};

#endif  // MODEL_MODEL_H_
