#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui/QPainter>


class Controller;

class MainWindow : public QMainWindow {
 Q_OBJECT

 public:
  int controller_id;
  Controller* controller;
  MainWindow(QWidget* parent = 0);
  ~MainWindow();

  void timerEvent(QTimerEvent* event);
  void paintEvent(QPaintEvent* event);
//  void mousePressEvent(QMouseEvent* event);
//  void mouseMoveEvent(QMouseEvent* event);
//  void mouseReleaseEvent(QMouseEvent* event);
//  void keyPressEvent(QKeyEvent* e);

};

#endif // MAINWINDOW_H
