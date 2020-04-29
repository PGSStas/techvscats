//
// Created by Стас - Не Админ on 29.04.2020.
//

#include "info_field.h"

void InfoField::Draw(QPainter* painter, const SizeHandler& size_handler) const {
  painter->save();
  painter->setPen(QPen(qRgb(103, 103, 103)));
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

  point = size_handler.GameToWindowCoordinate({position_.x + 3, position_.y +
      kSize.height * kRelativeHeaderSize.height + 3});
  size = size_handler.GameToWindowSize(
      {kSize.width * kRelativeImageSize.width,
       kSize.height * kRelativeImageSize.height});
  if (std::abs(image_.width() - size.width) > constants::kEpsilon) {
    image_.scaled(size.width, size.height);
  }
  painter->drawImage(point.x, point.y, image_);

  font = painter->font();
  font.setPixelSize(size_handler.GameToWindowLength(
      constants::kFontSize * 0.7 ));
  painter->setFont(font);

  point = size_handler.GameToWindowCoordinate({position_.x + kSize.width
      * kRelativeImageSize.width, position_.y +
      kSize.height * kRelativeHeaderSize.height});
  size = size_handler.GameToWindowSize(
      {kSize.width * kRelativeTextSize.width,
       kSize.height * kRelativeTextSize.height});
  painter->drawText(point.x, point.y,
                    size.width, size.height, Qt::TextWordWrap, info_);

  painter->restore();
}

void InfoField::SetInfo(const QString& header, const QString& info,
                        const QImage& image) {
  header_ = header;
  info_ = info;
  image_ = image;
}

void InfoField::SetPosition(Coordinate position,
                            Size button_size,
                            double shift) {
  position_ = position;
  if (position_.x + kSize.width >= constants::kGameWidth) {
    position_.x -= kSize.width + shift;
  } else {
    position_.x += button_size.width + shift;
  }
  if (position_.y + kSize.height >= constants::kGameHeight) {
    position_.y -= kSize.height + shift;
  } else {
    position.y += button_size.height + shift;
  }
}

void InfoField::Show() {
  is_showed_ = true;
}

void InfoField::Hide() {
  is_showed_ = false;
}
