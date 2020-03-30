#include <QDebug>

#include "building.h"

int Building::GetId() const {
  return id_;
}

int Building::GetProjectileId() const {
  return projectile_id_;
}

bool Building::IsInside(Coordinate point) const {
  return point.GetBetween(position_).GetLength() <= kInteractionRadius;
}

void Building::Upgrade() {
  current_level_++;
  qDebug() << "building #" << id_ << " upgraded to" << current_level_;
}

Building::Building(const std::list<std::shared_ptr<Enemy>>& enemies,
                   const std::vector<std::shared_ptr<Building>>& buildings,
                   int tower_type) :
    enemies_(enemies), buildings_(buildings), kTowerType(tower_type) {
  qDebug() << &enemies_;
}

int Building::GetInteractionRadius() const {
  return kInteractionRadius;
}

int Building::GetTowerType() const {
  return kTowerType;
}

Building::Building(const std::shared_ptr<const Building>& other) :
    Building(other->enemies_, other->buildings_, other->kTowerType) {
  SetParameters(other->id_, other->projectile_id_, other->max_level_,
                other->settle_cost_, other->upgrade_cost_,
                other->action_range_, other->action_power_);
  SetAnimationParameters(other->reload_color_, other->reload_time_,
                         other->pre_fire_color_, other->pre_fire_time_,
                         other->post_fire_color_, other->post_fire_time_);

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

  painter->drawEllipse(QPoint(position_.x, position_.y),
                       kInteractionRadius,
                       kInteractionRadius);
  painter->restore();
}

int Building::GetMaxLevel() const {
  return max_level_;
}

int Building::GetCurrentLevel() const {
  return current_level_;
}
void Building::SetParameters(int id, int projectile_id,
                             int max_level,
                             int settle_cost,
                             int upgrade_cost,
                             int action_range,
                             int action_power) {
  id_ = id;
  projectile_id_ = projectile_id;
  max_level_ = max_level;
  current_level_ = 0;
  settle_cost_ = settle_cost;
  upgrade_cost_ = upgrade_cost;
  action_range_ = action_range;
  action_power_ = action_power;
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

void Building::Tick(int controller_current_time) {}
void Building::UpdateAim() {}
void Building::DoAction() {}

std::vector<std::shared_ptr<Projectile>> Building::PrepareProjectile(const std::shared_ptr<
    Projectile>& projectile_instence) {
  is_ready_to_create_projectile_ = false;

  std::vector<std::shared_ptr<Projectile>> projectiles;
  for (auto& aim:aims_) {
    auto projectile = std::make_shared<Projectile>(projectile_instence);
    projectile->SetParameters(projectile_id_,
                              action_power_ * action_power_coefficient_,
                              projectile_instence->GetSpeed(), aim);
    projectile->SetPosition(position_);
    projectiles.push_back(projectile);
  };
  return projectiles;
}
bool Building::IsReadyToCreateProjectile() const {
  return is_ready_to_create_projectile_;
}
