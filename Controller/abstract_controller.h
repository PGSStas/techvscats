#ifndef CONTROLLER_ABSTRACT_CONTROLLER_H_
#define CONTROLLER_ABSTRACT_CONTROLLER_H_

#include <QObject>
#include <list>
#include <memory>
#include "GameObject/enemy.h"
#include "GameObject/active_tower.h"
#include "GameObject/passive_tower.h"
#include "GameObject/projectile.h"

// AbstractController is needed to avoid the problem with looping include
// All public methods of controller should also be written here
class AbstractController {
 public:
  virtual ~AbstractController() = default;
  virtual const std::list<std::shared_ptr<Enemy>>* GetEnemyes() const = 0;
  virtual void Tick(int current_time) = 0;
  virtual void StartGame(int level) = 0;
  virtual void EndGame(int end_code) = 0;
};

#endif  // CONTROLLER_ABSTRACT_CONTROLLER_H_
