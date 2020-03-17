#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include <utility>

class QPainter;

class GameObject {
 public:
  virtual void Draw(QPainter*) = 0;
  virtual void Update() = 0; // выполнение действий
 private:
  std::pair<double, double> position_;
};

#endif  // GAMEOBJECT_H_
