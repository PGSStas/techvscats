#ifndef VIEW_VIEW_H_
#define VIEW_VIEW_H_

#include <QObject>
#include <QMainWindow>
#include <QLabel>
#include "Controller/abstract_controller.h"

class View : public QMainWindow {
 Q_OBJECT

 public:
  explicit View(AbstractController* controller);
  ~View() = default;

  void StartGameUi();
  void UpdateGameUi();
  void EndGameUi();

 private:
  AbstractController* controller_;
  void paintEvent(QPaintEvent* event);
  std::unique_ptr<QLabel> wave_status_;
};

#endif  // VIEW_VIEW_H_
