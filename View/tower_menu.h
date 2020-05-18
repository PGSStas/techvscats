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
  ButtonImagePath(const QString& frame_up_path, const QString& frames_down_path)
      : main_path(frame_up_path), active_path(frames_down_path) {}
  QString main_path;
  QString active_path;
};

class TowerMenu {
 public:
  // Note: options are expected to be not empty
  explicit TowerMenu(QMainWindow*);

  void Recreate(Coordinate position, int owner_building_index,
                const std::vector<int>& possible_buildings_id,
                int owner_id, const SizeHandler& size_handler,
                int total_cost);
  void Tick(const SizeHandler& size_handler);
  void SetIsWantToReplaceToFalse();
  void RescaleButtons(const SizeHandler& size_handler);
  void DrawTowersAuraAndRange(QPainter* painter,
                              const SizeHandler& size_handler,
                              const Building& instance);
  void DrawInfoField(QPainter* painter, const SizeHandler& size_handler,
                     const Building& instance);
  void Close();
  void Hide(bool is_hidden);
  int GetTownerIndex() const;
  int GetSellectedTowerId() const;
  bool IsEnable() const;
  bool IsWantToReplace() const;

  int GetChosenButtonId() const;

 private:
  int owner_id_ = 0;
  std::vector<MenuButton*> buttons_;
  std::vector<int> possible_buildings_id_;
  Coordinate position_{};
  int owner_building_index_ = -1;
  int active_button_index_ = -1;
  bool id_to_replace_ = false;
  bool slow_disable = false;
  bool is_hidden_ = true;
  int total_cost_ = 0;

  InfoField info_field_{};

  double current_force_ = 0;

#ifndef Q_OS_ANDROID
  const double kThrowForce = 18;
#else
  const double kThrowForce = 24;
#endif
  const double kSlowdownCoefficient = 0.86;
  const Size kSizeOfButton = button_constants::kShortButtonSize * 0.8;

 private:
  void Disable();
  void ButtonTapped(int button_index);
};

#endif  // VIEW_TOWER_MENU_H_
