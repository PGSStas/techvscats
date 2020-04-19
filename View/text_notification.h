#ifndef VIEW_TEXT_NOTIFICATION_H_
#define VIEW_TEXT_NOTIFICATION_H_

#include <memory>
#include <QLabel>
#include <QString>

#include "Model/coordinate.h"
#include "size_handler.h"

class TextNotification {
 public:
  TextNotification(const QString& message, QMainWindow* main_window,
                   Coordinate start_position, QColor color, int creation_time,
                   Size moving_vector = Size(0, -8), int life_time = 1000);

  void Tick(int current_time, const SizeHandler& size_handler);

  bool IsDead() const;

 private:
  QLabel label_;
  Coordinate position_;
  Size moving_vector_;
  QColor color_;
  int creation_time_;
  int life_time_;

  bool is_dead_ = false;

  const double kFontSize = 15;
  const double kSlowdownCoefficient = 0.9;
};

#endif  // VIEW_TEXT_NOTIFICATION_H_
