#include "controller.h"
#include <QDebug>

Controller::Controller() : model_(std::make_unique<Model>()),
                           view_(std::make_unique<View>(this)),
                           game_mode_(WindowType::kMainMenu) {}

void Controller::StartGame(int level_id) {
  qDebug() << "Game Start!";
  game_mode_ = WindowType::kGame;

  last_round_start_time_ = current_time_;
  has_unprocessed_rounds_ = true;

  model_->SetGameLevel(level_id);

  view_->DisableMenuWindow();
  view_->EnableGameUi();
  view_->UpdateRounds(model_->GetCurrentRoundNumber(),
                      model_->GetRoundsCount());
}

void Controller::EndGame(Exit exit_code) {
  model_->ClearGameModel();
  view_->DisableGameUi();
  view_->EnableMenuUi();
  game_mode_ = WindowType::kMainMenu;
}

void Controller::Tick(int current_time) {
  current_time_ = current_time;
  if (game_mode_ == WindowType::kGame) {
    GameProcess();
  } else {
    MenuProcess();
  }
}

void Controller::GameProcess() {
  if (CanCreateNextWave()) {
    CreateNextWave();
  }
  TickSpawners();
  TickEnemies();
  TickAuras();
  model_->GetBase()->Tick();
}

void Controller::MenuProcess() {}

bool Controller::CanCreateNextWave() {
  // Check if Wave should be created
  int current_round_number = model_->GetCurrentRoundNumber();
  if (!has_unprocessed_rounds_ || current_time_ - last_round_start_time_
      < model_->GetTimeBetweenWaves()) {
    return false;
  }

  last_round_start_time_ = current_time_;
  if (current_round_number == model_->GetRoundsCount()) {
    has_unprocessed_rounds_ = false;
    qDebug() << "Rounds end.";
    return false;
  }

  return true;
}

void Controller::CreateNextWave() {
  auto&& enemy_groups =
      model_->GetEnemyGroupsPerRound(model_->GetCurrentRoundNumber());
  for (const auto& enemy_group : enemy_groups) {
    model_->AddSpawner(enemy_group);
  }

  model_->IncreaseCurrentRoundNumber();
  view_->UpdateRounds(model_->GetCurrentRoundNumber(),
                      model_->GetRoundsCount());
  qDebug() << "Round!";
}

void Controller::TickSpawners() {
  auto spawners = model_->GetSpawners();
  spawners->remove_if([&](const Spawner& spawner) { return spawner.IsDead(); });
  for (auto& spawner : *spawners) {
    spawner.Tick(current_time_ - last_round_start_time_);
    if (spawner.IsReadyToSpawn()) {
      Enemy enemy = model_->GetEnemyById(spawner.PrepareNextEnemyId());
      enemy.SetRoad(model_->GetRoad(spawner.GetRoad()));
      AddEnemyToModel(enemy);
    }
  }
}

void Controller::TickEnemies() {
  auto enemies = model_->GetEnemies();
  auto base = model_->GetBase();

  for (auto& enemy : *enemies) {
    enemy->Tick();
    if (enemy->IsEndReached()) {
      base->DecreaseHealth(enemy->GetDamage());
    }
  }
  enemies->remove_if([&](const std::shared_ptr<Enemy>& enemy) {
    return enemy->IsDead() || enemy->IsEndReached();
  });
}

void Controller::AddEnemyToModel(const Enemy& enemy) const {
  model_->AddEnemyFromInstance(enemy);
}

const std::list<std::shared_ptr<Enemy>>& Controller::GetEnemies() const {
  return *model_->GetEnemies();
}

const std::vector<Road>& Controller::GetRoads() const {
  return model_->GetRoads();
}

