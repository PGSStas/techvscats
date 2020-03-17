#ifndef VIEW_VIEW_H_
#define VIEW_VIEW_H_

#include <QObject>
#include <QMainWindow>
#include "AbstractView.h"
#include "Controller/AbstractController.h"

class View : public QMainWindow, public AbstractView {
  Q_OBJECT
 public:
  explicit View(AbstractController*);
  ~View() override = default;
 private:
  AbstractController* controller;
};

#endif  // VIEW_VIEW_H_
