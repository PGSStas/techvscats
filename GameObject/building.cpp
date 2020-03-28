#include <QDebug>

#include "building.h"

int Building::GetId() const {
  return id_;
}

bool Building::IsInside(Coordinate point) const {
  return point.GetBetween(position_).GetLength() <= kInteractionRadius;
}

void Building::Upgrade() {
  current_level_++;
  qDebug() << "building #" << id_ << " upgraded to" << current_level_;
}

Building::Building(const std::list<std::shared_ptr<Enemy>>& enemies,
                   int tower_type) :
    enemies_(enemies), kTowerType(tower_type) {
}

int Building::GetInteractionRadius() const {
  return kInteractionRadius;
}

int Building::GetTowerType() const {
  return kTowerType;
}

Building::Building(const std::shared_ptr<Building>& other) :
    Building(other->enemies_, other->kTowerType) {
  SetParameters(other->id_, other->max_level_,
                other->settle_cost_, other->upgrade_cost_,
                other->action_range_, other->action_power_);
  SetActions(other->wait_color_, other->wait_time_,
             other->pre_fire_color_, other->pre_fire_time_,
             other->post_fire_color_, other->post_fire_time_);
}

void Building::Tick() {}

void Building::Draw(QPainter* painter) const {
  painter->save();
  painter->setBrush(wait_color_);
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
void Building::SetParameters(int id,
                             int max_level,
                             int settle_cost,
                             int upgrade_cost,
                             int action_range,
                             int action_power) {
  id_ = id;
  max_level_ = max_level;
  current_level_ = 0;
  settle_cost_ = settle_cost;
  upgrade_cost_ = upgrade_cost;
  action_range_ = action_range;
  action_power_ = action_power;
}

void Building::SetActions(QColor wait_color,
                          int wait_time,
                          QColor pre_color,
                          int pre_fire_time,
                          QColor post_color,
                          int post_fire_time) {
  wait_color_ = wait_color;
  wait_time_ = wait_time;
  pre_fire_color_ = pre_color;
  pre_fire_time_ = pre_fire_time;
  post_fire_color_ = post_color;
  post_fire_time_ = post_fire_time;
}
