#include "controller.h"

Controller::Controller() : model_(std::make_unique<Model>()),
                           view_(std::make_unique<View>(this)),
                           game_mode_(WindowType::kMainMenu) {}

void Controller::StartGame(int level_id) {
  current_game_time_ = 0;
  game_mode_ = WindowType::kGame;
  last_round_start_time_ = current_game_time_;
  model_->SetGameLevel(level_id);

  view_->DisableMenuWindow();
  view_->EnableGameUi();
  view_->UpdateRounds(model_->GetCurrentRoundNumber(),
                      model_->GetRoundsCount());
}

void Controller::EndGame(Exit) {
  view_->DisableGameUi();
  view_->EnableMenuUi();
  model_->ClearGameModel();
  game_mode_ = WindowType::kMainMenu;
  current_game_time_ = 0;
}

void Controller::Tick(int current_time) {
  current_game_time_ = current_time;
  switch (game_mode_) {
    case WindowType::kGame: {
      GameProcess();
      break;
    }
    case WindowType::kMainMenu: {
      MenuProcess();
      break;
    }
  }
}

void Controller::GameProcess() {
  if (CanCreateNextWave()) {
    CreateNextWave();
  }
  TickSpawners();
  TickEnemies();
  TickBuildings();
  TickProjectiles();
  TickAuras();
  TickTextNotifications();
}

void Controller::MenuProcess() {}

bool Controller::CanCreateNextWave() {
  // Check if Wave should be created
  int current_round_number = model_->GetCurrentRoundNumber();
  if (!model_->GetEnemies()->empty()
      || current_round_number == model_->GetRoundsCount()
      || !model_->GetSpawners()->empty()) {
    return false;
  }

  if (!is_prepairing_to_spawn_) {
    last_round_start_time_ = current_game_time_;
    is_prepairing_to_spawn_ = true;
  }

  if (current_game_time_ - last_round_start_time_
      < model_->GetPrepairTimeBetweenRounds()) {
    return false;
  }

  last_round_start_time_ = current_game_time_;
  is_prepairing_to_spawn_ = false;
  return true;
}

void Controller::CreateNextWave() {
  auto&& enemy_groups = model_->GetEnemyGroupsPerRound(
      model_->GetCurrentRoundNumber());
  for (const auto& enemy_group : enemy_groups) {
    model_->AddSpawner(enemy_group);
  }
  model_->IncreaseCurrentRoundNumber();
  view_->UpdateRounds(model_->GetCurrentRoundNumber(),
                      model_->GetRoundsCount());
}

void Controller::TickSpawners() {
  auto spawners = model_->GetSpawners();
  spawners->remove_if([](const Spawner& spawner) { return spawner.IsDead(); });
  for (auto& spawner : *spawners) {
    spawner.Tick(current_game_time_ - last_round_start_time_);
    if (spawner.IsReadyToSpawn()) {
      Enemy enemy = model_->GetEnemyById(spawner.PrepareNextEnemyId());
      enemy.SetRoad(model_->GetRoad(spawner.GetRoad()));
      AddEnemyToModel(enemy);
    }
  }
}

void Controller::TickEnemies() {
  auto enemies = model_->GetEnemies();
  enemies->remove_if([this](const auto& enemy) {
    if (enemy->IsDead()) {
      ProcessEnemyDeath(*enemy);
    }
    return enemy->IsDead() || enemy->IsEndReached();
  });
  auto base = model_->GetBase();
  for (auto& enemy : *enemies) {
    enemy->Tick(current_game_time_);
    if (enemy->IsEndReached()) {
      base->DecreaseHealth(enemy->GetDamage());
    }
  }
}

void Controller::TickBuildings() {
  const auto& buildings = model_->GetBuildings();
  for (const auto& building : buildings) {
    building->Tick(current_game_time_);
    building->UpdateAim(*model_->GetEnemies());
    if (!building->IsReadyToCreateProjectiles()) {
      continue;
    }
    const auto& aims = building->GetAims();
    building->SetReadyToCreateProjectileToFalse();
    for (const auto& aim : aims) {
      model_->CreateProjectile(aim, *building);
    }
  }

  // Base
  model_->GetBase()->Tick(current_game_time_);
}

void Controller::TickProjectiles() {
  auto projectiles = model_->GetProjectiles();
  projectiles->remove_if([](const auto& projectile) {
    return projectile->IsDead();
  });

  for (auto& projectile : *projectiles) {
    projectile->Tick(current_game_time_);
    if (!projectile->IsEndReached()) {
      continue;
    }
    auto enemies = model_->GetEnemies();
    for (const auto& enemy : *enemies) {
      if (projectile->IsInAffectedArea(*enemy)) {
        enemy->ReceiveDamage(projectile->GetDamage());
      }
    }
  }
}

void Controller::TickAuras() {
  const auto& enemies = *model_->GetEnemies();
  for (const auto& enemy : enemies) {
    enemy->GetAppliedEffect()->ResetEffect();
  }

  const auto& buildings = model_->GetBuildings();
  for (const auto& building : buildings) {
    building->GetAppliedEffect()->ResetEffect();
  }

  for (const auto& enemy : enemies) {
    ApplyEffectToAllInstances(enemy->GetAuricField());
  }

  for (const auto& building : buildings) {
    ApplyEffectToAllInstances(building->GetAuricField());
  }
}

