#ifndef MODEL_MODEL_H_
#define MODEL_MODEL_H_

#include <iostream>
#include <list>
#include <memory>
#include <utility>
#include <vector>

#include <QCoreApplication>
#include <QDir>
#include <QSettings>
#include <QString>
#include <QSoundEffect>
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
#include "sound_vector.h"
#include "View/text_notification.h"
#include "View/tower_menu.h"

class Model {
 public:
  Model() = default;
  ~Model();
  void LoadDatabase();

  void SetGameLevel(int level);
  void AddSpawner(const EnemyGroup& enemy_group);
  void AddTextNotification(const TextNotification& text_notification);
  void AddEnemyFromInstance(const Enemy& enemy_instance,
                            bool position_copy = false);
  void CreateBuildingAtIndex(int i, int id);
  void CreateProjectile(const std::shared_ptr<Enemy>& aim,
                        const Building& building);
  void CreateParticles(const std::list<ParticleParameters>& parameters);
  void RescaleDatabase(const SizeHandler& size_handler);
  void IncreaseCurrentRoundNumber();
  void ClearGameModel();
  void SetParticlesVolume(int volume);

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
  int GetPreparedTimeBetweenRounds() const;
  int GetCurrentRoundNumber() const;

  const AnimationPlayer& GetBackGround(int back_ground_id) const;
  const AnimationPlayer& GetInterface() const;

  const QPixmap& GetEmptyZoneTexture(int index) const;
  const std::vector<QString>& GetTitles() const;

 private:
  void LoadLevel(int level);
  void InitializeTowerSlots();

  void SetAnimationToGameObject(GameObject* object,
                                const std::vector<int>& timings,
                                const std::vector<QString>& paths);
  std::shared_ptr<std::vector<QPixmap>> GetImagesByFramePath(
      const QString& path, const QString& picture_type = ".png") const;
  void SetParticlesToGameObject(GameObject* p_enemy, QJsonObject object);
  void LoadEffects(const QJsonObject& json_object);
  void LoadEnemies(const QJsonObject& json_object);
  void LoadBackground(const QJsonObject& json_object);
  void LoadBuildings(const QJsonObject& json_object);
  void LoadProjectiles(const QJsonObject& json_object);
  void LoadParticles(const QJsonObject& json_object);

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
  std::vector<QString> titles_;

  std::vector<Coordinate> empty_places_for_towers_;
  int prepared_time_between_rounds_ = 0;
  int rounds_count_ = 0;

  // Database of GameObject's instances, that is used to create GameObjects.
  std::vector<Enemy> id_to_enemy_;
  std::vector<std::shared_ptr<AbstractProjectile>> id_to_projectile_;
  std::vector<Building> id_to_building_;
  std::vector<std::vector<int>> upgrades_tree_;
  std::vector<Effect> id_to_effect_;
  std::vector<Particle> id_to_particle_;
  std::vector<SoundVector> id_to_particle_sound_;

  // Images
  std::vector<QPixmap> empty_zone_texture_;
  std::vector<AnimationPlayer> backgrounds_;
  AnimationPlayer interface_;
};

#endif  // MODEL_MODEL_H_
