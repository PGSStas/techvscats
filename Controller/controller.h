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

  void GameProcess();
  void MenuProcess();
  void CreateNextWave();
  void timerEvent(QTimerEvent* event);
  QElapsedTimer game_start_time_; // class for time access
  std::unique_ptr<Model> model_;
  std::unique_ptr<View> view_;
  int last_round_start_time;
  int tick_id_;  // info for timer
  const int tick_time_ = 10; // time between tick
};

#endif  // CONTROLLER_CONTROLLER_H_
