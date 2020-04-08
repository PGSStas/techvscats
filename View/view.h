#ifndef VIEW_VIEW_H_
#define VIEW_VIEW_H_

#include <QTimerEvent>
#include <QMouseEvent>
#include <QMainWindow>
#include <QPushButton>
#include <QElapsedTimer>
#include <QLabel>
#include <QObject>
#include <QString>
#include <memory>
#include <list>

#include "Controller/abstract_controller.h"
#include "tower_menu.h"
#include "size_handler.h"

enum class WindowType {
  kMainMenu,
  kGame
};

class View : public QMainWindow {
 Q_OBJECT

 public:
  explicit View(AbstractController* controller);
  ~View() = default;

  void EnableGameUi();
  void DisableGameUi();
  void EnableMenuUi();
  void DisableMenuWindow();

  void UpdateRounds(int current_round_number, int number_of_rounds);

  void ShowTowerMenu(const std::shared_ptr<TowerMenu>& menu);
  std::shared_ptr<TowerMenu> GetTowerMenu();
  bool IsTowerMenuEnabled() const;
  void DisableTowerMenu();

 private:
  WindowType window_type_;
  AbstractController* controller_;
  SizeHandler size_handler_;
  QElapsedTimer game_time_;

  // Game window
  QLabel* wave_status_label_;
  QPushButton* start_game_button_;

  bool is_tower_menu_enabled_ = false;
  std::shared_ptr<TowerMenu> tower_menu_ = nullptr;

  // Menu window
  QPushButton* return_menu_button_;
  int controller_timer_id_;
  const int kTimeBetweenTicks_ = 10;

 private:
  void paintEvent(QPaintEvent*) override;
  void timerEvent(QTimerEvent* event) override;
  void resizeEvent(QResizeEvent*) override;
  void mouseReleaseEvent(QMouseEvent* event) override;
  void mouseMoveEvent(QMouseEvent* event) override;

  void DrawWindow(QPainter* painter, const QBrush& brush);

  // Game window
  void DrawBackground(QPainter* painter);
  void DrawTowers(QPainter* painter);
  void DrawEnemies(QPainter* painter);
  void DrawProjectiles(QPainter* painter);
};

#endif  // VIEW_VIEW_H_
