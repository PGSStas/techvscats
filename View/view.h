#ifndef VIEW_VIEW_H_
#define VIEW_VIEW_H_

#include <QObject>
#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QString>
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
  bool is_menu_window;
  AbstractController* controller_;
  void paintEvent(QPaintEvent* event);
  // Game window
  QLabel* wave_status_label;
  QPushButton* start_game_button_;
  // Menu window
  QPushButton* return_menu_button_;
 private slots:
  void StartGameButtonClick();
  void ReturnMenuButtonClick();

};

#endif  // VIEW_VIEW_H_
