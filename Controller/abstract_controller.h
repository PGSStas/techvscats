#ifndef CONTROLLER_ABSTRACT_CONTROLLER_H_
#define CONTROLLER_ABSTRACT_CONTROLLER_H_

#include <list>
#include <vector>
#include <memory>

#include "GameObject/enemy.h"
#include "GameObject/projectile.h"
#include "GameObject/base.h"
#include "GameObject/building.h"

enum class Exit {
  kWin,
  kLose,
  kMenu,
};

// AbstractController is needed to avoid the problem with looping include
// All public methods of controller should also be written here
class AbstractController {
 public:
  virtual ~AbstractController() = default;

  virtual void Tick(int current_time) = 0;
  virtual void StartGame(int level) = 0;
  virtual void EndGame(Exit exit) = 0;

  virtual void MousePress(Coordinate position) = 0;
  virtual void MouseMove(Coordinate position) = 0;

  virtual const std::list<std::shared_ptr<Enemy>>& GetEnemies() const = 0;
  virtual const std::vector<std::shared_ptr<Building>>&
    GetBuildings() const = 0;
  virtual const std::vector<Road>& GetRoads() const = 0;
  virtual const Base& GetBase() const = 0;
};

#endif  // CONTROLLER_ABSTRACT_CONTROLLER_H_
