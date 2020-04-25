#ifndef GAMEOBJECT_AURIC_FIELD_H_
#define GAMEOBJECT_AURIC_FIELD_H_

#include <memory>
#include <QPainter>

#include "Model/constants.h"
#include "Model/coordinate.h"
#include "View/size_handler.h"

class AuricField {
 public:
  explicit AuricField(double effect_radius = -1, int effect_id = -1);

  void Draw(QPainter* painter, const SizeHandler& size_handler,
            Coordinate position = {-1000, -1000}) const;

  void SetCarrierCoordinate(Coordinate* carrier_coordinates);
  int GetEffectId() const;
  bool IsInRadius(const Coordinate& coordinate) const;
  bool IsValid() const;

 private:
  double effect_radius_;
  int effect_id_;
  Coordinate* carrier_coordinate_ = nullptr;
};

#endif  // GAMEOBJECT_AURIC_FIELD_H_
