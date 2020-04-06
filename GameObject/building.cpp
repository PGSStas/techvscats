#include <QDebug>

#include "building.h"

int Building::GetProjectileId() const {
  return projectile_id_;
}

bool Building::IsInside(Coordinate point) const {
  return point.GetBetween(position_).GetLength() <= kInteractionRadius;
}

int Building::GetId() const {
  return id_;
}

void Building::Upgrade() {
  current_level_++;
}

Building::Building(const std::list<std::shared_ptr<Enemy>>& enemies) :
    enemies_(enemies) {

}

Building::Building(const Building& other) : Building(other.enemies_) {
  SetParameters(other.id_,
                other.max_level_,
                other.settle_cost_,
                other.upgrade_cost_,
                other.max_aims_,
                other.attack_range_,
                other.attack_damage_,
                other.projectile_id_);
  SetAnimationParameters(other.reload_color_, other.reload_time_,
                         other.pre_fire_color_, other.pre_fire_time_,
                         other.post_fire_color_, other.post_fire_time_);
  current_level_ = other.current_level_;
}

void Building::Draw(QPainter* painter) const {
  painter->save();
  switch (action) {
    case Action::reload: painter->setBrush(reload_color_);
      break;
    case Action::pre_fire: painter->setBrush(pre_fire_color_);
      break;
    case Action::post_fire: painter->setBrush(post_fire_color_);
      break;
  }
  painter->save();
  painter->drawEllipse(QPoint(position_.x, position_.y),
                       kInteractionRadius,
                       kInteractionRadius);
}

void Building::Tick(int controller_current_time) {
  if (max_aims_ == 0) {
    return;
  }
  wait_time_ += (controller_current_time - object_current_time_);
  object_current_time_ = controller_current_time;

  switch (action) {
    case Action::reload:
      if (wait_time_ > reload_time_) {
        UpdateAim();
        if (have_possible_to_shoot_) {
          wait_time_ = 0;
          action = Action::pre_fire;
        }
      }
      break;
    case Action::pre_fire:UpdateAim();
      if (!have_possible_to_shoot_) {
        action = Action::reload;
        wait_time_ = reload_time_;
        return;
      }
      if (wait_time_ > pre_fire_time_) {
        if (have_possible_to_shoot_) {
          is_ready_to_create_projectiles_ = true;
          action = Action::post_fire;
          wait_time_ = 0;
        }
        break;
        case Action::post_fire:
          if (wait_time_ > post_fire_time_) {
            action = Action::reload;
          }
        break;
      }
  }

}

int Building::GetMaxLevel() const {
  return max_level_;
}

int Building::GetCurrentLevel() const {
  return current_level_;
}

void Building::SetParameters(int id,
                             int max_level,
                             int settle_cost,
                             int upgrade_cost,
                             int max_aims,
                             int attack_range,
                             int attack_damage,
                             int projectile_id) {

  id_ = id;
  projectile_id_ = projectile_id;
  max_level_ = max_level;
  current_level_ = 1;
  settle_cost_ = settle_cost;
  upgrade_cost_ = upgrade_cost;
  attack_range_ = attack_range;
  attack_damage_ = attack_damage;
  max_aims_ = max_aims;
}

void Building::SetAnimationParameters(QColor wait_color,
                                      int wait_time,
                                      QColor pre_color,
                                      int pre_fire_time,
                                      QColor post_color,
                                      int post_fire_time) {
  reload_color_ = wait_color;
  reload_time_ = wait_time;
  pre_fire_color_ = pre_color;
  pre_fire_time_ = pre_fire_time;
  post_fire_color_ = post_color;
  post_fire_time_ = post_fire_time;
}

void Building::UpdateAim() {
  if (enemies_.empty()) {
    have_possible_to_shoot_ = false;
    aims_.clear();
    return;
  }
  aims_.remove_if([&](const auto& object) {
    return (object->IsDead() ||
        object->GetPosition().GetBetween(position_).GetLength()
            > attack_range_);
  });

  if (static_cast<int>(aims_.size()) == max_aims_) {
    have_possible_to_shoot_ = true;
    return;
  }

  for (auto& enemy:enemies_) {
    if (static_cast<int>(aims_.size()) == max_aims_
        || aims_.size() == enemies_.size()) {
      break;
    }
    bool can_add = true;
    if (enemy->GetPosition().GetBetween(position_).GetLength()
        > attack_range_) {
      continue;
    }
    for (auto& aim:aims_) {
      if (aim->GetPosition() == enemy->GetPosition()) {
        can_add = false;
        break;
      }
    }
    if (can_add) {
      aims_.push_back(enemy);
    }
  }
  have_possible_to_shoot_ = !aims_.empty();
}

std::vector<Projectile> Building::PrepareProjectiles(
    const Projectile& projectile_instance) {
  is_ready_to_create_projectiles_ = false;

  std::vector<Projectile> projectiles;
  for (auto& aim:aims_) {
    auto projectile = Projectile(projectile_instance);
    projectile.SetParameters(projectile_instance.GetSpeed(),
                             attack_damage_,
                             aim);
    projectile.SetPosition(position_);
    projectiles.push_back(projectile);
  }
  return projectiles;
}

bool Building::IsReadyToCreateProjectile() const {
  return is_ready_to_create_projectiles_;
}

int Building::GetAttackRange() const {
  return attack_range_;
}