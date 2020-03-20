#include "controller.h"

Controller::Controller() : model_(std::make_unique<Model>()),
                           view_(std::make_unique<View>(this)) {
}

void Controller::StartGame(int level_id) {
  model_->SetGameModel(level_id);
  game_start_time_.start();
  last_round_start_time = 0;
}

void Controller::EndGame(int code) {
  // if 0 - win
}

void Controller::CreateNextWave() {
  /* check if Wave be created
  if (game_start_time.elapsed() - last_round_start_time
      < model_->map.time_to_prepair) {
    return;
  }
  if (model_->map.current_round_num == model_->map.rounds_count) {
    EndGame(0);
    return;
  }*/
  //  for (int i = 0; i < model_->map.current_round_num; i++) { // spawn create part
  //   Wave current = model_->map.Rounds[model_->map.current_round_num][i];
  // new Spawner(i,current); spawner Create part
  // }
  //++model_->map.current_round_num;
}

void Controller::MenuProcess() {
}

void Controller::GameProcess() {
  CreateNextWave();
}

void Controller::Tick() {
  if (game_start_time.isValid()) {
    GameProcess();
    return;
  }
  MenuProcess();
}

void Controller::timerEvent(QTimerEvent* event) {
  if (event->timerId() == tick_id_) {
    Tick();
  }
 // view_->repaint();
}


