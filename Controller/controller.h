#ifndef CONTROLLER_CONTROLLER_H_
#define CONTROLLER_CONTROLLER_H_

#include <list>
#include <vector>
#include <memory>

#include "abstract_controller.h"
#include "View/view.h"
#include "Model/model.h"

// This class controls the interaction between objects.
class Controller : public AbstractController {
 public:
  Controller();
  ~Controller() override = default;

  void StartGame(int level) override;
  void EndGame(Exit exit) override;
  void Tick(int current_time) override;
  void SetSpeedCoefficient(Speed speed) override;

  void MousePress(Coordinate position) override;
  void MouseMove(Coordinate position) override;
  void RescaleObjects(const SizeHandler& size_handler) override;

   const std::list<Particle>& GetParticles() const override;
  const std::list<std::shared_ptr<Enemy>>& GetEnemies() const override;
  const std::vector<std::shared_ptr<Building>>& GetBuildings() const override;

  const std::list<std::shared_ptr<AbstractProjectile>>&
    GetProjectiles() const override;
  const std::list<TextNotification>& GetTextNotifications() const override;

  const Base& GetBase() const override;
  int GetCurrentTime() const override;

  const AnimationPlayer& GetBackground(WindowType type) const override;

 private:
  std::unique_ptr<Model> model_;
  std::unique_ptr<View> view_;

  WindowType game_mode_;
  bool has_unprocessed_rounds_ = false;
  bool is_prepairing_to_spawn_ = false;
  int current_game_time_ = 0;
  int last_round_start_time_ = 0;

 private:
  void GameProcess();
  void MenuProcess();

  bool CanCreateNextWave();
  void CreateNextWave();
  void TickSpawners();
  void TickParticlesHandlers();
  void TickParticlesHandler(ParticleHandler* particle_handler);
  void TickParticles();
  void TickEnemies();
  void TickBuildings();
  void TickProjectiles();
  void TickAuras();
  void TickTextNotifications();

  void ApplyEffectToAllInstances(const AuricField& aura);
  void AddEnemyToModel(const Enemy& enemy) const;

  void SetBuilding(int index_in_buildings, int replacing_id);
  void CreateTowerMenu(int tower_index);
  void ProcessEnemyDeath(const Enemy& enemy) const;
};

#endif  // CONTROLLER_CONTROLLER_H_
