#ifndef CONTROLLER_CONTROLLER_H_
#define CONTROLLER_CONTROLLER_H_

#include <algorithm>
#include <list>
#include <vector>
#include <memory>
#include <QObject>

#include "abstract_controller.h"
#include "View/view.h"
#include "Model/model.h"

// This class controls the interaction between objects.
class Controller : public AbstractController {
 public:
  Controller();
  ~Controller() override = default;

  void SecondConstructorPart() override;

  void StartGame(int level) override;
  void EndGame() override;
  void Tick(int current_time) override;
  void SetSpeedCoefficient(Speed speed) override;
  void SetBuilding(int index_in_buildings, int replacing_id) override;

  void MouseEvent(Coordinate position, bool is_press) override;
  void RescaleObjects(const SizeHandler& size_handler) override;

  const Building& GetBuildingById(int instance_id) const override;
  const std::list<Particle>& GetParticles() const override;
  const std::list<std::shared_ptr<Enemy>>& GetEnemies() const override;
  const std::vector<std::shared_ptr<Building>>& GetBuildings() const override;
  const std::list<std::shared_ptr<AbstractProjectile>>&
  GetProjectiles() const override;
  const std::list<TextNotification>& GetTextNotifications() const override;

  const Base& GetBase() const override;
  int GetCurrentTime() const override;
  GameStatus GetCurrentStatus() const override;

  const AnimationPlayer& GetBackground(WindowType type) const override;

  const QImage& GetEmptyZoneTexture(WindowType type) const override;
  const AnimationPlayer& GetInterface() const override;

  int GetCurrentRoundNumber() const override;
  int GetRoundsCount() const override;
  void SetGameVolume(int volume) override;
  MultiplayerClient* GetClient() override;

  void CreateTitles() override;
  void EndTitles() override;

  MusicPlayer* GetMusicPlayer() override;

 private:
  std::unique_ptr<View> view_;
  std::unique_ptr<Model> model_;
  MusicPlayer music_player_;
  MultiplayerClient client_;

  GameStatus game_status_ = GameStatus::kPlay;
  WindowType window_type_ = WindowType::kMainMenu;
  bool is_preparing_to_spawn_ = false;
  int current_game_time_ = 0;
  int last_round_start_time_ = 0;

  const int kWinParticleId = 7;
  const int kLooseParticleId = 1;
  const int kParticlesPeriod = 100;
  int last_time_end_particle_created = 0;

  static std::mt19937 random_generator_;

  const int kTitlesSize = 40;
  const int kTitlesDuration = 84000;

 private:
  void GameProcess();

  bool CanCreateNextWave();
  void CreateNextWave();
  void TickClient();
  void TickEndGame();
  void TickSpawners();
  void TickParticleHandlers();
  void TickParticleHandler(ParticleHandler* particle_handler);
  void TickParticles();
  void TickEnemies();
  void TickBuildings();
  void TickProjectiles();
  void TickAuras();
  void TickTextNotifications();

  void ApplyEffectToAllInstances(const AuricField& aura);
  void AddEnemyToModel(const Enemy& enemy) const;

  void CreateTowerMenu(int tower_index);
  void ProcessEnemyDeath(const Enemy& enemy) const;
  void ProcessMessage(const Message& message);
  void ProcessCommand(const Message& message);
};

#endif  // CONTROLLER_CONTROLLER_H_
