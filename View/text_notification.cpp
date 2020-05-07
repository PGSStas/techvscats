#include "text_notification.h"

TextNotification::TextNotification(const QString& message,
                                   Coordinate start_position, QColor color,
                                   int creation_time, Size moving_vector,
                                   int life_time,
                                   double size_change_coefficient,
                                   double font_size)
    : GameObject({0, 0}, start_position), message_(message),
      force_vector_(moving_vector), color_(color),
      creation_time_(creation_time), life_time_(life_time),
      size_change_coefficient_(size_change_coefficient),
      font_size_(font_size) {}

void TextNotification::Tick(int current_time) {
  UpdateTime(current_time);
  position_ += force_vector_ * delta_time_ / constants::kTimeScale;
  font_size_ *= size_change_coefficient_;
  font_size_ = std::min(font_size_, kMaxTextSize);
  force_vector_ *= kSlowdownCoefficient;
  life_time_ -= delta_time_;
  if (life_time_ < 0) {
    is_dead_ = true;
  }
}

void TextNotification::Draw(QPainter* painter,
                            const SizeHandler& size_handler) const {
  painter->save();

  painter->setPen(color_);
  auto font = painter->font();
  font.setPixelSize(size_handler.GameToWindowLength(font_size_));
  font.setFamily(QFontDatabase::applicationFontFamilies(kFontId).at(0));
  painter->setFont(font);

  // Position, for camera span
  Coordinate point = size_handler.GameToWindowCoordinate(
      {position_.x - font_size_ * message_.size() * 0.35,
       position_.y + font_size_ / 4});
  if (font_size_ <= kMaxTextSize + constants::kEpsilon) {
    painter->drawText(point.x, point.y, message_);
  }

  painter->restore();
}

bool TextNotification::IsDead() const {
  return is_dead_;
}
