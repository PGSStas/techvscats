#ifndef MODEL_MODEL_H_
#define MODEL_MODEL_H_

#include <list>
#include <vector>
#include <memory>

#include <QDebug>

#include "GameObject/enemy.h"
#include "GameObject/active_tower.h"
#include "GameObject/projectile.h"

#include "Controller/spawner.h"
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
  std::vector<std::shared_ptr<Building>>* GetBuildings();
  std::list<std::shared_ptr<Projectile>>* GetProjectiles();

  const Wave& GetWave(int round_number, int road_number) const;
  const Road& GetRoad(int i) const;
  const std::vector<Road>& GetRoads() const;

  const std::vector<std::vector<int>>& GetBuildingsTree() const;
  std::shared_ptr<Building> GetBuildingById(int id);
    std::shared_ptr<Projectile> GetProjectileById(int id);
  int GetBuildingCount();
  void SetBuildingAt(int i, int id);
  void CreateProjectiles(std::vector<std::shared_ptr<Projectile>> projectiles);
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
  std::vector<std::shared_ptr<Enemy>> id_to_enemy_;
  std::vector<std::shared_ptr<Projectile>> id_to_projectile_;
  int building_count_;
  std::vector<std::shared_ptr<Building>> id_to_building_;
  std::vector<std::vector<int>> buildings_tree_;

 private:
  // Helping functions
  void InitialiseTowerSlots();
};

#endif  // MODEL_MODEL_H_
