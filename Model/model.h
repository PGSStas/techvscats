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

#include "Controller/spawner.h"
#include "GameObject/abstract_projectile.h"
#include "GameObject/aimed_projectile.h"
#include "GameObject/base.h"
#include "GameObject/bomb_projectile.h"
#include "GameObject/building.h"
#include "GameObject/effect.h"
#include "GameObject/enemy.h"
#include "GameObject/lazer_projectile.h"
#include "enemy_group.h"
#include "road.h"

class Model {
 public:
  Model();

  void SetGameLevel(int level);
  void AddSpawner(const EnemyGroup& enemy_group);
  void AddEnemyFromInstance(const Enemy& enemy_instance);
  void CreateBuildingAtIndex(int i, int id);
  void CreateProjectile(const std::shared_ptr<Enemy>& aim,
                        const Building& building);
  void IncreaseCurrentRoundNumber();
  void ClearGameModel();

  Base* GetBase();
  std::list<Spawner>* GetSpawners();
  std::list<std::shared_ptr<Enemy>>* GetEnemies();
  std::list<std::shared_ptr<AbstractProjectile>>* GetProjectiles();

  const std::vector<Road>& GetRoads() const;
  const std::vector<EnemyGroup>& GetEnemyGroupsPerRound(int i) const;
  const std::vector<std::vector<int>>& GetUpgradesTree() const;
  const std::vector<std::shared_ptr<Building>>& GetBuildings() const;

  const Road& GetRoad(int i) const;
  const Enemy& GetEnemyById(int id) const;
  const Effect& GetEffectById(int id) const;
  const Building& GetBuildingById(int id) const;

  int GetRoundsCount() const;
  int GetTimeBetweenWaves() const;
  int GetCurrentRoundNumber() const;

 private:
  void LoadLevelFromJson(int level);
  void LoadDatabaseFromJson();
  void InitializeTowerSlots();

  // Database which is updated by Controller all time
  std::list<Spawner> spawners_;
  std::list<std::shared_ptr<Enemy>> enemies_;
  std::vector<std::shared_ptr<Building>> buildings_;
  std::list<std::shared_ptr<AbstractProjectile>> projectiles_;
  int current_round_number_ = 0;
  int gold_ = 0;
  int score_ = 0;

  // Database which is loaded in SetGameLevel once
  std::vector<Road> roads_;
  std::vector<std::vector<EnemyGroup>> enemy_groups_;
  Base base_ = Base(0, {0, 0});
  std::vector<Coordinate> empty_places_for_towers_;
  int time_between_rounds_ = 0;
  int rounds_count_ = 0;

  // Database of GameObject's instances, that is used to create GameObjects.
  std::vector<Enemy> id_to_enemy_;
  std::vector<std::shared_ptr<AbstractProjectile>> id_to_projectile_;
  std::vector<Building> id_to_building_;
  std::vector<std::vector<int>> upgrades_tree_;
  std::vector<Effect> id_to_effect_;
};

#endif  // MODEL_MODEL_H_
