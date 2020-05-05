#include "text_notification.h"

TextNotification::TextNotification(const QString& message,
                                   Coordinate start_position, QColor color,
                                   int creation_time, Size moving_vector,
                                   int life_time,
                                   double size_change_coefficient)
    : GameObject({0, 0}, start_position), message_(message),
      force_vector_(moving_vector), color_(color),
      creation_time_(creation_time), life_time_(life_time),
      size_change_coefficient_(size_change_coefficient) {}

void TextNotification::Tick(int current_time) {
  UpdateTime(current_time);
  position_ += force_vector_ * delta_time_ / constants::kTimeScale;
  font_size *= size_change_coefficient_;
  font_size = std::min(font_size, 40000.0);
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
  font.setPixelSize(size_handler.GameToWindowLength(font_size));
  font.setFamily(QFontDatabase::applicationFontFamilies(kFontId).at(0));
  painter->setFont(font);

  Coordinate point = size_handler.GameToWindowCoordinate(
      {position_.x - font_size * message_.size() * 0.35,
       position_.y + font_size / 4});
  if (font_size != 40000)
  painter->drawText(point.x, point.y, message_);

  painter->restore();
}

bool TextNotification::IsDead() const {
  return is_dead_;
}
