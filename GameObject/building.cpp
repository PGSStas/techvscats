#include "building.h"

Building::Building(int id, int settle_cost, const AuricField& aura, Size size)
    : GameObject(size), auric_field_(aura), id_(id), cost_(settle_cost) {
  auric_field_.SetCarrierCoordinate(&position_);
}

Building::Building(const Building& other) :
    Building(other.id_, other.cost_, other.auric_field_, other.size_) {
  SetProjectile(other.projectile_id_, other.attack_damage_,
                other.attack_range_, other.max_aims_, other.shooting_anchor_);
  SetAnimationPlayers(other.animation_players_);
  particle_handler_.SetParticlePacks(other.particle_handler_);
  SetInfo(other.header_, other.description_);
}

void Building::Tick(int current_time) {
  UpdateTime(current_time);
  wait_time_ += delta_time_ * applied_effect_.GetAttackRateCoefficient();

  Action old_action = action_;
  switch (action_) {
    case Action::kWait: {
      if (is_ready_to_shoot_) {
        action_ = Action::kBeforeFire;
        wait_time_ = delta_time_;
      }
      break;
    }
    case Action::kBeforeFire: {
      if (!is_ready_to_shoot_) {
        action_ = Action::kWait;
        wait_time_ = 0;
        break;
      }
      if (wait_time_ > action_timings_[static_cast<int>(Action::kBeforeFire)]) {
        is_ready_to_create_projectiles_ = true;
        action_ = Action::kAfterFire;
        wait_time_ -= action_timings_[static_cast<int>(Action::kBeforeFire)];
      }
      break;
    }
    case Action::kAfterFire: {
      if (wait_time_ > action_timings_[static_cast<int>(Action::kAfterFire)]) {
        action_ = Action::kWait;
      }
      break;
    }
  }
  if (old_action == action_) {
    animation_players_[static_cast<int>(action_)].Tick(delta_time_ *
        applied_effect_.GetAttackRateCoefficient());
  } else {
    animation_players_[static_cast<int>(action_)].Reset();
  }
}

void Building::UpdateAim(const std::list<std::shared_ptr<Enemy>>& enemies) {
  if (action_ == Action::kAfterFire || id_ == 0) {
    return;
  }
  bool need_change_ = aims_.size() < max_aims_;
  for (const auto& enemy : aims_) {
    if (!IsInAttackRange(enemy->GetPosition()) || enemy->IsDead()) {
      need_change_ = true;
      break;
    }
  }
  if (!need_change_) {
    return;
  }
  aims_.clear();
  if (enemies.empty()) {
    is_ready_to_shoot_ = false;
    return;
  }
  for (const auto& enemy : enemies) {
    if (IsInAttackRange(enemy->GetPosition())) {
      aims_.push_back(enemy);
    }
  }
  Coordinate position = position_;
  aims_.sort([&position](const std::shared_ptr<Enemy>& one,
                         const std::shared_ptr<Enemy>& other) {
    if (one->GetPriority() != other->GetPriority()) {
      return one->GetPriority() < other->GetPriority();
    }
    return one->GetPosition().GetVectorTo(position).GetLength() <
        other->GetPosition().GetVectorTo(position).GetLength();
  });
  if (aims_.size() > max_aims_) {
    aims_.resize(max_aims_);
  }

  is_ready_to_shoot_ = !aims_.empty();
}

void Building::Draw(QPainter* painter, const SizeHandler& size_handler) const {
  painter->save();
  Coordinate point =
      size_handler.GameToWindowCoordinate(position_ - size_ / 2);
  painter->drawPixmap(
      point.x, point.y,
      animation_players_[static_cast<int>(action_)].GetCurrentFrame());
  painter->restore();
}

void Building::SetProjectile(int projectile_id,
                             double attack_damage,
                             int attack_range,
                             int max_aims,
                             Size shooting_anchor) {
  projectile_id_ = projectile_id;
  attack_damage_ = attack_damage;
  attack_range_ = attack_range;
  max_aims_ = max_aims;
  shooting_anchor_ = shooting_anchor;
}

void Building::SetReadyToCreateProjectileToFalse() {
  is_ready_to_create_projectiles_ = false;
}

void Building::SetTotalCost(int total_cost) {
  total_cost_ = total_cost;
}

void Building::SetInfo(const QString& header, const QString& description) {
  header_ = header;
  description_ = description;
}

int Building::GetId() const {
  return id_;
}

int Building::GetAttackRange() const {
  return attack_range_ * applied_effect_.GetRangeCoefficient();
}

int Building::GetProjectileId() const {
  return projectile_id_;
}

double Building::GetDamage() const {
  return attack_damage_ * applied_effect_.GetDamageCoefficient();
}

int Building::GetCost() const {
  return cost_;
}

int Building::GetTotalCost() const {
  return total_cost_;
}

const QString& Building::GetHeader() const {
  return header_;
}

const QString& Building::GetDescription() const {
  return description_;
}

uint32_t Building::GetMaxAims() const {
  return max_aims_;
}

double Building::GetProjectileSpeedCoefficient() const {
  return applied_effect_.GetMoveSpeedCoefficient();
}

Effect* Building::GetAppliedEffect() {
  return &applied_effect_;
}

const AuricField& Building::GetAuricField() const {
  return auric_field_;
}

const std::list<std::shared_ptr<Enemy>>& Building::GetAims() const {
  return aims_;
}

bool Building::IsInside(Coordinate point) const {
  return point.GetVectorTo(position_).GetLength() <= size_.width / 2;
}

bool Building::IsReadyToCreateProjectiles() const {
  return is_ready_to_create_projectiles_;
}

bool Building::IsInAttackRange(Coordinate coordinate) const {
  double result_range = attack_range_ * applied_effect_.GetRangeCoefficient();
  // Lower ellipse to the basement of the tower.
  coordinate.y -= size_.height / 3;
  return coordinate.IsInEllipse(position_, result_range);
}

Size Building::GetShootingAnchor() const {
  return shooting_anchor_;
}

int Building::GetReloadTime() const {
  return animation_players_[1].GetAnimationDuration()
      + animation_players_[2].GetAnimationDuration();
}

const Effect& Building::GetEffect() const {
  return applied_effect_;
}
