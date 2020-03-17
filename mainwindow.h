#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include <QMainWindow>
#include <QtGui/QPainter>
#include "Controller/controller.h"

class Controller;

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  int controller_id;
  Controller* controller;
  explicit MainWindow(QWidget* parent = 0);
  ~MainWindow();

  void timerEvent(QTimerEvent* event);
  void paintEvent(QPaintEvent* event);
//  void mousePressEvent(QMouseEvent* event);
//  void mouseMoveEvent(QMouseEvent* event);
//  void mouseReleaseEvent(QMouseEvent* event);
//  void keyPressEvent(QKeyEvent* e);
};

#endif  // MAINWINDOW_H_