void Controller::TickAuras() {
  const auto& enemies = *model_->GetEnemies();
  const auto& buildings = model_->GetBuildings();

  for (auto& enemy : enemies) {
    enemy->GetAppliedEffect()->ResetEffect();
  }

  for (auto& building : buildings) {
    building->GetAppliedEffect()->ResetEffect();
  }

  for (auto& enemy : enemies) {
    ApplyEffectToAllInstances(*enemy->GetAuricField());
  }

  for (auto& building : buildings) {
    ApplyEffectToAllInstances(*building->GetAuricField());
  }
}

void Controller::ApplyEffectToAllInstances(const AuricField& aura) {
  if (!aura.IsValid()) {
    return;
  }

  EffectTarget effect_target =
      model_->GetEffectById(aura.GetEffectId()).GetEffectTarget();

  if (effect_target == EffectTarget::kAll
      || effect_target == EffectTarget::kEnemies) {
    const auto& enemies = *model_->GetEnemies();

    const Effect& effect = model_->GetEffectById(aura.GetEffectId());
    for (const auto& enemy : enemies) {
      if (aura.IsInRadius(enemy->GetPosition())) {
        *enemy->GetAppliedEffect() += effect;
      }
    }
  }
  if (effect_target == EffectTarget::kAll
      || effect_target == EffectTarget::kBuildings) {
    const auto& buildings = model_->GetBuildings();

    const Effect& effect = model_->GetEffectById(aura.GetEffectId());
    for (const auto& building : buildings) {
      if (aura.IsInRadius(building->GetPosition())) {
        *building->GetAppliedEffect() += effect;
      }
    }
  }
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
        && view_->GetTowerMenu()->GetTower()->GetPosition()
            == building->GetPosition()) {
      view_->DisableTowerMenu();
      return;
    }

    CreateTowerMenu(i);
    return;
  }

  if (!view_->IsTowerMenuEnabled()) {
    return;
  }

  // Check if tower menu element was pressed
  auto pressed = view_->GetTowerMenu()->GetButtonContaining(position);
  if (pressed != nullptr) {
    pressed->MakeAction();
    qDebug() << pressed->GetReplacingTower().GetId() << " action";
  }

  // Disables menu after some action or if random point on the map was pressed
  view_->DisableTowerMenu();
}

void Controller::SetBuilding(int index_in_buildings, int replacing_id) {
  const auto& buildings = model_->GetBuildings();
  if (buildings[index_in_buildings]->GetId() == replacing_id) {
    model_->UpgradeBuildingAtIndex(index_in_buildings);
  } else {
    model_->SetBuildingAtIndex(index_in_buildings, replacing_id);
  }
}

void Controller::CreateTowerMenu(int tower_index) {
  std::vector<std::shared_ptr<TowerMenuOption>> options;
  const auto& buildings = model_->GetBuildings();
  const auto& building = buildings[tower_index];
  const auto& upgrade_tree = model_->GetUpgradesTree();
  int building_id = buildings[tower_index]->GetId();

  // Upgrade option (will only affect level of tower, but not the type)
  if (building->GetMaxLevel() > building->GetCurrentLevel()) {
    options.push_back(std::make_shared<TowerMenuOption>(
        model_->GetBuildingById(building_id),
        [&, tower_index, building_id]() {
          SetBuilding(tower_index, building_id);
        }));
  }

  // Tower building & evolve & delete options (will affect the type of tower)
  for (const auto& to_change_id : upgrade_tree[building_id]) {
    options.push_back(std::make_shared<TowerMenuOption>(
        model_->GetBuildingById(to_change_id),
        [&, tower_index, to_change_id]() {
          SetBuilding(tower_index, to_change_id);
        }));
  }

  auto menu = std::make_shared<TowerMenu>(current_time_, building, options);
  view_->ShowTowerMenu(menu);
}

void Controller::MouseMove(Coordinate position) {
  if (!view_->IsTowerMenuEnabled()) {
    return;
  }

  auto button = view_->GetTowerMenu()->GetButtonContaining(position);
  view_->GetTowerMenu()->Hover(button);
}

const Base& Controller::GetBase() const {
  return *model_->GetBase();
}
