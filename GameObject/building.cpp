#include <QDebug>
#include <utility>

#include "building.h"

Building::Building(const Building& other) :
    Building(other.id_, other.cost_, other.size_) {
  SetProjectile(other.max_aims_,
                other.attack_range_,
                other.attack_damage_,
                other.projectile_id_);
  SetAnimationParameters(other.reload_color_, other.action_time[0],
                         other.before_fire_color_, other.action_time[1],
                         other.after_fire_color_, other.action_time[2]);
}

Building::Building(int id, int settle_cost, Size size) :
    GameObject(size), id_(id), cost_(settle_cost) {}

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

void Building::Tick(int current_time) {
  if (max_aims_ == 0) {
    return;
  }
  UpdateTime(current_time);
  wait_time_ += delta_tick_time_;

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

void Building::SetProjectile(int max_aims, int attack_range,
                             double attack_damage, int projectile_id) {
  max_aims_ = max_aims;
  attack_range_ = attack_range;
  attack_damage_ = attack_damage;
  projectile_id_ = projectile_id;
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
            > attack_range_);
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
        > attack_range_) {
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

bool Building::IsReadyToCreateProjectiles() const {
  return is_ready_to_create_projectiles_;
}

int Building::GetAttackRange() const {
  return attack_range_;
}

int Building::GetProjectileId() const {
  return projectile_id_;
}

bool Building::IsInside(Coordinate point) const {
  return point.GetVectorTo(position_).GetLength() <= size_.width / 2;
}

int Building::GetId() const {
  return id_;
}

const std::list<std::shared_ptr<Enemy>>& Building::GetAims() const {
  return aims_;
}

void Building::SetReadyToCreateProjectileToFalse() {
  is_ready_to_create_projectiles_ = false;
}

double Building::GetDamage() const {
  return attack_damage_;
}
