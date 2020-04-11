#include <QDebug>

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
    id_(id), cost_(settle_cost) {
  size_ = size;
}

void Building::Draw(QPainter* painter, const SizeHandler& size_handler) const {
  painter->save();
  switch (action_) {
    case Action::reload: {
      painter->setBrush(reload_color_);
      break;
    }
    case Action::before_fire: {
      painter->setBrush(before_fire_color_);
      break;
    }
    case Action::after_fire: {
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
  wait_time_ += (current_time - object_time_);
  object_time_ = current_time;

  switch (action_) {
    case Action::reload: {
      if (wait_time_ > action_time[static_cast<int>(Action::reload)]) {
        if (is_ready_to_shoot) {
          wait_time_ = 0;
          action_ = Action::before_fire;
        }
      }
      break;
    }
    case Action::before_fire: {
      if (!is_ready_to_shoot) {
        action_ = Action::reload;
        wait_time_ = action_time[static_cast<int>(Action::reload)];
        return;
      }
      if (wait_time_ > action_time[static_cast<int>(Action::before_fire)]) {
        is_ready_to_create_projectiles_ = true;
        action_ = Action::after_fire;
        wait_time_ = 0;
      }
      break;
    }
    case Action::after_fire: {
      if (wait_time_ > action_time[static_cast<int>(Action::after_fire)]) {
        action_ = Action::reload;
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
  reload_color_ = reload_color;
  action_time[static_cast<int>(Action::reload)] = reload_time;
  before_fire_color_ = pre_color;
  action_time[static_cast<int>(Action::before_fire)] = before_fire_time;
  after_fire_color_ = post_color;
  action_time[static_cast<int>(Action::after_fire)] = after_fire_time;
}

void Building::UpdateAim(const std::list<std::shared_ptr<Enemy>>& enemies) {
  if ((wait_time_ < action_time[static_cast<int>(Action::reload)]
      && action_ == Action::reload) || action_ == Action::before_fire) {
    return;
  }
  if (enemies.empty()) {
    is_ready_to_shoot = false;
    aims_.clear();
    return;
  }
  aims_.remove_if([&](const auto& object) {
    return (object->IsDead() ||
        object->GetPosition().GetDistanceTo(position_).GetLength()
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
    if (enemy->GetPosition().GetDistanceTo(position_).GetLength()
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

std::vector<Projectile> Building::PrepareProjectiles(
    const Projectile& projectile_instance) {
  is_ready_to_create_projectiles_ = false;

  std::vector<Projectile> projectiles;
  for (auto& aim : aims_) {
    auto projectile = Projectile(projectile_instance);
    projectile.SetParameters(projectile_instance.GetSpeed(),
                             attack_damage_,
                             aim);
    projectile.SetPosition(position_);
    projectiles.push_back(projectile);
  }
  return projectiles;
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
  return point.GetDistanceTo(position_).GetLength() <= size_.width / 2;
}

int Building::GetId() const {
  return id_;
}
