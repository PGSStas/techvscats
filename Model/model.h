#ifndef MODEL_MODEL_H_
#define MODEL_MODEL_H_

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
#include "GameObject/base.h"
#include "GameObject/building.h"
#include "GameObject/projectile.h"
#include "GameObject/effect.h"

#include "Controller/spawner.h"
#include "enemy_group.h"
#include "road.h"

class Model {
 public:
  Model();
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
  std::list<std::shared_ptr<Building>>* GetBuildings();
  Enemy GetEnemyById(int id) const;
  const Effect& GetEffectById(int id) const;
  const std::vector<EnemyGroup>& GetEnemyGroupsPerRound(int i) const;
  const Road& GetRoad(int i) const;
  const std::vector<Road>& GetRoads() const;
  std::shared_ptr<Base> GetBase() const;

 private:
  void LoadLevelFromJson(int level);
  void LoadDatabaseFromJson();

  // Database which is updated by Controller all time
  std::list<std::shared_ptr<Projectile>> projectiles_;
  std::list<std::shared_ptr<Building>> buildings_;
  std::list<std::shared_ptr<Enemy>> enemies_;
  int current_round_number_ = 0;
  int gold_ = 0;
  int score_ = 0;

  // Database which is loaded in SetGameLevel once
  std::shared_ptr<Base> base_;
  std::vector<std::vector<EnemyGroup>> enemy_groups_;
  std::vector<Road> roads_;
  std::list<Spawner> spawners_;
  int time_between_rounds_ = 0;
  int rounds_count_ = 0;
  int roads_count_ = 0;

  // Database of GameObject's instances, that is used to create GameObjects.
  std::vector<Enemy> id_to_enemy_;
  std::vector<Effect> id_to_effect_;
  std::vector<Building> id_to_building_;
};

#endif  // MODEL_MODEL_H_
