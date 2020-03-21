#ifndef CONTROLLER_CONTROLLER_H_
#define CONTROLLER_CONTROLLER_H_

#include <vector>
#include <memory>

#include <QElapsedTimer>
#include <QTimerEvent>
#include "abstract_controller.h"
#include "View/view.h"
#include "Model/model.h"

// This class controls the interaction between objects.
class Controller : public AbstractController, public QMainWindow {

 public:
  Controller();
  ~Controller() override = default;

  void StartGame(int level) override;
  void EndGame(int end_code) override;
  void Tick() override;

 private:
  void timerEvent(QTimerEvent* event);
  std::unique_ptr<Model> model_;
  std::unique_ptr<View> view_;
  QElapsedTimer game_time_;

  void GameProcess();
  void MenuProcess();

  void CreateNextWave();
  void CreateEnemy(const Enemy* enemy) const;
  void TickSpawners(int current_time) const ;

  bool is_game_now_;
  bool is_rounds_end_;
  int last_round_start_time_;
  int tick_id_;
  const int time_between_ticks = 10;
};

#endif  // CONTROLLER_CONTROLLER_H_
