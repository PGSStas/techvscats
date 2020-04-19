#include "text_notification.h"

const double TextNotification::kFontSize = 15;
const double TextNotification::kSlowdownCoefficient = 0.9;

TextNotification::TextNotification(const QString& message,
                                   QMainWindow* main_window,
                                   Coordinate start_position, QColor color,
                                   int creation_time, Size moving_vector,
                                   int life_time) :
    position_(start_position), moving_vector_(moving_vector), color_(color),
    creation_time_(creation_time), life_time_(life_time) {
  label_ = std::make_shared<QLabel>(message, main_window);
  label_->show();

  auto pallete = label_->palette();
  pallete.setColor(label_->backgroundRole(), color);
  pallete.setColor(label_->foregroundRole(), color);
  label_->setPalette(pallete);
}

void TextNotification::Tick(int current_time, const SizeHandler& size_handler) {
  position_ += moving_vector_;
  moving_vector_ *= kSlowdownCoefficient;
  if ((current_time - creation_time_ > life_time_)) {
    is_dead_ = true;
  }

  Coordinate point = size_handler.GameToWindowCoordinate(position_);
  label_->setGeometry(point.x, point.y, label_->width(), label_->height());

  auto font = label_->font();
  font.setPointSize(size_handler.GameToWindowLength(kFontSize));
  label_->setFont(font);
}

bool TextNotification::IsDead() const {
  return is_dead_;
}


