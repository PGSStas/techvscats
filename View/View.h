#ifndef VIEW_VIEW_H_
#define VIEW_VIEW_H_

#include <QObject>
#include <QMainWindow>
#include "Controller/AbstractController.h"

class View : public QMainWindow {
  Q_OBJECT

 public:
  explicit View(AbstractController* controller);
  ~View() = default;

 private:
  AbstractController* controller_;
};

#endif  // VIEW_VIEW_H_
