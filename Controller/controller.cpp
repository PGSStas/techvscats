#include "controller.h"

std::mt19937 Controller::random_generator_ = std::mt19937(
    std::chrono::system_clock::now().time_since_epoch().count());

Controller::Controller() : model_(std::make_unique<Model>()),
                           view_(std::make_unique<View>(this)) {}

void Controller::StartGame(int level_id) {
  game_status_ = GameStatus::kPlay;
  current_game_time_ = 0;
  last_time_end_particle_created = 0;
  window_type_ = WindowType::kGame;
  last_round_start_time_ = 0;
  model_->SetGameLevel(level_id);

  SetSpeedCoefficient(Speed::kNormalSpeed);
  view_->DisableMainMenuUi();
  view_->EnableGameUi();
  if (client_.IsOnline()) {
    client_.EnterRoom(level_id);
  }
}

void Controller::EndGame() {
  model_->ClearGameModel();
  view_->DisableGameUi();
  view_->EnableMainMenuUi();
  window_type_ = WindowType::kMainMenu;
  if (client_.IsOnline()) {
    client_.LeaveRoom();
  }
  current_game_time_ = 0;
}

void Controller::Tick(int current_time) {
  current_game_time_ = current_time;
  TickClient();
  TickTextNotifications();
  if (window_type_ == WindowType::kGame) {
    GameProcess();
  }
}

void Controller::SetSpeedCoefficient(Speed speed) {
  view_->ChangeGameSpeed(speed);
}

void Controller::SetBuilding(int index_in_buildings, int replacing_id) {
  int settle_cost = model_->GetBuildingById(replacing_id).GetCost();
  auto base = model_->GetBase();
  if (base->GetGold() >= settle_cost) {
    if (replacing_id == 0) {
      int sell_cost = model_->GetBuildings()[index_in_buildings]->GetTotalCost()
          * constants::kRefundCoefficient;

      model_->AddTextNotification({"+" + QString::number(sell_cost) + " gold",
                                   base->GetGoldPosition(), Qt::green,
                                   current_game_time_});
      base->AddGoldAmount(sell_cost);
      model_->CreateBuildingAtIndex(index_in_buildings, replacing_id);
    } else {
      model_->CreateBuildingAtIndex(index_in_buildings, replacing_id);
      base->SubtractGoldAmount(settle_cost);

      model_->AddTextNotification({"-" + QString::number(settle_cost) + " gold",
                                   base->GetGoldPosition(), Qt::red,
                                   current_game_time_});
    }
  } else {
    auto position = model_->GetBuildings()[index_in_buildings]->GetPosition();
    model_->AddTextNotification({QObject::tr("Not enough ") +
        constants::kCurrency, position, Qt::blue, current_game_time_});
  }
}

void Controller::GameProcess() {
  if (game_status_ == GameStatus::kPlay && CanCreateNextWave()) {
    CreateNextWave();
  }
  if (game_status_ != GameStatus::kPlay) {
    TickEndGame();
  }
  TickSpawners();
  TickEnemies();
  TickBuildings();
  TickProjectiles();
  TickAuras();
  TickParticleHandlers();
  TickParticles();
}

