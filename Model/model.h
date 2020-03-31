#ifndef MODEL_MODEL_H_
#define MODEL_MODEL_H_

#include <list>
#include <vector>
#include <memory>

#include <QDebug>

#include "GameObject/enemy.h"
#include "GameObject/building.h"
#include "GameObject/projectile.h"

#include "Controller/spawner.h"
#include <GameObject/default_tower.h>
#include <GameObject/multi_tower.h>
#include "wave.h"
#include "road.h"

class Model {
 public:
  Model() = default;
  ~Model() = default;

  void SetGameModel(int level);
  void ClearGameModel();

  void AddSpawner(const Wave& wave, int current_time);
  void AddEnemyFromInstance(const Enemy& enemy_instance);

  void IncreaseCurrentRoundNumber();

  int GetTimeBetweenWaves() const;
  int GetRoundsCount() const;
  int GetWavesCount(int round_number) const;
  int GetCurrentRoundNumber() const;
  std::list<Spawner>* GetSpawners();
  std::list<std::shared_ptr<Enemy>>* GetEnemies();
  const Wave& GetWave(int round_number, int road_number) const;
  const Road& GetRoad(int i) const;
  const std::vector<Road>& GetRoads() const;

  const std::vector<Coordinate>& GetTowerSlots() const;
  const std::vector<std::shared_ptr<Building>>& GetBuildings() const;
  const std::vector<std::vector<int>>& GetBuildingsTree() const;
  std::shared_ptr<Building> GetBuildingById(int id) const;

  void SetBuildingAtIndex(int i, int id);
  void UpgradeBuildingAtIndex(int i);

 private:
  // Database which is updated by Controller all time
  std::list<std::shared_ptr<Projectile>> projectiles_;
  std::vector<std::shared_ptr<Building>> buildings_;
  std::list<std::shared_ptr<Enemy>> enemies_;
  int current_round_number_;
  int gold_;
  int score_;

  // Database which is loaded in SetGameModel once
  std::vector<std::vector<Wave>> rounds_;
  std::vector<Road> roads_;
  std::list<Spawner> spawners_;
  std::vector<Coordinate> empty_towers_;

  int time_between_rounds_;
  int rounds_count_;
  int roads_count_;

  // Database of GameObject's instances, that is used to create GameObjects.
  std::vector<Enemy> id_to_enemy_;
  int building_count_;
  std::vector<std::shared_ptr<Building>> id_to_building_;
  // buildings_tree[i] is a vector of towers to which
  // ith tower can be evolved or changed
  std::vector<std::vector<int>> buildings_tree_;

 private:
  // Helping functions

  // Creates EmptyTower classes from empty_towers_ vector
  // Should be called on load of empty_towers_
  void InitialiseTowerSlots();
};

#endif  // MODEL_MODEL_H_
