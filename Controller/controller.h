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

  void Tick(int current_time) override;
  void StartGame(int level) override;
  void EndGame(Exit exit) override;

  void MousePress(Coordinate position) override;
  void MouseMove(Coordinate position) override;

  const std::list<std::shared_ptr<Enemy>>& GetEnemies() const override;
  const std::vector<Road>& GetRoads() const override;
  const std::vector<std::shared_ptr<Building>>& GetBuildings() const override;

 private:
  std::unique_ptr<Model> model_;
  std::unique_ptr<View> view_;

  WindowType game_mode_ = WindowType::kMainMenu;
  bool has_unprocessed_rounds_ = true;
  int current_time_ = 0;
  int last_round_start_time_ = 0;

 private:
  void GameProcess();
  void MenuProcess();

  void CreateNextWave();
  bool CanCreateNextWave();
  void CreateEnemy(const Enemy& enemy) const;
  void TickSpawners();
  void TickEnemies();

  void CreateTowerMenu(int tower_to_process);

  // Upgrades or evolves the building
  void SetBuilding(int index_in_buildings, int replacing_id);
};

#endif  // CONTROLLER_CONTROLLER_H_
