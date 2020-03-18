#ifndef CONTROLLER_GAMEOBJECT_H_
#define CONTROLLER_GAMEOBJECT_H_

#include <utility>

class QPainter;

class GameObject {
 public:
  virtual void Draw(QPainter*) = 0;
  virtual void Update() = 0;  // выполнение действий
 protected:
  std::pair<double, double> position_;
};

#endif  // CONTROLLER_GAMEOBJECT_H_
