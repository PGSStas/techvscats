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
#include <GameObject/empty_tower.h>
#include <GameObject/fast_tower.h>
#include <GameObject/slow_tower.h>
#include "wave.h"
#include "road.h"

class Model {
 public:
  Model() = default;
  ~Model() = default;

  void SetGameModel(int level);
  void ClearGameModel();

  void AddSpawner(int road_number, const Wave& wave, int current_time);
  void AddEnemyFromInstance(const Enemy& enemy_instance);

  void IncreaseCurrentRoundNumber();

  int GetTimeBetweenWaves() const;
  int GetRoundsCount() const;
  int GetRoadsCount() const;
  int GetCurrentRoundNumber() const;
  std::list<Spawner>* GetSpawners();
  std::list<std::shared_ptr<Enemy>>* GetEnemies();
  const Wave& GetWave(int round_number, int road_number) const;
  const Road& GetRoad(int i) const;
  const std::vector<Road>& GetRoads() const;

  const std::vector<Coordinate>& GetTowerSlots() const;
  const std::vector<std::shared_ptr<Building>>& GetBuildings() const;

  std::shared_ptr<Building> GetBuildingById(int id);
  int GetBuildingCount();
  void SetBuildingAt(int i, int id);
  void UpgradeBuildingAt(int i);

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

 private:
  // Helping functions

  // Creates EmptyTower classes from empty_towers_ vector
  // Should be called on load of empty_towers_
  void InitialiseTowerSlots();
};

#endif  // MODEL_MODEL_H_
