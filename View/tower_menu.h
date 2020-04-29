#ifndef VIEW_TOWER_MENU_H_
#define VIEW_TOWER_MENU_H_

#include <algorithm>
#include <memory>
#include <vector>

#include <QPainter>

#include "GameObject/building.h"
#include "Model/coordinate.h"
#include "View/info_field.h"
#include "View/menu_button.h"

struct ButtonImagePath {
  ButtonImagePath(const QString& frame_up_path,
                  const QString& frames_down_path) :
      main_path(frame_up_path), active_path(frames_down_path) {}
  QString main_path;
  QString active_path;
};

class TowerMenu {
 public:
  // Note: options are expected to be not empty
  explicit TowerMenu(QMainWindow*);

  void Recreate(Coordinate position, int carrier_building_index,
                const std::vector<int>& possible_buildings_id,
                int carrier_id, const SizeHandler& size_handler);
  void Tick(const SizeHandler& size_handler, int delta_time);
  void SetIsWantToReplaceToFalse();
  void RescaleButtons(const SizeHandler& size_handler);
  void DrawAdditionalInfo(QPainter* painter, const SizeHandler& size_handler,
                          const Building& instance);

  void Disable(bool is_fast_disable = true);
  int GetCarrierIndex() const;
  int GetSellectedTowerId() const;
  bool IsEnable() const;
  bool IsWantToReplace() const;

 private:
  int building_id_;
  int carrier_id_;
  std::vector<MenuButton*> buttons_;
  std::vector<int> possible_buildings_id_;
  Coordinate position_;
  int carrier_building_index_ = -1;
  int active_button_index_ = -1;
  bool want_to_replace_ = false;
  bool slow_disable = false;

  InfoField info_field_;

  double current_force_;

  const double kThrowForce = 65;
  const double kSlowCoefficient = 0.92;
  const Size kSizeOfButton = {50, 50};

 private:
  void HeTappedMe(uint button_index);
};

#endif  // VIEW_TOWER_MENU_H_
