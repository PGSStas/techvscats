#ifndef VIEW_VIEW_H_
#define VIEW_VIEW_H_

#include <QElapsedTimer>
#include <QLabel>
#include <QMainWindow>
#include <QMouseEvent>
#include <QObject>
#include <QPushButton>
#include <QString>
#include <QTimer>
#include <QTimerEvent>

#include <list>
#include <memory>
#include <vector>

#include "Controller/abstract_controller.h"
#include "button_handler.h"
#include "tower_menu.h"

class View : public QMainWindow {
 Q_OBJECT

 public:
  explicit View(AbstractController* controller);
  ~View() override = default;

  void EnableGameUi();
  void DisableGameUi();
  void EnableMainMenuUi();
  void DisableMainMenuUi();

  void ReplaceTowerMenu(Coordinate position, int carrier_building_index,
                        const std::vector<int>& possible_buildings_id,
                        int carrier_id_);
  void DisableTowerMenu();

  void ChangeGameSpeed(Speed speed);
  const SizeHandler& GetSizeHandler() const;
  bool IsTowerMenuEnabled() const;

  int GetRealTime() const;

 private:
  AbstractController* controller_;
  SizeHandler size_handler_;
  QElapsedTimer view_timer_;


  int controller_timer_id_;

  // Game window
  QElapsedTimer time_between_ticks_;
  ButtonHandler button_handler_;
  TowerMenu tower_menu_;

  double game_speed_coefficient_ = 1;

  const QString endgame_message_ = "Restart level or go to the main menu...";
  Coordinate message_position_ = {constants::kGameWidth, 900};
  double alpha_channel_ = 0;
  double delta_alpha_ = 2;

  const Coordinate kRoundPosition = {1758, 1001};
  const Size kRoundSize = {120, 60};

 private:
  // Events
  void paintEvent(QPaintEvent*) override;
  void resizeEvent(QResizeEvent*) override;
  void timerEvent(QTimerEvent* event) override;
  void mouseReleaseEvent(QMouseEvent* event) override;
  void mousePressEvent(QMouseEvent* event) override;

  void DrawEmptyZones(QPainter* painter);
  void DrawMainMenu(QPainter* painter);
  void DrawGame(QPainter* painter);
  void DrawSettings(QPainter* painter);
  void DrawPauseMenu(QPainter* painter);
  void DrawEndgameMessage(QPainter* painter);

  // Game window
  void DrawTowersAuraAndRange(QPainter* painter);
  void DrawEnemies(QPainter* painter);
  void DrawProjectiles(QPainter* painter);
  void DrawTowers(QPainter* painter);
  void DrawParticles(QPainter* painter);
  void DrawBars(QPainter* painter);
  void DrawAdditionalInfo(QPainter* painter);
  void DrawRoundInfo(QPainter* painter);
};

#endif  // VIEW_VIEW_H_
