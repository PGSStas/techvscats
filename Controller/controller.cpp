#include "controller.h"
#include <QDebug>

Controller::Controller() : model_(std::make_unique<Model>()),
                           view_(std::make_unique<View>(this)) {}

void Controller::StartGame(int level_id) {
  qDebug() << "Game Start!";
  is_game_now_ = true;

  last_round_start_time_ = current_time_;
  have_unprocess_rounds_ = true;

  model_->SetGameModel(level_id);

  view_->DisableMenuWindow();
  view_->EnableGameUi();
  view_->UpdateRounds(model_->GetCurrentRoundNumber(),
                      model_->GetRoundsCount());
}

void Controller::EndGame(Exit exit) {
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

void Controller::GameProcess() {
  if (CanCreateNextWave()) {
    CreateNextWave();
  }
  TickSpawners();
  TickEnemies();
  TickBuildings();
}

void Controller::MenuProcess() {}

bool Controller::CanCreateNextWave() {
  // Check if Wave should be created
  int current_round_number = model_->GetCurrentRoundNumber();
  if (!have_unprocess_rounds_ || current_time_ - last_round_start_time_
      < model_->GetTimeBetweenWaves()) {
    return false;
  }

  last_round_start_time_ = current_time_;
  if (current_round_number == model_->GetRoundsCount()) {
    have_unprocess_rounds_ = false;
    qDebug() << "Rounds end.";
    return false;
  }

  return true;
}

void Controller::CreateNextWave() {
  int current_round_number = model_->GetCurrentRoundNumber();
  int waves_count = model_->GetWavesCount(current_round_number);
  for (int i = 0; i < waves_count; i++) {
    const Wave& temporary_wave = model_->GetWave(current_round_number, i);
    model_->AddSpawner(temporary_wave, current_time_);
  }

  model_->IncreaseCurrentRoundNumber();

  view_->UpdateRounds(model_->GetCurrentRoundNumber(),
                      model_->GetRoundsCount());
  qDebug() << "Round!";
}

void Controller::TickSpawners() {
  auto* spawners = model_->GetSpawners();
  spawners->remove_if([&](const Spawner& sp) { return sp.IsDead(); });
  for (auto& spawner : *spawners) {
    spawner.Tick(current_time_);
    if (spawner.IsReadyToSpawn()) {
      Enemy enemy_to_spawn = spawner.GetEnemy();
      CreateEnemy(enemy_to_spawn);
    }
  }
}

void Controller::TickEnemies() {
  auto* enemies = model_->GetEnemies();
  for (auto& enemy : *enemies) {
    enemy->Tick();
  }
}

void Controller::TickBuildings() {
  auto* buildings = &model_->GetBuildings();
  for(auto& building:*buildings){
      building->Tick();
  }
}

void Controller::CreateEnemy(const Enemy& enemy) const {
  model_->AddEnemyFromInstance(enemy);
}

const std::list<std::shared_ptr<Enemy>>& Controller::GetEnemies() const {
  return *model_->GetEnemies();
}

const std::vector<Road>& Controller::GetRoads() const {
  return model_->GetRoads();
}

const std::vector<std::shared_ptr<Building>>& Controller::GetBuildings() const {
  return model_->GetBuildings();
}

void Controller::MousePress(Coordinate position) {
  // Check if some tower was pressed
  const auto& buildings = model_->GetBuildings();
  for (size_t i = 0; i < buildings.size(); i++) {
    const auto& building = buildings[i];
    if (!building->IsInside(position)) {
      continue;
    }
    // Check if that's the same building on which menu was already open
    // (which means now we should close it)
    if (view_->IsTowerMenuEnabled()
        && view_->GetTowerMenu()->GetTowerPosition()
            == building->GetPosition()) {
      view_->DisableTowerMenu();
      return;
    }

    // Create the appropriate menu
    std::vector<std::shared_ptr<TowerMenuOption>> options;
    const auto& building_tree = model_->GetBuildingsTree();
    int building_id = buildings[i]->GetId();
    for (const auto& to_upgrade_id : building_tree[building_id]) {
      // Tower building options
      options.push_back(std::make_shared<TowerMenuOption>(
          to_upgrade_id, [&, i, to_upgrade_id]() {
            ChangeBuildingAttempt(i, to_upgrade_id);
          }));
    }

    // Upgrade option
    if (building->GetMaxLevel() > building->GetCurrentLevel()) {
      options.push_back(std::make_shared<TowerMenuOption>(
          building_id, [&, i, building_id]() {
            ChangeBuildingAttempt(i, building_id);
          }));
    }
    auto menu = std::make_shared<TowerMenu>(building->GetPosition(),
                                            building->GetInteractionRadius(),
                                            options);
    view_->ShowTowerMenu(menu);
    return;
  }

  if (view_->GetTowerMenu() == nullptr) {
    return;
  }

// Check if tower menu element was pressed
  auto pressed = view_->GetTowerMenu()->GetPressedOption(position);
  if (pressed != nullptr) {
    pressed->Action();
    qDebug() << pressed->GetId() << " action";
  }

// Disables menu after some action or if random point on the map was pressed
  view_->DisableTowerMenu();
}

void Controller::ChangeBuildingAttempt(int building_number, int building_id) {
  auto buildings = model_->GetBuildings();

  // Some manipulations with gold should be added here
  if (buildings[building_number]->GetId() == building_id) {
    model_->UpgradeBuildingAt(building_number);
    return;
  }
  model_->SetBuildingAt(building_number, building_id);
}

