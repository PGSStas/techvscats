#include "info_field.h"

void InfoField::Draw(QPainter* painter, const SizeHandler& size_handler) {
  painter->save();
  painter->setPen(QPen(QBrush(qRgb(103, 103, 103)), 3));
  painter->setBrush(QBrush(qRgb(53, 53, 53)));

  auto font = painter->font();
  font.setFamily(QFontDatabase::applicationFontFamilies(0).at(0));
  font.setPixelSize(size_handler.GameToWindowLength(
      constants::kFontSize * 0.7));
  QFontMetrics metrics(font);
  font.setPixelSize(size_handler.GameToWindowLength(constants::kFontSize));
  painter->setFont(font);

  if (is_current_tower_) {
    DrawCurrentTower(painter, size_handler);
  } else {
    DrawPurchasableTower(painter, size_handler, metrics);
  }

  painter->restore();
}

void InfoField::DrawCurrentTower(QPainter* painter,
                                 const SizeHandler& size_handler) {
  int speed_percent = std::round(effect_.GetMoveSpeedCoefficient() * 100) - 100;
  int rate_percent = std::round(effect_.GetAttackRateCoefficient() * 100) - 100;
  int range_percent = std::round(effect_.GetRangeCoefficient() * 100) - 100;

  int valid_effects = 0;
  if (speed_percent != 0) {
    valid_effects++;
  }
  if (rate_percent != 0) {
    valid_effects++;
  }
  if (range_percent != 0) {
    valid_effects++;
  }

  Size true_size = {kSize.width, kSize.height *
      ((3 + valid_effects) * kRelativeStatisticsSize.height +
          kRelativeHeaderSize.height) + 4 * kMargin};
  Size size = size_handler.GameToWindowSize(true_size);
  true_position_ = FixPosition(true_size);
  Coordinate point = size_handler.GameToWindowCoordinate(true_position_);

  if (is_hidden_ || (is_current_tower_ && is_sell_info_)) {
    return;
  }

  painter->drawRect(point.x, point.y, size.width, size.height);

  painter->setPen(Qt::white);

  size = size_handler.GameToWindowSize(
      {kSize.width * kRelativeHeaderSize.width,
       kSize.height * kRelativeHeaderSize.height});
  painter->drawText(point.x, point.y, size.width, size.height,
                    Qt::AlignCenter, header_);

  auto font = painter->font();
  font.setPixelSize(size_handler.GameToWindowLength(
      constants::kFontSize * 0.7));
  painter->setFont(font);

  point = size_handler.GameToWindowCoordinate(
      {true_position_.x, true_position_.y +
          kSize.height * kRelativeHeaderSize.height});
  size = size_handler.GameToWindowSize(
      {kSize.width * kRelativeStatisticsSize.width,
       kSize.height * kRelativeStatisticsSize.height});

  double shift = 0;
  QString sign;
  if (speed_percent != 0) {
    if (speed_percent > 0) {
      sign = "+";
    } else {
      sign = "-";
    }
    painter->drawText(point.x, point.y, size.width, size.height,
                      Qt::AlignCenter,
                      QObject::tr("Bullet speed bonus") + ": " +
                          sign + QString::number(speed_percent) + "%");
    shift += kSize.height * kRelativeStatisticsSize.height;
  }

  point = size_handler.GameToWindowCoordinate(
      {true_position_.x, true_position_.y +
          kSize.height * kRelativeHeaderSize.height + shift});

  if (rate_percent != 0) {
    if (rate_percent > 0) {
      sign = "+";
    } else {
      sign = "-";
    }
    painter->drawText(point.x, point.y, size.width, size.height,
                      Qt::AlignCenter,
                      QObject::tr("Attack rate bonus") + ": " +
                          sign + QString::number(rate_percent) + "%");
    shift += kSize.height * kRelativeStatisticsSize.height;
  }

  point = size_handler.GameToWindowCoordinate(
      {true_position_.x, true_position_.y +
          kSize.height * kRelativeHeaderSize.height + shift});

  if (range_percent != 0) {
    if (range_percent > 0) {
      sign = "+";
    } else {
      sign = "-";
    }
    painter->drawText(point.x, point.y, size.width, size.height,
                      Qt::AlignCenter,
                      QObject::tr("Attack range bonus") + ": " +
                          sign + QString::number(range_percent) + "%");
  }

  DrawStatistics(painter, size_handler, shift);
}

void InfoField::DrawPurchasableTower(QPainter* painter,
                                     const SizeHandler& size_handler,
                                     const QFontMetrics& metrics) {
  auto info_size = size_handler.GameToWindowLength(kSize.width - 4 * kMargin);
  double text_height = size_handler.WindowToGameLength(metrics.boundingRect(
      0, 0, info_size, 0, Qt::TextWordWrap, info_).height() + 2 * kMargin);
  double final_text_height = std::min(kSize.height, text_height +
      (1 - kRelativeTextSize.height) * kSize.height);

  true_position_ = FixPosition({kSize.width, final_text_height});
  Coordinate point = size_handler.GameToWindowCoordinate(true_position_);
  Size size = size_handler.GameToWindowSize({kSize.width, final_text_height});

  if (is_hidden_ || (is_current_tower_ && is_sell_info_)) {
    return;
  }

  painter->drawRect(point.x, point.y, size.width, size.height);

  painter->setPen(Qt::white);

  size = size_handler.GameToWindowSize(
      {kSize.width * kRelativeHeaderSize.width,
       kSize.height * kRelativeHeaderSize.height});
  painter->drawText(point.x, point.y, size.width, size.height,
                    Qt::AlignCenter, header_);

  auto font = painter->font();
  font.setPixelSize(size_handler.GameToWindowLength(
      constants::kFontSize * 0.7));
  painter->setFont(font);

  point = size_handler.GameToWindowCoordinate({true_position_.x + 2 * kMargin,
                                               true_position_.y + kSize.height *
                                                   kRelativeHeaderSize.height});
  size = size_handler.GameToWindowSize(
      {kSize.width * kRelativeTextSize.width - 4 * kMargin,
       text_height - 2 * kMargin});
  painter->drawText(point.x, point.y,
                    size.width, size.height, Qt::TextWordWrap, info_);

  if (is_sell_info_) {
    DrawSellInfo(painter, size_handler, text_height);
  } else {
    DrawStatistics(painter, size_handler, text_height);
  }

  if (has_image_) {
    DrawImage(painter, size_handler, final_text_height);
  }
}

