#ifndef VIEW_VIEW_H_
#define VIEW_VIEW_H_

#include <QTimerEvent>
#include <QMainWindow>
#include <QPushButton>
#include <QElapsedTimer>
#include <QObject>
#include <QString>
#include <QLabel>
#include "Controller/abstract_controller.h"

class View : public QMainWindow {
  Q_OBJECT

 public:
  explicit View(AbstractController* controller);
  ~View() = default;

  void EnableGameWindow();
  void DisableGameWindow();
  void EnableMenuWindow();
  void DisableMenuWindow();

  void UpdateRounds(int current_round_number, int rounds_count);

 private:
  bool is_menu_window_enabled;
  AbstractController* controller_;
  void paintEvent(QPaintEvent* event);
  void timerEvent(QTimerEvent* event);
  QElapsedTimer game_time_;
  // Game window
  QLabel* wave_status_label_;
  QPushButton* start_game_button_;
  // Menu window
  QPushButton* return_menu_button_;
  int timer_controller_id_;
  const int time_between_ticks_ = 10;

};

#endif  // VIEW_VIEW_H_
