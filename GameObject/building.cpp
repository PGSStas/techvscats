#include <QDebug>
#include <utility>

#include "building.h"

Building::Building(const Building& other) :
    Building(other.size_, other.id_, other.cost_) {
  SetProjectile(other.projectile_id_,other.attack_damage_,
                other.attack_range_,other.max_aims_);
  SetAnimationParameters(other.reload_color_, other.action_time[0],
                         other.before_fire_color_, other.action_time[1],
                         other.after_fire_color_, other.action_time[2]);
}

Building::Building(Size size, int id, int settle_cost) :
    GameObject(size), id_(id), cost_(settle_cost) {}

void Building::Tick(int current_time) {
  if (max_aims_ == 0) {
    return;
  }
  UpdateTime(current_time);
  wait_time_ += delta_tick_time_*applied_effect_.GetAttackRateCoefficient();

  switch (action_) {
    case Action::kReload: {
      if (wait_time_ > action_time[static_cast<int>(Action::kReload)]) {
        if (is_ready_to_shoot) {
          wait_time_ = 0;
          action_ = Action::kBeforeFire;
        }
      }
      break;
    }
    case Action::kBeforeFire: {
      if (!is_ready_to_shoot) {
        action_ = Action::kReload;
        wait_time_ = action_time[static_cast<int>(Action::kReload)];
        return;
      }
      if (wait_time_ > action_time[static_cast<int>(Action::kBeforeFire)]) {
        is_ready_to_create_projectiles_ = true;
        action_ = Action::fAfterFire;
        wait_time_ = 0;
      }
      break;
    }
    case Action::fAfterFire: {
      if (wait_time_ > action_time[static_cast<int>(Action::fAfterFire)]) {
        action_ = Action::kReload;
      }
      break;
    }
  }
}

void Building::UpdateAim(const std::list<std::shared_ptr<Enemy>>& enemies) {
  if ((wait_time_ < action_time[static_cast<int>(Action::kReload)]
      && action_ == Action::kReload) || action_ == Action::kBeforeFire) {
    return;
  }
  if (enemies.empty()) {
    is_ready_to_shoot = false;
    aims_.clear();
    return;
  }
  aims_.remove_if([&](const auto& object) {
    return (object->IsDead() ||
        object->GetPosition().GetVectorTo(position_).GetLength()
            > attack_range_*applied_effect_.GetRangeCoefficient());
  });

  if (aims_.size() == max_aims_) {
    is_ready_to_shoot = true;
    return;
  }

  for (auto& enemy : enemies) {
    if (aims_.size() == max_aims_
        || aims_.size() == enemies.size()) {
      break;
    }
    if (enemy->GetPosition().GetVectorTo(position_).GetLength()
        > attack_range_*applied_effect_.GetRangeCoefficient()) {
      continue;
    }
    bool can_add = true;
    for (auto& aim : aims_) {
      if (aim == enemy) {
        can_add = false;
        break;
      }
    }
    if (can_add) {
      aims_.push_back(enemy);
    }
  }
  is_ready_to_shoot = !aims_.empty();
}

void Building::Draw(QPainter* painter, const SizeHandler& size_handler) const {
  painter->save();
  switch (action_) {
    case Action::kReload: {
      painter->setBrush(reload_color_);
      break;
    }
    case Action::kBeforeFire: {
      painter->setBrush(before_fire_color_);
      break;
    }
    case Action::fAfterFire: {
      painter->setBrush(after_fire_color_);
      break;
    }
  }

  Coordinate center = size_handler.GameToWindowCoordinate(position_);
  Size size = size_handler.GameToWindowSize(size_);
  painter->drawEllipse(QPointF(center.x, center.y),
                       size.width / 2,
                       size.height / 2);
  painter->restore();
}

void Building::SetAnimationParameters(QColor reload_color, int reload_time,
                                      QColor pre_color, int before_fire_time,
                                      QColor post_color, int after_fire_time) {
  reload_color_ = std::move(reload_color);
  action_time[static_cast<int>(Action::kReload)] = reload_time;
  before_fire_color_ = std::move(pre_color);
  action_time[static_cast<int>(Action::kBeforeFire)] = before_fire_time;
  after_fire_color_ = std::move(post_color);
  action_time[static_cast<int>(Action::fAfterFire)] = after_fire_time;
}

void Building::SetProjectile(int projectile_id, double attack_damage,
                             int attack_range, int max_aims) {
  projectile_id_ = projectile_id;
  attack_damage_ = attack_damage;
  attack_range_ = attack_range;
  max_aims_ = max_aims;
}

void Building::SetReadyToCreateProjectileToFalse() {
  is_ready_to_create_projectiles_ = false;
}

int Building::GetId() const {
  return id_;
}

int Building::GetAttackRange() const {
  return attack_range_*applied_effect_.GetRangeCoefficient();
}

int Building::GetProjectileId() const {
  return projectile_id_;
}

double Building::GetDamage() const {
  return attack_damage_*applied_effect_.GetDamageCoefficient();
}

double Building::GetProjectileSpeedCoefficient() const {
  return applied_effect_.GetMooveSpeedCoefficient();
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
