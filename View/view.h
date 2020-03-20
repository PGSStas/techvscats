#ifndef VIEW_VIEW_H_
#define VIEW_VIEW_H_

#include <QObject>
#include <QMainWindow>
#include "Controller/abstract_controller.h"

class View : public QMainWindow {
 Q_OBJECT

 public:
  explicit View(AbstractController* controller);
  ~View() = default;

 private:
  AbstractController* controller_;
  void paintEvent(QPaintEvent* event);
};

#endif  // VIEW_VIEW_H_
