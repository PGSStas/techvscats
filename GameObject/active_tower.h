#ifndef GAMEOBJECT_ACTIVE_TOWER_H_
#define GAMEOBJECT_ACTIVE_TOWER_H_

#include <memory>
#include "building.h"

class ActiveTower : public Building {
 public:
  explicit ActiveTower(const std::list<std::shared_ptr<Enemy>>&,
                       int max_aims_count);
  explicit ActiveTower(const std::shared_ptr<const Building>& other);
  void Tick(int controller_current_time) override;
  void UpdateAim() override;
  void DoAction() override;
 private:
  int max_aims_ = 1;
};

#endif  // GAMEOBJECT_ACTIVE_TOWER_H_