bool Controller::CanCreateNextWave() {
  // Check if Wave should be created
  int current_round_number = model_->GetCurrentRoundNumber();

  if (current_round_number == model_->GetRoundsCount() &&
      model_->GetEnemies()->empty() && model_->GetSpawners()->empty()
      && game_status_ == GameStatus::kPlay) {
    game_status_ = GameStatus::kWin;
    client_.RoundCompleted(model_->GetBase()->GetCurrentHealth(),
                           static_cast<int>( GameStatus::kWin));
    int life_time = 16000;
    double size_coefficient = 1.03;
    model_->AddTextNotification({"Level Complete",
                                 {constants::kGameWidth / 2,
                                  constants::kGameHeight / 2}, Qt::red,
                                 view_->GetRealTime(), {0, 0}, life_time,
                                 size_coefficient});
  }

  if (!model_->GetEnemies()->empty()
      || current_round_number == model_->GetRoundsCount()
      || !model_->GetSpawners()->empty()) {
    return false;
  }

  if (client_.IsOnline() && !client_.HasPermissionToStartRound()) {
    if (current_round_number != 0) {
      client_.RoundCompleted(model_->GetBase()->GetCurrentHealth(),
                             static_cast<int>( GameStatus::kPlay));
    }
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
  if (is_prepairing_to_spawn_) {
    last_round_start_time_ = current_game_time_;
    is_prepairing_to_spawn_ = false;
  }
  if (client_.IsOnline()) {
    client_.SetPermissionToStartRound(false);
  }
  return true;
}

void Controller::CreateNextWave() {
  auto&& enemy_groups = model_->GetEnemyGroupsPerRound(
      model_->GetCurrentRoundNumber());
  for (const auto& enemy_group : enemy_groups) {
    model_->AddSpawner(enemy_group);
  }
  model_->IncreaseCurrentRoundNumber();
}

void Controller::TickClient() {
  if (client_.IsReceivedMessageEmpty()) {
    return;
  }
  const auto& messages = client_.GetReceivedMessages();
  for (auto& message : messages) {
    switch (message.GetType()) {
      case MessageType::kDialog: {
        ProcessControllerMessage(message);
        break;
      }
      case MessageType::kControllerCommand: {
        ProcessControllerCommand(message);
        break;
      }
      default: {
        qDebug() << "error";
        break;
      }
    }
  }
  client_.ClearReceivedMessage();
}

void Controller::TickEndGame() {
  if (last_time_end_particle_created + kParticlesPeriod < current_game_time_) {
    last_time_end_particle_created = current_game_time_;
    ParticleParameters particle(
        (game_status_ == GameStatus::kLose) ? kLooseParticleId : kWinParticleId,
        {-1, -1},
        Coordinate(0, 0) + Size(
            random_generator_() % static_cast<int>(constants::kGameWidth),
            random_generator_()
                % static_cast<int>(constants::kGameHeight)));
    model_->CreateParticles({particle});
    if (random_generator_() % 1000 < 100) {
      const auto& buildings = model_->GetBuildings();
      for (uint32_t i = 0; i < buildings.size(); i++) {
        if (buildings[i]->GetId() != 0) {
          model_->CreateBuildingAtIndex(i, 0);
          return;
        }
      }
    }
  }
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
  if (model_->GetBase()->IsDead() && game_status_ == GameStatus::kPlay) {
    game_status_ = GameStatus::kLose;

    client_.RoundCompleted(model_->GetBase()->GetCurrentHealth(),
                           static_cast<int>( GameStatus::kLose));
    int life_time = 16000;
    double size_coefficient = 1.03;
    model_->AddTextNotification({"GameOver:(",
                                 {constants::kGameWidth / 2,
                                  constants::kGameHeight / 2}, Qt::red,
                                 view_->GetRealTime(), {0, 0}, life_time,
                                 size_coefficient});

  }
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
    notification.Tick(view_->GetRealTime());
  }
}

void Controller::TickParticleHandlers() {
  auto enemies = model_->GetEnemies();
  for (auto& enemy : *enemies) {
    TickParticleHandler(enemy->GetParticleHandler());
  }
  auto buildings = model_->GetBuildings();
  for (auto& building : buildings) {
    TickParticleHandler(building->GetParticleHandler());
  }
  auto projectiles = model_->GetProjectiles();
  for (auto& projectile : *projectiles) {
    TickParticleHandler(projectile->GetParticleHandler());
  }
  auto particles = model_->GetParticles();
  for (auto& particle : *particles) {
    TickParticleHandler(particle.GetParticleHandler());
  }
  auto base = model_->GetBase();
  TickParticleHandler(base->GetParticleHandler());
}

