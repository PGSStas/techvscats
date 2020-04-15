#ifndef GAMEOBJECT_AURIC_FIELD_H_
#define GAMEOBJECT_AURIC_FIELD_H_

#include <memory>
#include <QPainter>

#include "Model/coordinate.h"
#include "View/size_handler.h"

class AuricField {
 public:
  explicit AuricField(double effect_radius = -1, int effect_id = -1);

  void Draw(QPainter* painter,
            const SizeHandler& size_handler) const;

  void SetCarrierCoordinate(Coordinate* carrier_coordinates);
  bool IsInRadius(const Coordinate& coordinate) const;
  int GetEffectId() const;
  bool IsValid() const;

 private:
  double effect_radius_;
  int effect_id_;
  Coordinate* carrier_coordinate_ = nullptr;
};

#endif  // GAMEOBJECT_AURIC_FIELD_H_
