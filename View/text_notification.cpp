#include "text_notification.h"

TextNotification::TextNotification(const QString& message,
                                   Coordinate start_position, QColor color,
                                   int creation_time, Size moving_vector,
                                   int life_time)
    : GameObject({0, 0}, start_position), message_(message),
      moving_vector_(moving_vector), color_(color),
      creation_time_(creation_time), life_time_(life_time) {}

void TextNotification::Tick(int current_time) {
  position_ += moving_vector_;
  moving_vector_ *= kSlowdownCoefficient;
  if ((current_time - creation_time_ > life_time_)) {
    is_dead_ = true;
  }
}

void TextNotification::Draw(QPainter* painter,
                            const SizeHandler& size_handler) const {
  painter->save();

  painter->setPen(color_);
  auto font = painter->font();
  font.setPixelSize(size_handler.GameToWindowLength(constants::kFontSize));
  font.setFamily(QFontDatabase::applicationFontFamilies(kFontId).at(0));
  painter->setFont(font);

  Coordinate point = size_handler.GameToWindowCoordinate(position_ - size_ / 2);
  painter->drawText(point.x, point.y, message_);

  painter->restore();
}

bool TextNotification::IsDead() const {
  return is_dead_;
}
