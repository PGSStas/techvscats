#ifndef VIEW_VIEW_H_
#define VIEW_VIEW_H_

#include <QTimerEvent>
#include <QMainWindow>
#include <QPushButton>
#include <QElapsedTimer>
#include <QObject>
#include <QString>
#include <QLabel>
#include <QDebug>
#include <list>
#include "Controller/abstract_controller.h"

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
  void DisableGameUi() const;
  void EnableMenuUi();
  void DisableMenuWindow() const;

  void UpdateRounds(int current_round_number, int number_of_rounds);

 private:
  WindowType window_type;
  AbstractController* controller_;
  QElapsedTimer game_time_;

  // Game window
  QLabel* wave_status_label_;
  QPushButton* start_game_button_;

  void DrawBackground(QPainter* p);

  // Menu window
  QPushButton* return_menu_button_;
  int controller_timer_id_;
  const int time_between_ticks_ = 10;

 private:
  void paintEvent(QPaintEvent* event) override;
  void timerEvent(QTimerEvent* event) override;
};

#endif  // VIEW_VIEW_H_
