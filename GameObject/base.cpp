#include "base.h"

std::mt19937 Base::random_generator_ = std::mt19937(
    std::chrono::system_clock::now().time_since_epoch().count());

Base::Base(int gold, Size size, Coordinate position, double max_health)
    : GameObject(size, position), gold_(gold), max_health_(max_health),
      current_health_(max_health) {}

void Base::Tick(int current_time) {
  UpdateTime(current_time);
  animation_players_[0].Tick(delta_time_);
  int period = 0;
  double health_percent = current_health_ / max_health_;
  if (health_percent < kHealthFlameTheshold) {
    period = kFlameSpawnSpeed * health_percent;
    period = std::max(period, 200);
  }

  particle_handler_.SetPeriod(period);
}

void Base::Draw(QPainter* painter, const SizeHandler& size_handler) const {
  painter->save();

  Coordinate point = size_handler.GameToWindowCoordinate(
      position_ - size_ / 2);
  painter->drawPixmap(point.x, point.y, animation_players_[0].GetCurrentFrame());

  painter->restore();
}

void Base::DrawUI(QPainter* painter, const SizeHandler& size_handler) const {
  painter->save();

  auto font = painter->font();
  font.setPixelSize(size_handler.GameToWindowLength(constants::kFontSize));
  font.setFamily(QFontDatabase::applicationFontFamilies(0).at(0));
  painter->setFont(font);

  Coordinate health_background = size_handler.GameToWindowCoordinate(
      kHealthPosition);
  Size health_size = size_handler.GameToWindowSize(kHealthSize);
  painter->setBrush(Qt::red);
  painter->drawEllipse(health_background.x, health_background.y,
                       health_size.width, health_size.height);

  painter->setBrush(Qt::black);
  double eng = 0 + (1 - current_health_ / max_health_) * 180;
  painter->drawChord(health_background.x,
                     health_background.y,
                     health_size.width,
                     health_size.height,
                     -eng * 16 + 90 * 16,
                     2 * eng * 16);

  painter->setBrush(QBrush(qRgb(103, 103, 103)));
  Coordinate gold_top_corner = size_handler.GameToWindowCoordinate(
      kGoldPosition);
  Size gold_size = size_handler.GameToWindowSize(kGoldSize);
  painter->drawRect(gold_top_corner.x, gold_top_corner.y,
                    gold_size.width, gold_size.height);

  painter->setPen(Qt::white);
  painter->drawText(health_background.x, health_background.y,
                    health_size.width, health_size.height, Qt::AlignCenter,
                    QString::number(static_cast<int>(current_health_)));

  painter->setPen(Qt::yellow);
  painter->drawText(gold_top_corner.x, gold_top_corner.y,
                    gold_size.width, gold_size.height,
                    Qt::Alignment({Qt::AlignVCenter, Qt::AlignRight}),
                    QString::number(gold_) + " " + constants::kCurrency + " ");

  painter->restore();
}

void Base::DecreaseHealth(double damage) {
  if (!is_immortal_) {
    current_health_ -= std::min(damage, current_health_);
  }
  Coordinate rand_position = position_;
  rand_position +=
      Size(random_generator_() % static_cast<int>(size_.width / 1.5)
               - size_.width / 3,
           random_generator_() % static_cast<int>(size_.height / 1.5)
               - size_.height / 3);
  particle_handler_.AddParticle(
      ParticleParameters(0, size_ / 3, rand_position));

  if (current_health_ <= constants::kEpsilon) {
    is_dead_ = true;
  }
}

void Base::SetImmortal() {
  is_immortal_ = true;
  current_health_ = 666;
}

double Base::GetCurrentHealth() const {
  return current_health_;
}

int Base::GetGold() const {
  return gold_;
}

Coordinate Base::GetGoldPosition() const {
  return kGoldPosition;
}

void Base::AddGoldAmount(int gold_amount) {
  gold_ += std::max(gold_amount, 0);
  gold_ = std::min(9999, gold_);
}

void Base::SubtractGoldAmount(int gold_amount) {
  gold_ -= gold_amount;
}

bool Base::IsDead() const {
  return is_dead_;
}

Size Base::GetGoldSize() const {
  return kGoldSize;
}
