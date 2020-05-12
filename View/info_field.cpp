#include "info_field.h"

#include <utility>

void InfoField::Draw(QPainter* painter, const SizeHandler& size_handler) const {
  if (is_hidden_) {
    return;
  }
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

  auto info_size = size_handler.GameToWindowLength(kSize.width - 2 * kMargin);
  double text_height = size_handler.WindowToGameLength(metrics.boundingRect(
      0, 0, info_size, 0, Qt::TextWordWrap, info_).height() + 2 * kMargin);
  double final_text_height = std::min(kSize.height, text_height +
      (1 - kRelativeTextSize.height) * kSize.height);

  Coordinate point = size_handler.GameToWindowCoordinate(position_);
  Size size = size_handler.GameToWindowSize({kSize.width, final_text_height});
  painter->drawRect(point.x, point.y, size.width, size.height);

  painter->setPen(Qt::white);

  size = size_handler.GameToWindowSize(
      {kSize.width * kRelativeHeaderSize.width,
       kSize.height * kRelativeHeaderSize.height});
  painter->drawText(point.x, point.y, size.width, size.height,
                    Qt::AlignCenter, header_);

  font = painter->font();
  font.setPixelSize(size_handler.GameToWindowLength(
      constants::kFontSize * 0.7));
  painter->setFont(font);

  point = size_handler.GameToWindowCoordinate({position_.x + kMargin,
                                               position_.y + kSize.height *
                                                   kRelativeHeaderSize.height});
  size = size_handler.GameToWindowSize(
      {kSize.width * kRelativeTextSize.width - 2 * kMargin,
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

  painter->restore();
}

void InfoField::DrawStatistics(QPainter* painter,
                               const SizeHandler& size_handler,
                               double text_height) const {
  painter->save();

  Coordinate point = size_handler.GameToWindowCoordinate(
      {position_.x, position_.y + kSize.height * kRelativeHeaderSize.height
          + text_height + 2 * kMargin});
  Size size = size_handler.GameToWindowSize(
      {kSize.width * kRelativeStatisticsSize.width,
       kSize.height * kRelativeStatisticsSize.height});
  painter->drawText(point.x, point.y, size.width, size.height,
                    Qt::AlignCenter, QObject::tr("Урон")
                        + ": " + QString::number(damage_) +
          ", " + QObject::tr("Количество целей") + ": " +
          QString::number(aims_count_));

  point = size_handler.GameToWindowCoordinate(
      {position_.x, position_.y + kSize.height * (kRelativeHeaderSize.height +
          kRelativeStatisticsSize.height) + text_height + 2 * kMargin});
  painter->drawText(point.x, point.y, size.width, size.height,
                    Qt::AlignCenter, QObject::tr("Стоимость") +
          ": " + QString::number(cost_));

  point = size_handler.GameToWindowCoordinate(
      {position_.x, position_.y + kSize.height * (kRelativeHeaderSize.height +
          2 * kRelativeStatisticsSize.height) + text_height + 2 * kMargin});
  painter->drawText(point.x, point.y, size.width, size.height,
                    Qt::AlignCenter, QObject::tr("Скорость атаки")
                        + ": " + attack_speed_);

  painter->restore();
}

void InfoField::DrawSellInfo(QPainter* painter,
                             const SizeHandler& size_handler,
                             double text_height) const {
  painter->save();

  Coordinate point = size_handler.GameToWindowCoordinate(
      {position_.x, position_.y + kSize.height * (kRelativeHeaderSize.height +
          kRelativeStatisticsSize.height) + text_height + 2 * kMargin});
  Size size = size_handler.GameToWindowSize(
      {kSize.width * kRelativeStatisticsSize.width,
       kSize.height * kRelativeStatisticsSize.height});
  painter->drawText(point.x, point.y, size.width, size.height,
                    Qt::AlignCenter, QObject::tr("Стоимость продажи") +
          ": " + QString::number(cost_));

  painter->restore();
}

void InfoField::DrawImage(QPainter* painter, const SizeHandler& size_handler,
                          double field_size) const {
  painter->save();
  painter->setPen(QPen(QBrush(qRgb(103, 103, 103)), 3));
  painter->setBrush(QBrush(qRgb(53, 53, 53)));

  Coordinate game_point = {position_.x - 40 - kImagePadSize.width,
                           position_.y + field_size / 2 -
                               kImagePadSize.height / 2};

  if (game_point.x < 10) {
    game_point.x = position_.x + 40 + kSize.width;
  }

  Coordinate point = size_handler.GameToWindowCoordinate(game_point);
  Size size = size_handler.GameToWindowSize(kImagePadSize);

  painter->drawRect(point.x, point.y, size.width, size.height);

  // TODO(watislaf): Draw image here.

  painter->restore();
}

void InfoField::SetInfo(const Building& building, int total_cost) {
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
}

void InfoField::SetPosition(Coordinate position, Size button_size,
                            double shift) {
  position_ = position;
  position_.x -= kSize.width / 2;
  shift += button_size.height;
  if (position_.y + kSize.height + shift >= constants::kGameHeight) {
    position_.y -= kSize.height + shift;
    is_on_bottom_ = false;
  } else {
    position_.y += shift;
    is_on_bottom_ = true;
  }

  if (position_.x + kSize.width > constants::kGameWidth) {
    position_.x = constants::kGameWidth - kSize.width - 10;
  }
  if (position_.x < 0) {
    position_.x = 0;
  }
}

void InfoField::SetVisible(bool is_hide) {
  is_hidden_ = !is_hide;
}

bool InfoField::IsOnBottom() const {
  return is_on_bottom_;
}

void InfoField::SetImage(QImage image) {
  has_image_ = true;
  image_ = std::move(image);
}

void InfoField::RemoveImage() {
  has_image_ = false;
}

