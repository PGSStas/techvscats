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
#include "size_handler.h"

#include <QMouseEvent>
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

 private:
  WindowType window_type;
  AbstractController* controller_;
  std::shared_ptr<SizeHandler> size_handler_;
  QElapsedTimer game_time_;

  // Game window
  QLabel* wave_status_label_;
  QPushButton* start_game_button_;

  void DrawBackground(QPainter* p);

  // Menu window
  QPushButton* return_menu_button_;
  int timer_controller_id_;
  const int time_between_ticks_ = 10;

 private:
  void paintEvent(QPaintEvent* event) override;
  void timerEvent(QTimerEvent* event) override;
  void resizeEvent(QResizeEvent* event) override;
};

#endif  // VIEW_VIEW_H_
