#ifndef GAMEOBJECT_AURIC_FIELD_H_
#define GAMEOBJECT_AURIC_FIELD_H_

#include <memory>
#include "game_object.h"
#include "Model/coordinate.h"

class AuricField {
 public:
  AuricField() = default;

  void SetParameters(double effect_radius, int effect_id);
  void SetCarrierCoordinate(Coordinate* carrier_coordinates);

  int GetEffectId() const;

  void Draw(QPainter* painter,
            std::shared_ptr<SizeHandler> size_handler) const;

  bool IsInRadius(const Coordinate& coordinate) const;;
  bool IsValid() const;

 private:
  double effect_radius_;
  int effect_id_;
  Coordinate* carrier_coordinates_;
};

#endif  // GAMEOBJECT_AURIC_FIELD_H_
