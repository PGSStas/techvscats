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
#include <QSettings>
#include <QString>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

#include "Controller/spawner.h"
#include "GameObject/abstract_projectile.h"
#include "GameObject/homing_projectile.h"
#include "GameObject/base.h"
#include "GameObject/bomb_projectile.h"
#include "GameObject/building.h"
#include "GameObject/effect.h"
#include "GameObject/enemy.h"
#include "GameObject/laser_projectile.h"
#include "GameObject/particle.h"
#include "enemy_group.h"
#include "road.h"
#include "View/text_notification.h"
#include "View/tower_menu.h"

class Model {
 public:
  Model();

  void SetGameLevel(int level);
  void AddSpawner(const EnemyGroup& enemy_group);
  void AddTextNotification(const TextNotification& text_notification);
  void AddEnemyFromInstance(const Enemy& enemy_instance);
  void CreateBuildingAtIndex(int i, int id);
  void CreateProjectile(const std::shared_ptr<Enemy>& aim,
                        const Building& building);
  void CreateParticles(const std::list<ParticleParameters>& parameters);
  void RescaleDatabase(const SizeHandler& size_handler);
  void IncreaseCurrentRoundNumber();
  void ClearGameModel();

  Base* GetBase();
  std::list<Spawner>* GetSpawners();
  std::list<Particle>* GetParticles();
  std::list<std::shared_ptr<Enemy>>* GetEnemies();
  std::list<std::shared_ptr<AbstractProjectile>>* GetProjectiles();
  std::list<TextNotification>* GetTextNotifications();

  const std::vector<EnemyGroup>& GetEnemyGroupsPerRound(int i) const;
  const std::vector<std::vector<int>>& GetUpgradesTree() const;
  const std::vector<std::shared_ptr<Building>>& GetBuildings() const;

  const Road& GetRoad(int i) const;
  const Enemy& GetEnemyById(int id) const;
  const Effect& GetEffectById(int id) const;
  const Building& GetBuildingById(int id) const;

  int GetRoundsCount() const;
  int GetPrepairTimeBetweenRounds() const;
  int GetCurrentRoundNumber() const;

  const AnimationPlayer& GetBackGround(int back_ground_id) const;
  const AnimationPlayer& GetInterface() const;

  const QImage& GetEmptyZoneTexture(int index) const;

 private:
  void LoadLevel(int level);
  void LoadDatabase();
  void InitializeTowerSlots();
  void SetAnimationToGameObject(
      GameObject* object, std::vector<int> timmings,
      std::vector<QString> paths);
  std::shared_ptr<std::vector<QImage>> GetImagesByFramePath(
      QString path, QString picture_type = ".png") const;
  void SetParticlesToGameObject(GameObject* p_enemy, QJsonObject object);

  // Database which is updated by Controller all time
  std::list<Spawner> spawners_;
  std::list<Particle> particles_;
  std::list<std::shared_ptr<Enemy>> enemies_;
  std::vector<std::shared_ptr<Building>> buildings_;
  std::list<std::shared_ptr<AbstractProjectile>> projectiles_;
  std::list<TextNotification> text_notifications_;

  int current_round_number_ = 0;

  // Database which is loaded in SetGameLevel once
  std::vector<Road> roads_;
  std::vector<std::vector<EnemyGroup>> enemy_groups_;
  std::shared_ptr<Base> base_;

  std::vector<Coordinate> empty_places_for_towers_;
  int prepair_time_between_rounds_ = 0;
  int rounds_count_ = 0;

  // Database of GameObject's instances, that is used to create GameObjects.
  std::vector<Enemy> id_to_enemy_;
  std::vector<std::shared_ptr<AbstractProjectile>> id_to_projectile_;
  std::vector<Building> id_to_building_;
  std::vector<std::vector<int>> upgrades_tree_;
  std::vector<Effect> id_to_effect_;
  std::vector<Particle> id_to_particle_;

  // Images

  std::vector<QImage> empty_zone_texture_;
  std::vector<AnimationPlayer> backgrounds_;
  AnimationPlayer interface_;
};

#endif  // MODEL_MODEL_H_
