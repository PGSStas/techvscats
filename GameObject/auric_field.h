#ifndef GAMEOBJECT_AURIC_FIELD_H_
#define GAMEOBJECT_AURIC_FIELD_H_

#include <memory>
#include <QPainter>

#include "View/size_handler.h"
#include "Model/coordinate.h"

class AuricField {
 public:
  explicit AuricField(double effect_radius = -1, int effect_id = -1);
  void SetCarrierCoordinate(Coordinate* carrier_coordinates);

  int GetEffectId() const;

  void Draw(QPainter* painter,
            std::shared_ptr<SizeHandler> size_handler) const;

  bool IsInRadius(const Coordinate& coordinate) const;
  bool IsValid() const;

 private:
  double effect_radius_ = -1;
  int effect_id_ = -1;
  Coordinate* carrier_coordinate_;
};

#endif  // GAMEOBJECT_AURIC_FIELD_H_
