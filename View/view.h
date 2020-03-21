#ifndef VIEW_VIEW_H_
#define VIEW_VIEW_H_

#include <QObject>
#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include "Controller/abstract_controller.h"

class View : public QMainWindow {
 Q_OBJECT

 public:
  explicit View(AbstractController* controller);
  ~View() = default;

  void Tick();

  void EnableGameWindow();
  void DisableGameWindow();

 private:
  bool is_game_window;
  AbstractController* controller_;
  void paintEvent(QPaintEvent* event);

  // Game Ui
  QLabel* wave_status_label;
};

#endif  // VIEW_VIEW_H_
