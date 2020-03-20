#include "controller.h"
#include <QDebug>
Controller::Controller() : model_(std::make_unique<Model>()),
                           view_(std::make_unique<View>(this)) {
}

void Controller::StartGame(int level_id) {
  model_->SetGameModel(level_id);
  tick_id_ = startTimer(time_between_ticks);
  is_game_now_ = true;
  game_start_time_.start();
  last_round_start_time_ = 0;
}

void Controller::EndGame(int end_code) {
  game_start_time_.invalidate();
  // if 0 - win
}

void Controller::CreateNextWave() {
  // checks if Wave can be created
  int currrent_round_number = model_->GetCurrentRoundNumber();
  if (game_start_time_.elapsed() - last_round_start_time_
      < model_->GetTimeBetweenWaves()) {
    return;
  }
  if (currrent_round_number == model_->GetRoundsCount()) {
    EndGame(0);
    return;
  }

  for (int i = 0; i < currrent_round_number; i++) {
    Wave temporary_wave = model_->GetRounds()[currrent_round_number][i];
    model_->CreateSpawner(i, temporary_wave);
  }
  model_->IncrementCurrentRoundNumber();
}

void Controller::MenuProcess() {
}

void Controller::GameProcess() {
  CreateNextWave();
}

void Controller::Tick() {
  if (is_game_now_) {
    GameProcess();
    return;
  }
  MenuProcess();
}

void Controller::timerEvent(QTimerEvent* event) {
  if (event->timerId() == tick_id_) {
    Tick();
  }
  view_->repaint();
}