void Controller::TickTextNotifications() {
  auto text_notifications = model_->GetTextNotifications();
  text_notifications->remove_if([](const TextNotification& text_notification) {
    return text_notification.IsDead();
  });
  for (auto& notification : *text_notifications) {
    notification.Tick(current_game_time_);
  }
}

void Controller::ApplyEffectToAllInstances(const AuricField& aura) {
  if (!aura.IsValid()) {
    return;
  }

  const Effect& effect = model_->GetEffectById(aura.GetEffectId());
  EffectTarget effect_target = effect.GetEffectTarget();

  if (effect_target == EffectTarget::kAny
      || effect_target == EffectTarget::kEnemy) {
    const auto& enemies = *model_->GetEnemies();

    for (const auto& enemy : enemies) {
      if (aura.IsInRadius(enemy->GetPosition())) {
        *enemy->GetAppliedEffect() += effect;
      }
    }
  }
  if (effect_target == EffectTarget::kAny
      || effect_target == EffectTarget::kBuilding) {
    const auto& buildings = model_->GetBuildings();

    for (const auto& building : buildings) {
      if (aura.IsInRadius(building->GetPosition())) {
        *building->GetAppliedEffect() += effect;
      }
    }
  }
}

void Controller::AddEnemyToModel(const Enemy& enemy) const {
  model_->AddEnemyFromInstance(enemy);
}

void Controller::SetBuilding(int index_in_buildings, int replacing_id) {
  int settle_cost = model_->GetBuildingById(replacing_id).GetCost();
  auto base = model_->GetBase();
  if (base->GetGold() >= settle_cost) {
    if (replacing_id == 0) {
      int sell_cost = model_->GetBuildings()[index_in_buildings]->GetTotalCost()
          * kRefundCoefficient;

      model_->AddTextNotification(TextNotification(
          "+ " + QString::number(sell_cost) + " gold", Size(70, 30),
          base->GetGoldPosition(), Qt::green, current_game_time_));
      base->AddGoldAmount(sell_cost);
      model_->CreateBuildingAtIndex(index_in_buildings, replacing_id);
    } else {
      model_->CreateBuildingAtIndex(index_in_buildings, replacing_id);
      base->SubtractGoldAmount(settle_cost);

      model_->AddTextNotification(TextNotification(
          "- " + QString::number(settle_cost) + " gold", Size(70, 30),
          base->GetGoldPosition(), Qt::red, current_game_time_));
    }
  } else {
    model_->AddTextNotification(TextNotification(
        "Not enough gold", Size(70, 30),
        base->GetGoldPosition(), Qt::blue, current_game_time_));
  }
}

void Controller::CreateTowerMenu(int tower_index) {
  std::vector<std::shared_ptr<TowerMenuOption>> options;
  const auto& buildings = model_->GetBuildings();
  const auto& building = buildings[tower_index];
  const auto& upgrade_tree = model_->GetUpgradesTree();
  int building_id = buildings[tower_index]->GetId();
  // Tower building & evolve & delete options (will affect the type of tower)
  for (const auto& to_change_id : upgrade_tree[building_id]) {
    options.push_back(std::make_shared<TowerMenuOption>(
        model_->GetBuildingById(to_change_id),
        [this, tower_index, to_change_id]() {
          SetBuilding(tower_index, to_change_id);
        }));
  }
  auto menu = std::make_shared<TowerMenu>(
      current_game_time_, *building, options);
  view_->ShowTowerMenu(menu);
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
        && view_->GetTowerMenu()->GetTower().GetPosition()
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

  // TODO(elizabethfeden): qt buttons.
  auto pressed = view_->GetTowerMenu()->GetButtonInside(position);
  if (pressed != nullptr) {
    pressed->MakeAction();
  }
  view_->DisableTowerMenu();
}

void Controller::MouseMove(Coordinate position) {
  if (!view_->IsTowerMenuEnabled()) {
    return;
  }

  auto button = view_->GetTowerMenu()->GetButtonInside(position);
  view_->GetTowerMenu()->Hover(button);
}

void Controller::RescaleObjects(const SizeHandler& size_handler) {
  model_->RescaleDatabase(size_handler);
}

const std::list<std::shared_ptr<Enemy>>& Controller::GetEnemies() const {
  return *model_->GetEnemies();
}

const std::vector<std::shared_ptr<Building>>&
  Controller::GetBuildings() const {
  return model_->GetBuildings();
}

const std::list<std::shared_ptr<AbstractProjectile>>&
  Controller::GetProjectiles() const {
  return *model_->GetProjectiles();
}

const std::list<TextNotification>& Controller::GetTextNotifications() const {
  return *model_->GetTextNotifications();
}

const Base& Controller::GetBase() const {
  return *model_->GetBase();
}

int Controller::GetCurrentTime() const {
  return current_game_time_;
}

void Controller::ProcessEnemyDeath(const Enemy& enemy) const {
  int reward = enemy.ComputeReward();
  model_->AddTextNotification(TextNotification(
      QString::number(reward) + " gold", Size(70, 30),
      enemy.GetPosition(), Qt::yellow, current_game_time_));
  model_->GetBase()->AddGoldAmount(reward);
}

const AnimationPlayer& Controller::GetMap() const {
  return model_->GetMap();
}