void InfoField::DrawStatistics(QPainter* painter,
                               const SizeHandler& size_handler,
                               double text_height) {
  painter->save();

  Coordinate point = size_handler.GameToWindowCoordinate(
      {true_position_.x, true_position_.y +
          kSize.height * kRelativeHeaderSize.height
          + text_height + 2 * kMargin});
  Size size = size_handler.GameToWindowSize(
      {kSize.width * kRelativeStatisticsSize.width,
       kSize.height * kRelativeStatisticsSize.height});
  if (aims_count_ != 0) {
    painter->drawText(point.x, point.y, size.width, size.height,
                      Qt::AlignCenter, QObject::tr("Damage")
                          + ": " + QString::number(damage_) +
            ", " + QObject::tr("Number of target") + ": " +
            QString::number(aims_count_));
  }

  point = size_handler.GameToWindowCoordinate(
      {true_position_.x, true_position_.y +
          kSize.height * (kRelativeHeaderSize.height +
              kRelativeStatisticsSize.height) + text_height + 2 * kMargin});
  painter->drawText(point.x, point.y, size.width, size.height,
                    Qt::AlignCenter, QObject::tr("Сost") +
          ": " + QString::number(cost_));

  if (aims_count_ != 0) {
    point = size_handler.GameToWindowCoordinate(
        {true_position_.x, true_position_.y +
            kSize.height * (kRelativeHeaderSize.height +
                2 * kRelativeStatisticsSize.height) + text_height
            + 2 * kMargin});
    painter->drawText(point.x, point.y, size.width, size.height,
                      Qt::AlignCenter, QObject::tr("Attack speed")
                          + ": " + attack_speed_);
  }

  painter->restore();
}

void InfoField::DrawSellInfo(QPainter* painter,
                             const SizeHandler& size_handler,
                             double text_height) {
  painter->save();

  Coordinate point = size_handler.GameToWindowCoordinate(
      {true_position_.x, true_position_.y +
          kSize.height * (kRelativeHeaderSize.height +
              kRelativeStatisticsSize.height) + text_height + 2 * kMargin});
  Size size = size_handler.GameToWindowSize(
      {kSize.width * kRelativeStatisticsSize.width,
       kSize.height * kRelativeStatisticsSize.height});
  painter->drawText(point.x, point.y, size.width, size.height,
                    Qt::AlignCenter, QObject::tr("Sell cost") +
          ": " + QString::number(cost_));

  painter->restore();
}

void InfoField::DrawImage(QPainter* painter, const SizeHandler& size_handler,
                          double field_size) {
  painter->save();
  painter->setPen(QPen(QBrush(qRgb(103, 103, 103)), 3));
  painter->setBrush(QBrush(qRgb(53, 53, 53)));

  Coordinate game_point = {true_position_.x - 40 - kImagePadSize.width,
                           true_position_.y + field_size / 2 -
                               kImagePadSize.height / 2};

  if (game_point.x < 10) {
    game_point.x = true_position_.x + 40 + kSize.width;
  }

  Coordinate point = size_handler.GameToWindowCoordinate(game_point);
  Size size = size_handler.GameToWindowSize(kImagePadSize);

  painter->drawRect(point.x, point.y, size.width, size.height);

  // TODO(watislaf): Draw image here.

  painter->restore();
}

void InfoField::SetInfo(const Building& building, int total_cost,
                        bool is_current_tower) {
  is_current_tower_ = is_current_tower;
  effect_ = building.GetEffect();
  header_ = building.GetHeader();
  info_ = building.GetDescription();
  damage_ = building.GetDamage();
  aims_count_ = building.GetMaxAims();
  if (building.GetId() == 0) {
    is_sell_info_ = true;
    cost_ = total_cost * constants::kRefundCoefficient;
  } else {
    is_sell_info_ = false;
    cost_ = building.GetCost();
  }

  int reload_time = building.GetReloadTime();
  if (reload_time < 500) {
    attack_speed_ = QObject::tr("Very fast");
  } else if (reload_time < 3000) {
    attack_speed_ = QObject::tr("Medium");
  } else {
    attack_speed_ = QObject::tr("Slow");
  }
}

void InfoField::SetPosition(const Coordinate& position) {
  position_ = position;
}

Coordinate InfoField::FixPosition(Size field_size) {
  Coordinate position = position_;
  position.x -= field_size.width / 2;
  double shift = 2 * kMargin;
  is_on_bottom_ = IsOnBottom();
  if (!is_on_bottom_) {
    position.y -= field_size.height + shift;
  } else {
    position.y += shift;
  }

  if (position.x + field_size.width > constants::kGameWidth) {
    position.x = constants::kGameWidth - field_size.width - shift;
  }
  if (position.x < 0) {
    position.x = shift;
  }

  return position;
}

void InfoField::SetVisible(bool is_hide) {
  is_hidden_ = !is_hide;
}

bool InfoField::IsOnBottom() const {
  return position_.y + kSize.height + 2 * kMargin < constants::kGameHeight;
}
