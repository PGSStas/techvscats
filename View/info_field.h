#ifndef VIEW_INFO_FIELD_H_
#define VIEW_INFO_FIELD_H_

#include <algorithm>
#include <QFontDatabase>
#include <QImage>
#include <QPainter>
#include <QString>

#include "animation_player.h"
#include "size_handler.h"
#include "Model/constants.h"
#include "Model/coordinate.h"
#include "Model/size.h"

class InfoField {
 public:
  void Draw(QPainter* painter, const SizeHandler& size_handler) const;

  void SetInfo(const QString& header, const QString& info, const QImage& image);

  void SetPosition(Coordinate position, Size button_size, double shift);

  void Show();
  void Hide();
  void SetShowPercent(double show_percent);

 private:
  Coordinate position_;
  bool is_showed_ = false;

  QString header_ = "HEADER";
  QString info_ = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. "
                  "Vestibulum sit amet pulvinar purus. Nullam efficitur "
                  "elementum eros pretium rhoncus. Duis nec egestas massa. "
                  "Etiam mattis, massa sed malesuada dignissim, quam orci "
                  "scelerisque orci, sed fermentum eros felis non felis. "
                  "Quisque id est eget justo tristique volutpat non ut nisl. "
                  "Vivamus quis felis ligula. Sed et volutpat tortor.";
  QImage image_;

  const Size kSize = {600, 400};
  const Size kRelativeHeaderSize = {1, 0.2};
  const Size kRelativeImageSize = {0.4, 0.75};
  const Size kRelativeTextSize = {0.6, 0.75};
};

#endif  // VIEW_INFO_FIELD_H_
