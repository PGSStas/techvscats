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
#include "GameObject/lazer_projectile.h"
#include "GameObject/aimed_projectile.h"
#include "GameObject/bomb_projectile.h"
#include "GameObject/base.h"
#include "GameObject/building.h"
#include "GameObject/abstract_projectile.h"
#include "GameObject/effect.h"

#include "Controller/spawner.h"
#include "enemy_group.h"
#include "road.h"

class Model {
 public:
  Model();

  void SetGameLevel(int level);
  void ClearGameModel();

  void AddSpawner(const EnemyGroup& enemy_group);
  void AddEnemyFromInstance(const Enemy& enemy_instance);

  void IncreaseCurrentRoundNumber();

  int GetTimeBetweenWaves() const;
  int GetRoundsCount() const;
  int GetCurrentRoundNumber() const;

  std::list<Spawner>* GetSpawners();
  std::list<std::shared_ptr<Enemy>>* GetEnemies();
  Base* GetBase();
  const Enemy& GetEnemyById(int id) const;
  const Effect& GetEffectById(int id) const;
  std::list<std::shared_ptr<AbstractProjectile>>* GetProjectiles();
  const std::vector<std::shared_ptr<Building>>& GetBuildings();

  const Building& GetBuildingById(int id) const;

  const std::vector<EnemyGroup>& GetEnemyGroupsPerRound(int i) const;

  const Road& GetRoad(int i) const;
  const std::vector<Road>& GetRoads() const;

  void CreateProjectile(const Building& building,
                        const std::shared_ptr<Enemy>& aim);
  const std::vector<std::vector<int>>& GetUpgradesTree() const;

  void SetBuildingAtIndex(int i, int id);

 private:
  void LoadLevelFromJson(int level);
  void LoadDatabaseFromJson();

  // Database which is updated by Controller all time
  std::list<std::shared_ptr<AbstractProjectile>> projectiles_;
  std::vector<std::shared_ptr<Building>> buildings_;
  std::list<std::shared_ptr<Enemy>> enemies_;
  int current_round_number_ = 0;
  int gold_ = 0;
  int score_ = 0;

  // Database which is loaded in SetGameLevel once
  Base base_ = Base(0, {0, 0});
  std::vector<std::vector<EnemyGroup>> enemy_groups_;
  std::vector<Road> roads_;
  std::list<Spawner> spawners_;
  std::vector<Coordinate> empty_places_for_towers_;
  int time_between_rounds_ = 0;
  int rounds_count_ = 0;
  int roads_count_ = 0;

  // Database of GameObject's instances, that is used to create GameObjects.
  std::vector<Enemy> id_to_enemy_;
  std::vector<std::shared_ptr<AbstractProjectile>> id_to_projectile_;
  int building_count_;
  std::vector<Effect> id_to_effect_;
  std::vector<Building> id_to_building_;
  // upgrades_tree[i] is a vector of towers to which
  // ith tower can be evolved or changed
  std::vector<std::vector<int>> upgrades_tree_;

 private:
  // Helping functions

  // Creates EmptyTower classes from empty_places_for_towers_ vector
  // Should be called on load of empty_places_for_towers_
  void InitializeTowerSlots();
};

#endif  // MODEL_MODEL_H_
