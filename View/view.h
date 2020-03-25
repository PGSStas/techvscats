#ifndef VIEW_VIEW_H_
#define VIEW_VIEW_H_

#include <QTimerEvent>
#include <QMouseEvent>
#include <QMainWindow>
#include <QPushButton>
#include <QElapsedTimer>
#include <QObject>
#include <QString>
#include <QLabel>
#include <QDebug>

#include <list>

#include "Controller/abstract_controller.h"
#include "tower_menu.h"

class View : public QMainWindow {
  Q_OBJECT

 public:
  explicit View(AbstractController* controller);
  ~View() = default;

  void EnableGameUi();
  void DisableGameUi();
  void EnableMenuUi();
  void DisableMenuWindow();

  void UpdateRounds(int current_round_number, int rounds_count);

  void ShowTowerMenu(std::shared_ptr<TowerMenu> menu);
  TowerMenu* GetTowerMenu();
  bool IsTowerMenuEnabled();
  void DisableTowerMenu();

 private:
  bool is_menu_window_enabled;
  AbstractController* controller_;
  QElapsedTimer game_time_;

  // Game window
  QLabel* wave_status_label_;
  QPushButton* start_game_button_;

  bool is_tower_menu_enabled = false;
  std::shared_ptr<TowerMenu> tower_menu_ = nullptr;

  // Menu window
  QPushButton* return_menu_button_;
  int timer_controller_id_;
  const int time_between_ticks_ = 10;

 private:
  void paintEvent(QPaintEvent* event) override;
  void timerEvent(QTimerEvent* event) override;
  void mousePressEvent(QMouseEvent* event) override;

  // Game window
  void DrawBackground(QPainter* p);
  void DrawTowers(QPainter* p);
};

#endif  // VIEW_VIEW_H_
