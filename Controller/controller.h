#ifndef CONTROLLER_CONTROLLER_H_
#define CONTROLLER_CONTROLLER_H_

#include "abstract_controller.h"
#include "View/view.h"
#include "Model/model.h"

// This class controls the interaction between objects.
class Controller : public AbstractController {
 public:
  Controller();
  ~Controller() override = default;
  const std::list<std::shared_ptr< Enemy>>& GetEnemies() const override;
  void Tick(int current_time) override;
  void StartGame(int level) override;
  void EndGame(Exit exit) override;

 private:
  std::unique_ptr<Model> model_;
  std::unique_ptr<View> view_;

  void GameProcess();
  void MenuProcess();

  void CreateNextWave();
  bool CanCreateNextWave();
  void CreateEnemy(const Enemy& enemy) const;
  void TickSpawners();
  void TickEnemies();

  bool is_game_now_ = false;
  bool is_rounds_end_ = false;
  int current_time_ = 0;
  int last_round_start_time_ = 0;
};

#endif  // CONTROLLER_CONTROLLER_H_
