#include "enemy.h"

std::mt19937 Enemy::random_generator_ = std::mt19937(
    std::chrono::system_clock::now().time_since_epoch().count());

Enemy::Enemy(double speed, double damage, double armor, int reward,
             double max_health, Size size, int priority, AuricField auric_field)
    : MovingObject(size, speed), damage_(damage), armor_(armor),
      reward_(reward), max_health_(max_health), current_health_(max_health_),
      priority_(priority), auric_field_(auric_field), node_number_(0) {
  health_bar_shift_ = Size(health_bar_size_.width / 2, size_.width / 4);
}

Enemy::Enemy(const Enemy& other)
    : Enemy(other.speed_, other.damage_, other.armor_,
            other.reward_, other.max_health_, other.size_, other.priority_,
            other.auric_field_) {
  SetDrawingAttitude(other.drawing_attitude_);
  SetAnimationPlayers(other.animation_players_);
  SetTowerKiller(other.tower_kill_radius_, other.kill_reload_);
  SetBreeder(other.times_to_breed_, other.new_enemies_count_,
      other.breed_attitude_);

  SetBossMusicId(other.boss_music_id_);
  health_bar_size_ = other.health_bar_size_;
  health_bar_shift_ = Size(health_bar_size_.width / 2, size_
      .height * other.health_bar_shift_.height / other.size_.height);
  health_bar_shift_ = other.health_bar_shift_;
  front_health_color_ = other.front_health_color_;
  back_health_color_ = other.back_health_color_;

  particle_handler_.SetParticlePacks(other.particle_handler_);
  auric_field_.SetCarrierCoordinate(&position_);
  if (other.road_ != nullptr) {
    SetRoad(*other.road_);
  }
}

void Enemy::Tick(int current_time) {
  UpdateTime(current_time);
  Move();
  animation_players_[0].Tick(delta_time_ *
      applied_effect_.GetMoveSpeedCoefficient());
  wait_to_kill_ -= delta_time_;
}

void Enemy::Move() {
  if (is_end_reached_) {
    return;
  }
  double speed = speed_;
  speed_ *= applied_effect_.GetMoveSpeedCoefficient();
  MoveToDestination();
  speed_ = speed;
  if (position_ == destination_) {
    node_number_++;
    if (road_->IsEnd(node_number_)) {
      is_end_reached_ = true;
      is_dead_ = true;
      return;
    }
    destination_ = (road_->GetNode(node_number_));
    if (!road_->IsEnd(node_number_ + 1)) {
      ShiftCoordinate(&destination_);
    }
  }
}

void Enemy::Draw(QPainter* painter, const SizeHandler& size_handler) const {
  painter->save();

  Coordinate point = size_handler.GameToWindowCoordinate(
      position_ - size_ / 2);
  Size size = size_handler.GameToWindowSize(size_);

  painter->translate(point.x, point.y);
  if (position_.GetVectorTo(destination_).width < constants::kEpsilon) {
    painter->translate(size.width, 0);
    // mirroring the image
    painter->scale(-1.0, 1.0);
  }
  QPoint new_position_with_attitude(0, 0);
  new_position_with_attitude =
      QPoint(size.width * drawing_attitude_.width,
             size.height * drawing_attitude_.height);
  painter->drawPixmap(new_position_with_attitude,
                      animation_players_[0].GetCurrentFrame());

  painter->restore();
}

void Enemy::DrawHealthBar(QPainter* painter,
                          const SizeHandler& size_handler) const {
  painter->save();
  Coordinate point =
      size_handler.GameToWindowCoordinate(position_ - health_bar_shift_);
  painter->setBrush(back_health_color_);
  Size size = size_handler.GameToWindowSize(health_bar_size_);
  painter->drawRect(point.x, point.y, size.width, size.height);
  painter->setBrush(front_health_color_);
  size = size_handler.GameToWindowSize(Size(
      health_bar_size_.width * current_health_ / max_health_,
      health_bar_size_.height));
  painter->drawRect(point.x, point.y, size.width, size.height);

  painter->restore();
}

