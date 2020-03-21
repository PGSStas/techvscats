#include "controller.h"
#include <QDebug>
Controller::Controller() : model_(std::make_unique<Model>()),
                           view_(std::make_unique<View>(this)),
                           is_game_now_(false) {
}

void Controller::StartGame(int level_id) {
  qDebug() << "Game Start!";
  is_game_now_ = true;

  game_time_.start();
  last_round_start_time_ = 0;
  tick_id_ = startTimer(time_between_ticks);

  model_->SetGameModel(level_id);

  view_->DisableMenuWindow();
  view_->EnableGameWindow();
  view_->UpdateRounds(model_->GetCurrentRoundNumber(),
                      model_->GetRoundsCount());
}

void Controller::EndGame(int end_code) {
  // if end_code == 0 - win, 1 - return menu clicked
  model_->ClearGameModel();
  view_->DisableGameWindow();
  view_->EnableMenuWindow();
  is_game_now_ = false;
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

void Controller::MenuProcess() {
}

void Controller::GameProcess() {
  CreateNextWave();
  TickSpawners(game_time_.elapsed());
}

void Controller::CreateNextWave() {
  // Checks if Wave can be created
  int current_round_number = model_->GetCurrentRoundNumber();
  if (is_rounds_end_ || game_time_.elapsed() - last_round_start_time_
      < model_->GetTimeBetweenWaves()) {
    return;
  }

  last_round_start_time_ = game_time_.elapsed();
  if (current_round_number == model_->GetRoundsCount()) {
    is_rounds_end_ = true;
    qDebug() << "Round ends.";
    return;
  }

  int roads_number = model_->GetRoadsCount();
  for (int i = 0; i < roads_number; i++) {
    const Wave* temporary_wave = model_->GetWave(current_round_number, i);
    model_->AddSpawner(i, temporary_wave, game_time_.elapsed());
  }

  model_->IncrementCurrentRoundNumber();

  view_->UpdateRounds(model_->GetCurrentRoundNumber(),
                      model_->GetRoundsCount());
  qDebug() << "Round!";
}

void Controller::TickSpawners(int current_time) const{
  std::list<Spawner>* spawners = model_->GetSpawners();
  spawners->remove_if([&](Spawner& i) { return i.IsDead(); });
  for (auto& spawner : *spawners) {
    spawner.Tick(current_time);
    if (spawner.IsReadyToSpawn()) {
      CreateEnemy(spawner.GetEnemy());
    }
  }
}

void Controller::CreateEnemy(const Enemy* enemy) const {
  model_->AddEnemyFromInstance(enemy);
  qDebug() << "new enemy";
}


