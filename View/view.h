#ifndef VIEW_VIEW_H_
#define VIEW_VIEW_H_

#include <algorithm>
#include <QElapsedTimer>
#include <QLabel>
#include <QMainWindow>
#include <QMouseEvent>
#include <QObject>
#include <QPushButton>
#include <QString>
#include <QSplashScreen>
#include <QTimer>
#include <QTimerEvent>

#include <list>
#include <memory>
#include <vector>

#include "Controller/abstract_controller.h"
#include "global_chat.h"
#include "button_handler.h"
#include "tower_menu.h"

class View : public QMainWindow {
  Q_OBJECT

 public:
  explicit View(AbstractController* controller);
  ~View() override = default;

  void SecondConstructorPart();
  void EnableGameUi();
  void DisableGameUi();
  void EnableMainMenuUi();
  void DisableMainMenuUi();
  void ChangeChatStyle();

  void AddGlobalChatMessage(const QStringList& message);

  void ReplaceTowerMenu(Coordinate position, int carrier_building_index,
                        const std::vector<int>& possible_buildings_id,
                        int carrier_id_, int total_cost);
  void DisableTowerMenu();
  bool IsTowerMenuEnabled() const;

  void ChangeGameSpeed(Speed speed, bool im_the_button = false);

  int GetRealTime() const;

  int GetChosenLevel() const;
  void SetChosenLevel(int level);

  void StartTitles();
  void EndTitles();
  void ShowSettingsButton();
  void ShowNextLevelButton();
  void BeginNextLevel();
  bool IsLastLevel();

 private:
  AbstractController* controller_;
  SizeHandler size_handler_;
  QElapsedTimer view_timer_;
  WindowType window_type_ = WindowType::kMainMenu;

  int controller_timer_id_;

  // Main Ui
  std::shared_ptr<ButtonHandler> button_handler_;
  std::shared_ptr<GlobalChat> global_chat_;
  // Game window
  QElapsedTimer time_between_ticks_;
  TowerMenu tower_menu_;

  double game_speed_coefficient_ = 1;

  const QString kEndgameMessage = tr("Restart level or go to the main menu");
  Coordinate message_position_ = {constants::kGameWidth / 2, 900};
  double alpha_channel_ = 0;
  double delta_alpha_ = 2;

  const Coordinate kRoundPosition = {1758, 1001};
  const Size kRoundSize = {120, 60};

  QImage logo_ = QImage(":resources/images/backgrounds/logo.png");
  bool is_model_loaded_ = false;

 private:
  // Events
  void paintEvent(QPaintEvent*) override;
  void resizeEvent(QResizeEvent*) override;
  void timerEvent(QTimerEvent* event) override;
  void mouseReleaseEvent(QMouseEvent* event) override;
  void mousePressEvent(QMouseEvent* event) override;
  void keyPressEvent(QKeyEvent* event) override;

  void Resize();

  void DrawEmptyZones(QPainter* painter);
  void DrawMainMenu(QPainter* painter);
  void DrawGame(QPainter* painter);
  void DrawSettings(QPainter* painter);
  void DrawPauseMenu(QPainter* painter);
  void DrawEndgameMessage(QPainter* painter);
  void DrawTextNotification(QPainter* painter);

  // Game window
  void DrawTowersAuraAndRange(QPainter* painter);
  void DrawProjectiles(QPainter* painter);
  void DrawGameObjects(QPainter* painter);
  void DrawParticles(QPainter* painter);
  void DrawBars(QPainter* painter);
  void DrawAdditionalInfo(QPainter* painter);
  void DrawRoundInfo(QPainter* painter);
};

#endif  // VIEW_VIEW_H_
