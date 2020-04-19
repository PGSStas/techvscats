#include "text_notification.h"

TextNotification::TextNotification(const QString& message,
                                   QMainWindow* main_window,
                                   Coordinate start_position, QColor color,
                                   int creation_time, Size moving_vector,
                                   int life_time) :
    position_(start_position), moving_vector_(moving_vector), color_(color),
    creation_time_(creation_time), life_time_(life_time) {
  label_ = new QLabel(main_window);
  label_->setText(message);
}

void TextNotification::Tick(int current_time) {
  position_ += moving_vector_;
  moving_vector_ *= kSlowdownCoefficient;
  if ((current_time - creation_time_ > life_time_)) {
    is_dead_ = true;
  }
}

bool TextNotification::IsDead() const {
  return is_dead_;
}

