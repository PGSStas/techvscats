#include <QDebug>

#include "building.h"

Building::Building(const Building& other) :
    Building(other.id_, other.max_level_, other.settle_cost_,
             other.upgrade_cost_, other.size_, other.enemies_) {
  SetProjectile(other.max_aims_,
                other.attack_range_,
                other.attack_damage_,
                other.projectile_id_);
  SetAnimationParameters(other.reload_color_, other.reload_time_,
                         other.pre_fire_color_, other.pre_fire_time_,
                         other.post_fire_color_, other.post_fire_time_);
  size_ = other.size_;
  current_level_ = other.current_level_;
}

Building::Building(int id, int max_level, int settle_cost,
                   int upgrade_cost, Size size,
                   const std::list<std::shared_ptr<Enemy>>& enemies) :
    id_(id), max_level_(max_level), settle_cost_(settle_cost),
    upgrade_cost_(upgrade_cost), enemies_(enemies) {
  size_ = size;
}

void Building::Draw(QPainter* painter, const SizeHandler& size_handler) const {
  painter->save();
  switch (action) {
    case Action::reload: painter->setBrush(reload_color_);
      break;
    case Action::pre_fire: painter->setBrush(pre_fire_color_);
      break;
    case Action::post_fire: painter->setBrush(post_fire_color_);
      break;
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

void Building::SetProjectile(int max_aims, int attack_range,
                             double attack_damage, int projectile_id) {
  max_aims_ = max_aims;
  attack_range_ = attack_range;
  attack_damage_ = attack_damage;
  projectile_id_ = projectile_id;
  current_level_ = 1;
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
        object->GetPosition().GetDistanceTo(position_).GetLength()
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
    if (enemy->GetPosition().GetDistanceTo(position_).GetLength()
        > attack_range_) {
      continue;
    }
    for (auto& aim : aims_) {
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
  for (auto& aim : aims_) {
    auto projectile = Projectile(projectile_instance);
    projectile.SetParameters(projectile_instance.GetSpeed(),
                             attack_damage_,
                             aim);
    projectile.SetPosition(position_);
    projectile.SetType(projectile_instance.GetType());
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

void Building::Upgrade() {
  current_level_++;
}

int Building::GetMaxLevel() const {
  return max_level_;
}

int Building::GetCurrentLevel() const {
  return current_level_;
}
