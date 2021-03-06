#ifndef VIEW_INFO_FIELD_H_
#define VIEW_INFO_FIELD_H_

#include <algorithm>
#include <QFontDatabase>
#include <QPixmap>
#include <QPainter>
#include <QString>
#include <utility>

#include "animation_player.h"
#include "size_handler.h"
#include "GameObject/building.h"
#include "Model/constants.h"
#include "Model/coordinate.h"
#include "Model/size.h"

class InfoField {
 public:
  void Draw(QPainter* painter, const SizeHandler& size_handler);
  void DrawCurrentTower(QPainter* painter,
                        const SizeHandler& size_handler);
  void DrawPurchasableTower(QPainter* painter,
                            const SizeHandler& size_handler,
                            const QFontMetrics& metrics);
  void DrawStatistics(QPainter* painter, const SizeHandler& size_handler,
                      double text_height);
  void DrawSellInfo(QPainter* painter, const SizeHandler& size_handler,
                    double text_height);
  void DrawImage(QPainter* painter, const SizeHandler& size_handler,
                 double field_size);

  void SetInfo(const Building& building, int total_cost,
               bool is_current_tower);
  void SetPosition(const Coordinate& position);
  Coordinate FixPosition(Size button_size);
  void SetVisible(bool is_hide);
  bool IsOnBottom() const;

 private:
  Coordinate position_;
  Coordinate true_position_;
  bool is_hidden_ = false;
  bool is_on_bottom_ = true;
  bool is_sell_info_ = false;

  QString header_;
  QString info_;
  int damage_ = 0;
  int aims_count_ = 0;
  int cost_ = 0;
  QString attack_speed_;

  bool is_current_tower_;
  bool has_image_ = false;
  Effect effect_ = Effect(EffectTarget::kBuilding);

  const double kMargin = 10;
  const Size kSize = {500, 500};
  const Size kRelativeHeaderSize = {1, 0.2};
  const Size kRelativeTextSize = {1, 0.5};
  const Size kRelativeStatisticsSize = {1.0, 0.2 / 3};
  const Size kImagePadSize = {150, 250};
};

#endif  // VIEW_INFO_FIELD_H_
