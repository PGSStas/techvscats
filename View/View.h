#ifndef VIEW_H
#define VIEW_H

#include <QObject>
#include <QMainWindow>
#include "AbstractView.h"
#include "Controller/AbstractController.h"

class View :public QMainWindow, public AbstractView {
 Q_OBJECT
 public:
  View(AbstractController*);
  ~View() override = default;
 private:
  AbstractController* controller;
 };

#endif // VIEW_H
