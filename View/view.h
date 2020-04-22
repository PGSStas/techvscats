#ifndef VIEW_VIEW_H_
#define VIEW_VIEW_H_

#include <QTimerEvent>
#include <QTimer>
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
#include "button_handler.h"

class View : public QMainWindow {
  Q_OBJECT

 public:
  explicit View(AbstractController* controller);
  ~View() override = default;
  void EnableGameUi();
  void DisableGameUi();
  void EnableMainMenuUi();
  void DisableMainMenuUi();

  void ShowTowerMenu(const std::shared_ptr<TowerMenu>& menu);
  void UpdateRounds(int current_round_number, int number_of_rounds);

  void ChangeGameSpeed(Speed speed);
  std::shared_ptr<TowerMenu> GetTowerMenu();
  bool IsTowerMenuEnabled() const;
  void DisableTowerMenu();

 private:
  AbstractController* controller_;
  SizeHandler size_handler_;
  // WindowType window_type_ = WindowType::kMainMenu;
  QElapsedTimer view_timer_;
  int controller_timer_id_;

  // Game window
  QElapsedTimer time_between_ticks_;
  std::shared_ptr<ButtonHandler> button_handler_;

  std::shared_ptr<TowerMenu> tower_menu_ = nullptr;
  bool is_tower_menu_enabled_ = false;
  double game_speed_coefficient_ = 1;

 private:
  // Events
  void paintEvent(QPaintEvent*) override;
  void resizeEvent(QResizeEvent*) override;
  void timerEvent(QTimerEvent* event) override;
  void mouseReleaseEvent(QMouseEvent* event) override;
  void mouseMoveEvent(QMouseEvent* event) override;

  void DrawMainMenu(QPainter* painter);
  void DrawGame(QPainter* painter);
  void DrawSettings(QPainter* painter);
  void DrawPauseMenu(QPainter* painter);

  // Game window
  void DrawAuras(QPainter* painter);
  void DrawEnemies(QPainter* painter);
  void DrawProjectiles(QPainter* painter);
  void DrawTowers(QPainter* painter);
  void DrawInterface(QPainter* painter);
};

#endif  // VIEW_VIEW_H_
