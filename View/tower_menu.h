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
  void DrawTowersAuraAndRange(QPainter* painter, const SizeHandler& size_handler,
                              const Building& instance);
  void DrawInfoField(QPainter* painter, const SizeHandler& size_handler,
                     const Building& instance);
  void Disable(bool is_fast_disable = true);
  void Hide(bool is_hidden);
  int GetCarrierIndex() const;
  int GetSellectedTowerId() const;
  bool IsEnable() const;
  bool IsWantToReplace() const;

 private:
  int carrier_id_;
  std::vector<MenuButton*> buttons_;
  std::vector<int> possible_buildings_id_;
  Coordinate position_;
  int carrier_building_index_ = -1;
  int active_button_index_ = -1;
  bool want_to_replace_ = false;
  bool slow_disable = false;
  bool is_hidden_;

  InfoField info_field_;

  double current_force_;

  const double kThrowForce = 100;
  const double kSlowCoefficient = 0.88;
  const Size kSizeOfButton = {60, 60};

 private:
  void HeTappedMe(uint button_index);
};

#endif  // VIEW_TOWER_MENU_H_
