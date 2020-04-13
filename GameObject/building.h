#ifndef GAMEOBJECT_BUILDING_H_
#define GAMEOBJECT_BUILDING_H_

#include <memory>

#include "game_object.h"
#include "effect.h"
#include "auric_field.h"

class Building : public GameObject {
 public:
  Building();
  Building(const Building& other);
  void SetParameters(int id,
                     const QColor& draw_color,
                     int max_level,
                     int action_range,
                     AuricField auric_field = AuricField(-1, -1));

  // Determines whether the point is inside the building;
  // Is used to check whether mouse press was on the building;
  // Default realization is for circle-shaped buildings.
  bool IsInside(Coordinate point) const;

  virtual void Upgrade();
  void Tick() override;

  void Draw(QPainter* painter,
            const std::shared_ptr<SizeHandler>& size_handler) const override;

  int GetId() const;
  int GetMaxLevel() const;
  int GetCurrentLevel() const;
  int GetActionRange() const;
  const AuricField& GetAuricField() const;
  Effect* GetAppliedEffect();

 private:
  AuricField auric_field_;
  Effect applied_effect_ = Effect(EffectTarget::kBuildings);

  int id_ = 0;
  int max_level_ = 0;
  int current_level_ = 0;
  int action_range_ = 75;

  // later here should be images to draw
  QColor draw_color_ = QColor("black");
};

#endif  // GAMEOBJECT_BUILDING_H_
