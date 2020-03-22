#include "controller.h"
#include <QDebug>
Controller::Controller() : model_(std::make_unique<Model>()),
                           view_(std::make_unique<View>(this)) {
}

void Controller::StartGame(int level_id) {
  qDebug() << "Game Start!";
  is_game_now_ = true;

  last_round_start_time_ = current_time_;
  is_rounds_end_ = false;

  model_->SetGameModel(level_id);

  view_->DisableMenuWindow();
  view_->EnableGameUi();
  view_->UpdateRounds(model_->GetCurrentRoundNumber(),
                      model_->GetRoundsCount());
}

void Controller::EndGame(int end_code) {
  // if end_code == 0 - win, 1 - return menu clicked
  model_->ClearGameModel();
  view_->DisableGameUi();
  view_->EnableMenuUi();
  is_game_now_ = false;
}

void Controller::Tick(int current_time) {
  current_time_ = current_time;
  if (is_game_now_) {
    GameProcess();
    return;
  }
  MenuProcess();
}

void Controller::MenuProcess() {
}

void Controller::GameProcess() {
  CreateNextWave();
  if((*model_->GetEnemies()).size()!=0) {
    int x = (*model_->GetEnemies()).back()->GGGRRRAA();
    x*=1;
    int g = x;
  }

  TickSpawners();
  TickEnemies();
}

void Controller::CreateNextWave() {
  // Checks if Wave can be created
  int current_round_number = model_->GetCurrentRoundNumber();
  if (is_rounds_end_ || current_time_ - last_round_start_time_
      < model_->GetTimeBetweenWaves()) {
    return;
  }

  last_round_start_time_ = current_time_;
  if (current_round_number == model_->GetRoundsCount()) {
    is_rounds_end_ = true;
    qDebug() << "Rounds end.";
    return;
  }

  int roads_number = model_->GetRoadsCount();
  for (int i = 0; i < roads_number; i++) {
    const Wave& temporary_wave = model_->GetWave(current_round_number, i);
    model_->AddSpawner(i, temporary_wave, current_time_);
  }

  model_->IncrementCurrentRoundNumber();

  view_->UpdateRounds(model_->GetCurrentRoundNumber(),
                      model_->GetRoundsCount());
  qDebug() << "Round!";
}

void Controller::TickSpawners() {
  std::list<Spawner>* spawners = model_->GetSpawners();
  spawners->remove_if([&](Spawner& i) { return i.IsDead(); });
  for (auto& spawner : *spawners) {
    spawner.Tick(current_time_);
    if (spawner.IsReadyToSpawn()) {
      CreateEnemy(spawner.GetEnemy());
    }
  }
}

void Controller::TickEnemies() {
  std::list<std::shared_ptr<Enemy>>* enemies = model_->GetEnemies();
  //enemies->remove_if([&](Enemy& i) { return i.IsDead(); });
  for (auto &enemy : *enemies) {
    enemy->Tick(current_time_);
  }
}

void Controller::CreateEnemy(const Enemy& enemy) const {
  model_->AddEnemyFromInstance(enemy,current_time_);
  qDebug() << "new enemy";
}

const std::list<std::shared_ptr<Enemy>>* Controller::GetEnemyes() const {
  return model_->GetEnemies();
}



