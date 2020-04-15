#ifndef VIEW_VIEW_H_
#define VIEW_VIEW_H_

#include <list>
#include <memory>

#include <QElapsedTimer>
#include <QLabel>
#include <QMainWindow>
#include <QMouseEvent>
#include <QObject>
#include <QPushButton>
#include <QString>
#include <QTimerEvent>

#include "Controller/abstract_controller.h"
#include "size_handler.h"
#include "tower_menu.h"

enum class WindowType {
  kMainMenu,
  kGame
};

class View : public QMainWindow {
 Q_OBJECT

 public:
  explicit View(AbstractController* controller);

  void EnableGameUi();
  void EnableMenuUi();
  void DisableGameUi();
  void DisableMenuWindow();

  void ShowTowerMenu(const std::shared_ptr<TowerMenu>& menu);
  void UpdateRounds(int current_round_number, int number_of_rounds);

  std::shared_ptr<TowerMenu> GetTowerMenu();
  bool IsTowerMenuEnabled() const;
  void DisableTowerMenu();

 private:
  AbstractController* controller_;
  SizeHandler size_handler_;
  WindowType window_type_ = WindowType::kMainMenu;
  QElapsedTimer view_timer_;
  int controller_timer_id_;

  // Game window
  QElapsedTimer time_between_ticks_;
  QPushButton* start_game_button_;
  QLabel* wave_status_label_;
  std::shared_ptr<TowerMenu> tower_menu_ = nullptr;
  bool is_tower_menu_enabled_ = false;
  double game_speed_coefficient_ = 1;

  // Menu window
  QPushButton* return_menu_button_;

 private:
  void DrawWindow(QPainter* painter, const QBrush& brush);
  // Events
  void paintEvent(QPaintEvent*) override;
  void resizeEvent(QResizeEvent*) override;
  void timerEvent(QTimerEvent* event) override;
  void mouseReleaseEvent(QMouseEvent* event) override;
  void mouseMoveEvent(QMouseEvent* event) override;
  // Game window
  void DrawBackground(QPainter* painter);
  void DrawAuras(QPainter* painter);
  void DrawEnemies(QPainter* painter);
  void DrawProjectiles(QPainter* painter);
  void DrawTowers(QPainter* painter);
  void DrawInterface(QPainter* painter);
};

#endif  // VIEW_VIEW_H_