void Enemy::SetRoad(const Road& road) {
  road_ = std::make_shared<const Road>(road);
  position_ = road_->GetNode(node_number_);
  destination_ = road_->GetNode(node_number_);
  if (!road_->IsEnd(node_number_ + 1)) {
    ShiftCoordinate(&destination_);
  }
}

void Enemy::CopyPosition(const Enemy& instance, bool go_back) {
  position_ = instance.position_;
  destination_ = instance.destination_;
  node_number_ = instance.node_number_;
  if (go_back) {
    node_number_ -= random_generator_() % 5;
    destination_ = (road_->GetNode(node_number_));
  }
}

const AuricField& Enemy::GetAuricField() const {
  return auric_field_;
}

Effect* Enemy::GetAppliedEffect() {
  return &applied_effect_;
}

Coordinate Enemy::GetPredictPosition(double predict_power) const {
  Size move_vector = position_.GetVectorTo(destination_).Normalize();
  Coordinate prefire_position = position_;
  prefire_position +=
      move_vector * speed_ * predict_power * constants::kTimeScale
          / delta_time_;
  return prefire_position;
}

double Enemy::GetDamage() const {
  return damage_ * applied_effect_.GetDamageCoefficient();
}

void Enemy::ReceiveDamage(double damage) {
  double armor = armor_ * applied_effect_.GetArmorCoefficient() / 100;
  current_health_ -= std::min((1 - armor) * damage, current_health_);
  if (current_health_ <= constants::kEpsilon) {

    Size attitude = {size_.width * drawing_attitude_.width,
                     size_.height * drawing_attitude_.height};
    position_ += attitude;
    particle_handler_.PlayOwnerDeath();
    position_ -= attitude;

    is_dead_ = true;
  }
}

int Enemy::ComputeReward() const {
  return reward_;
}

void Enemy::SetBigHealth(Size health_bar_size_attitude,
                         double health_bar_shift_attitude) {
  front_health_color_ = Qt::darkGreen;
  back_health_color_ = Qt::black;

  health_bar_size_ *= health_bar_size_attitude;
  health_bar_shift_ = Size(health_bar_size_.width / 2, size_
      .height * health_bar_shift_attitude);
}

void Enemy::SetTowerKiller(double tower_kill_radius, int kill_reload) {
  tower_kill_radius_ = tower_kill_radius;
  kill_reload_ = kill_reload;
  wait_to_kill_ = kill_reload_ / 2;
}

bool Enemy::IsTowerKiller() const {
  return tower_kill_radius_ != 0;
}

bool Enemy::IsTimeToKill() const {
  return wait_to_kill_ < 0;
}

void Enemy::SetBreeder(int times_to_breed, int count,
                       BreederAttitude breed_apply_attitude) {
  times_to_breed_ = times_to_breed;
  new_enemies_count_ = count;
  breed_attitude_ = breed_apply_attitude;
}

bool Enemy::IsBreeder() const {
  return times_to_breed_ != 0;
}

void Enemy::KillReload() {
  wait_to_kill_ = kill_reload_;
}

double Enemy::GetKillRadius() const {
  return tower_kill_radius_;
}

double Enemy::GetNewEnemiesCount() const {
  return new_enemies_count_;
}

void Enemy::Breed() {
  times_to_breed_--;
  size_ *= breed_attitude_.size_coefficient;
  damage_ *= breed_attitude_.damage_coefficient;
  speed_ *= breed_attitude_.speed_coefficient;
  armor_ *= breed_attitude_.armor_coefficient;
}

int Enemy::GetBossMusicId() {
  return boss_music_id_;
}

void Enemy::SetBossMusicId(int music_id) {
  boss_music_id_ = music_id;
}

void Enemy::ShiftCoordinate(Coordinate* coordinate) {
  // We make small shifts so that enemies move chaotically,
  // not in the linear queue
  coordinate->x += static_cast<int32_t>(random_generator_()) % kMoveShift
      - kMoveShift / 2;
  coordinate->y += static_cast<int32_t>(random_generator_()) % kMoveShift
      - kMoveShift / 2;
}

int Enemy::GetPriority() const {
  return priority_;
}
