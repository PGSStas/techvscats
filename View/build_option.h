#ifndef BUILD_OPTION_H
#define BUILD_OPTION_H

#include <memory>

#include "GameObject/building.h"
#include "tower_menu_option.h"

class BuildOption : public TowerMenuOption {
 public:
  explicit BuildOption(const Building& tower_to_build_);

  void Draw(QPainter* p, Coordinate pos) override;

 private:
  const Building& tower_to_build_;
};

#endif //BUILD_OPTION_H
