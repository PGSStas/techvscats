#ifndef VIEW_INFO_FIELD_H_
#define VIEW_INFO_FIELD_H_

#include <algorithm>
#include <QFontDatabase>
#include <QImage>
#include <QPainter>
#include <QString>

#include "animation_player.h"
#include "size_handler.h"
#include "GameObject/building.h"
#include "Model/constants.h"
#include "Model/coordinate.h"
#include "Model/size.h"

class InfoField {
 public:
  void Draw(QPainter* painter, const SizeHandler& size_handler) const;

  void SetInfo(const Building& building);
  void SetPosition(Coordinate position, Size button_size, double shift);
  void Hide(bool is_hide);

  bool IsOnBottom() const;

 private:
  Coordinate position_;
  bool is_hidden_ = false;
  bool is_on_bottom_ = true;

  QString header_;
  QString info_;
  int damage_ = 0;
  int aims_count_ = 0;
  int cost_ = 0;
  QString attack_speed_;

  const double kMargin = 10;
  const Size kSize = {500, 300};
  const Size kRelativeHeaderSize = {1, 0.2};
  const Size kRelativeTextSize = {1, 0.5};
  const Size kRelativeStatisticsSize = {1.0, 0.1};
};

#endif  // VIEW_INFO_FIELD_H_
