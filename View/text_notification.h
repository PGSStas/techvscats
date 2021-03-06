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
  TextNotification(QString  message, Coordinate start_position,
                   QColor color, Size moving_vector = Size(0, -50),
                   int life_time = 1000, double size_change_coefficient = 1,
                   bool fade = false, bool is_accelerated = true,
                   bool center_align = true);
  ~TextNotification() override = default;

  void Tick(int current_time) override;
  void Draw(QPainter* painter, const SizeHandler& size_handler) const override;

  bool IsDead() const;

  void SetFontSize(int new_size);

 private:
  QString message_;
  Size force_vector_;
  QColor color_;
  int life_time_;
  int fade_speed_ = 3;
  double size_change_coefficient_;

  bool is_dead_ = false;
  double font_size_ = 18;
  bool is_fade_ = false;
  bool is_accelerated_ = true;
  bool center_align_ = true;

  const double kSlowdownCoefficient = 0.85;
  const double kMaxTextSize = 40000;
  const int kFontId = 0;
};

#endif  // VIEW_TEXT_NOTIFICATION_H_
