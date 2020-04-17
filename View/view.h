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
#include <QDebug>
#include <QTimerEvent>

#include <memory>
#include <list>

#include "Controller/abstract_controller.h"
#include "tower_menu.h"
#include "button_handler.h"

class View : public QMainWindow {
  Q_OBJECT

 public:
  explicit View(AbstractController* controller);

  void EnableGameUi();
  void DisableGameUi();
  void EnableMainMenuUi();
  void DisableMainMenuUi();

  void ShowTowerMenu(const std::shared_ptr<TowerMenu>& menu);
  void UpdateRounds(int current_round_number, int number_of_rounds);

  std::shared_ptr<TowerMenu> GetTowerMenu();
  bool IsTowerMenuEnabled() const;
  void DisableTowerMenu();

 private:
  // WindowType window_type_;
  AbstractController* controller_;
  std::shared_ptr<SizeHandler> size_handler_;
  QElapsedTimer view_timer_;
  QElapsedTimer time_between_ticks_;
  std::shared_ptr<ButtonHandler> button_handler_;

  std::shared_ptr<TowerMenu> tower_menu_ = nullptr;

  int controller_timer_id_;
  const int kTimeBetweenTicks_ = 10;
  bool is_tower_menu_enabled_ = false;
  double game_speed_coefficient_ = 1;

 private:
  void DrawWindow(QPainter* painter, const QBrush& brush);
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
  void DrawBackground(QPainter* painter);
  void DrawAuras(QPainter* painter);
  void DrawEnemies(QPainter* painter);
  void DrawProjectiles(QPainter* painter);
  void DrawTowers(QPainter* painter);
  void DrawInterface(QPainter* painter);
};

#endif  // VIEW_VIEW_H_
