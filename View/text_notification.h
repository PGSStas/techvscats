#ifndef VIEW_TEXT_NOTIFICATION_H_
#define VIEW_TEXT_NOTIFICATION_H_

#include <algorithm>
#include <memory>
#include <QFontDatabase>
#include <QLabel>
#include <QString>

#include "GameObject/game_object.h"
#include "size_handler.h"

class TextNotification : public GameObject {
 public:
  TextNotification(const QString& message, Coordinate start_position,
                   QColor color, int creation_time,
                   Size moving_vector = Size(0, -50), int life_time = 1000,
                   double size_change_coefficient = 1, double font_size = 18,
                   bool fade = false);
  ~TextNotification() override = default;

  void Tick(int current_time) override;
  void Draw(QPainter* painter, const SizeHandler& size_handler) const override;

  bool IsDead() const;

 private:
  QString message_;
  Size force_vector_;
  QColor color_;
  int creation_time_;
  int life_time_;
  int fade_speed_ = 3;
  double size_change_coefficient_;

  bool is_dead_ = false;
  double font_size_;
  bool is_fade_ = false;

  const double kSlowdownCoefficient = 0.85;
  const double kMaxTextSize = 40000;
  const int kFontId = 0;
};

#endif  // VIEW_TEXT_NOTIFICATION_H_
