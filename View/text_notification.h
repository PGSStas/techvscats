#ifndef VIEW_TEXT_NOTIFICATION_H_
#define VIEW_TEXT_NOTIFICATION_H_

#include <memory>
#include <QLabel>
#include <QString>

#include "GameObject/game_object.h"
#include "size_handler.h"

class TextNotification : public GameObject {
 public:
  TextNotification(const QString& message, Size size,
                   Coordinate start_position, QColor color, int creation_time,
                   Size moving_vector = Size(0, -8), int life_time = 1000);
  ~TextNotification() override = default;

  void Tick(int current_time) override;
  void Draw(QPainter* painter, const SizeHandler& size_handler) const override;

  bool IsDead() const;

 private:
  QString message_;
  Size moving_vector_;
  QColor color_;
  int creation_time_;
  int life_time_;

  bool is_dead_ = false;

  const double kFontSize = 18;
  const double kSlowdownCoefficient = 0.9;
};

#endif  // VIEW_TEXT_NOTIFICATION_H_