void Controller::TickParticleHandler(ParticleHandler* particle_handler) {
  particle_handler->Tick();
  if (particle_handler->IsReadyToCreateParticle()) {
    model_->CreateParticles(particle_handler->GetParticlesQueue());
    particle_handler->Clear();
  }
}

void Controller::TickParticles() {
  auto particles = model_->GetParticles();
  particles->remove_if([](const Particle& particle) {
    return particle.IsDead();
  });
  for (auto& particle : *particles) {
    particle.Tick(current_game_time_);
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

void Controller::CreateTowerMenu(int tower_index) {
  const auto& building = model_->GetBuildings()[tower_index];
  const auto& possible_upgrades = model_->GetUpgradesTree()[building->GetId()];
  view_->ReplaceTowerMenu(building->GetPosition(), tower_index,
                          possible_upgrades, building->GetId(),
                          building->GetTotalCost());
}

void Controller::MouseEvent(Coordinate position, bool is_press) {
  // Check if some tower was pressed
  const auto& buildings = model_->GetBuildings();
  for (size_t i = 0; i < buildings.size(); i++) {
    const auto& building = buildings[i];
    if (!building->IsInside(position)) {
      continue;
    }
    if (view_->IsTowerMenuEnabled()) {
      view_->DisableTowerMenu();
      return;
    }
    if (!is_press) {
      CreateTowerMenu(i);
    }
    return;
  }

  if (!view_->IsTowerMenuEnabled()) {
    return;
  }
  view_->DisableTowerMenu();
}

void Controller::RescaleObjects(const SizeHandler& size_handler) {
  model_->RescaleDatabase(size_handler);
}

const Building& Controller::GetBuildingById(int instance_id) const {
  return model_->GetBuildingById(instance_id);
}

const std::list<Particle>& Controller::GetParticles() const {
  return *model_->GetParticles();
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
  model_->AddTextNotification({QString::number(reward) + " "
                                   + constants::kCurrency,
                               enemy.GetPosition(), Qt::yellow,
                               view_->GetRealTime()});

  model_->GetBase()->AddGoldAmount(reward);
}

const AnimationPlayer& Controller::GetBackground(WindowType type) const {
  return model_->GetBackGround(static_cast<int>(type));
}

GameStatus Controller::GetCurrentStatus() const {
  return game_status_;
}

const QImage& Controller::GetEmptyZoneTexture(WindowType type) const {
  return model_->GetEmptyZoneTexture(static_cast<int>(type));
}

const AnimationPlayer& Controller::GetInterface() const {
  return model_->GetInterface();
}

int Controller::GetCurrentRoundNumber() const {
  return model_->GetCurrentRoundNumber();
}

int Controller::GetRoundsCount() const {
  return model_->GetRoundsCount();
}

MultiplayerClient* Controller::GetClient() {
  return &client_;
}

void Controller::ProcessControllerMessage(const Message& message) {
  switch (message.GetDialogType()) {
    case DialogType::kWarning: {
      model_->AddTextNotification(
          {message.GetArgument(0),
           {constants::kGameWidth / 2,
            constants::kGameHeight / 5},
           Qt::darkCyan, view_->GetRealTime(),
           {0, +40}, 3000, 1,
           50, true});
      break;
    }
    case DialogType::kChat: {
      view_->AddGlobalChatMessage(message.GetArgument(0).split("\n"));
      break;
    }
  }
}

void Controller::ProcessControllerCommand(const Message& message) {
  switch (message.GetControllerCommandType()) {
    case ControllerCommandType::kGoldChange: {
      if (WindowType::kGame == window_type_) {
        model_->GetBase()->AddGoldAmount(message.GetArgument(0).toInt());
      }
      break;
    }
    case ControllerCommandType::kHealthGrow: {
      if (WindowType::kGame == window_type_) {
        model_->GetBase()->DecreaseHealth(-10000);
      }
      break;
    }
  }
}
