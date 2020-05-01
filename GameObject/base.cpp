#include "base.h"

const Size Base::kBaseSize = Size(50, 50);
const Coordinate Base::kHealthPosition = Coordinate(1748, 811);
const Size Base::kHealthSize = Size(167, 167);
const Coordinate Base::kGoldPosition = Coordinate(1581, 1002);
const Size Base::kGoldSize = Size(164, 57);

Base::Base(int gold, double max_health, Coordinate position)
    : GameObject(Size(0, 0), position), gold_(gold),
      max_health_(max_health), current_health_(max_health) {}

void Base::Tick(int) {
  current_health_ = std::min(max_health_, current_health_ + regeneration_rate_);
}

void Base::Draw(QPainter* painter, const SizeHandler& size_handler) const {
  painter->save();

  painter->setBrush(Qt::magenta);

  auto point = size_handler.GameToWindowCoordinate(position_ - kBaseSize / 2);
  Size size = size_handler.GameToWindowSize(kBaseSize);

  painter->drawRect(point.x, point.y, size.width, size.height);

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
  current_health_ -= std::min(damage, current_health_);
  if (current_health_ <= constants::kEpsilon) {
    is_dead_ = true;
  }
}

double Base::GetCurrentHealth() const {
  return current_health_;
}

double Base::GetMaxHealth() const {
  return max_health_;
}

int Base::GetGold() const {
  return gold_;
}

Coordinate Base::GetGoldPosition() const {
  return kGoldPosition;
}

void Base::AddGoldAmount(int gold_amount) {
  gold_ += gold_amount;
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

