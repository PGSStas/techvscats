//
// Created by Стас - Не Админ on 29.04.2020.
//

#include "info_field.h"

void InfoField::Draw(QPainter* painter, const SizeHandler& size_handler) const {
  if (!is_showed_) {
    return;
  }
  painter->save();
  painter->setPen(QPen(QBrush(qRgb(103, 103, 103)), 3));
  painter->setBrush(QBrush(qRgb(53, 53, 53)));

  Coordinate point = size_handler.GameToWindowCoordinate(position_);
  Size size = size_handler.GameToWindowSize(kSize);
  painter->drawRect(point.x, point.y, size.width, size.height);

  auto font = painter->font();
  font.setPixelSize(size_handler.GameToWindowLength(
      constants::kFontSize));
  font.setFamily(QFontDatabase::applicationFontFamilies(0).at(0));
  painter->setFont(font);
  painter->setPen(Qt::white);

  size = size_handler.GameToWindowSize(
      {kSize.width * kRelativeHeaderSize.width,
       kSize.height * kRelativeHeaderSize.height});
  painter->drawText(point.x, point.y,
                    size.width, size.height, Qt::AlignCenter, header_);

  font = painter->font();
  font.setPixelSize(size_handler.GameToWindowLength(
      constants::kFontSize * 0.7));
  painter->setFont(font);

  point = size_handler.GameToWindowCoordinate({position_.x + kMargin,
                                               position_.y + kSize.height *
                                                   kRelativeHeaderSize.height});
  size = size_handler.GameToWindowSize(
      {kSize.width * kRelativeTextSize.width - 2 * kMargin,
       kSize.height * kRelativeTextSize.height - 2 * kMargin});
  painter->drawText(point.x, point.y,
                    size.width, size.height, Qt::TextWordWrap, info_);

  point = size_handler.GameToWindowCoordinate(
      {position_.x, position_.y + kSize.height *
          (kRelativeHeaderSize.height + kRelativeTextSize.height)});
  size = size_handler.GameToWindowSize(
      {kSize.width * kRelativeStatisticsSize.width,
       kSize.height * kRelativeStatisticsSize.height});
  painter->drawText(point.x, point.y, size.width, size.height,
                    Qt::AlignCenter, "Урон: " + QString::number(damage_) +
          ", Количество целей: " + QString::number(aims_count_));

  point = size_handler.GameToWindowCoordinate(
      {position_.x, position_.y + kSize.height *
          (kRelativeHeaderSize.height + kRelativeTextSize.height +
              kRelativeStatisticsSize.height)});
  painter->drawText(point.x, point.y, size.width, size.height,
                    Qt::AlignCenter, "Стоимость: " + QString::number(cost_) +
          ", Скорость атаки: " + attack_speed_);

  painter->restore();
}

void InfoField::SetInfo(const Building& building) {
  header_ = building.GetHeader();
  info_ = building.GetDescription();
  cost_ = building.GetCost();
  damage_ = building.GetDamage();
  aims_count_ = building.GetMaxAims();
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
}

void InfoField::Show() {
  is_showed_ = true;
}

void InfoField::Hide() {
  is_showed_ = false;
}

bool InfoField::IsOnBottom() const {
  return is_on_bottom_;
}
