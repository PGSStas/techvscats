#ifndef GAMEOBJECT_AURIC_FIELD_H_
#define GAMEOBJECT_AURIC_FIELD_H_

#include <memory>
#include <QPainter>

#include "View/size_handler.h"
#include "Model/coordinate.h"

class AuricField {
 public:
  void SetParameters(double effect_radius, int effect_id);
  void SetCarrierCoordinate(Coordinate* carrier_coordinates);

  int GetEffectId() const;

  void Draw(QPainter* painter,
            std::shared_ptr<SizeHandler> size_handler) const;

  bool IsInRadius(const Coordinate& coordinate) const;;
  bool IsValid() const;

 private:
  double effect_radius_ = -1;
  int effect_id_ = -1;
  Coordinate* carrier_coordinates_;
};

#endif  // GAMEOBJECT_AURIC_FIELD_H_
