#include "info_field.h"

void InfoField::Draw(QPainter* painter, const SizeHandler& size_handler) const {
  if (!is_hidden_) {
    return;
  }
  painter->save();
  painter->setPen(QPen(QBrush(qRgb(103, 103, 103)), 3));
  painter->setBrush(QBrush(qRgb(53, 53, 53)));

  auto font = painter->font();
  font.setPixelSize(size_handler.GameToWindowLength(constants::kFontSize));
  font.setFamily(QFontDatabase::applicationFontFamilies(0).at(0));
  painter->setFont(font);

  QFontMetrics metrics(font);

  double text_height = metrics.boundingRect(0, 0, kSize.width - 2 * kMargin,
                                            kSize.height - 2 * kMargin,
                                            Qt::TextWordWrap, info_).height();
  double final_text_height = std::min(kSize.height, text_height +
      (1 - kRelativeTextSize.height) * kSize.height) + 2 * kMargin;

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
       kSize.height * kRelativeTextSize.height - 2 * kMargin});
  painter->drawText(point.x, point.y,
                    size.width, size.height, Qt::TextWordWrap, info_);

  point = size_handler.GameToWindowCoordinate(
      {position_.x, position_.y + kSize.height * kRelativeHeaderSize.height
          + text_height + 2 * kMargin});
  size = size_handler.GameToWindowSize(
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

void InfoField::Hide(bool is_hide) {
  is_hidden_ = is_hide;
}

bool InfoField::IsOnBottom() const {
  return is_on_bottom_;
}
