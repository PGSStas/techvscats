#ifndef CONTROLLER_ABSTRACT_CONTROLLER_H_
#define CONTROLLER_ABSTRACT_CONTROLLER_H_

#include <QObject>
#include <list>
#include <vector>
#include <memory>
#include "GameObject/enemy.h"
#include "GameObject/active_tower.h"
#include "GameObject/passive_tower.h"
#include "GameObject/projectile.h"

enum class Exit {
  kWin,
  kLose,
  kMenu,
};

// AbstractController is needed to avoid the problem with looping include
// All public methods of controller should also be written here
class AbstractController {
 public:
  virtual void Tick(int current_time) = 0;
  virtual void StartGame(int level) = 0;
  virtual void EndGame(Exit exit) = 0;
  virtual const std::list<std::shared_ptr<Enemy>>& GetEnemies() const = 0;

  virtual ~AbstractController() = default;
};

#endif  // CONTROLLER_ABSTRACT_CONTROLLER_H_
