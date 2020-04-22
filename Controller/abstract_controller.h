#ifndef CONTROLLER_ABSTRACT_CONTROLLER_H_
#define CONTROLLER_ABSTRACT_CONTROLLER_H_

#include <list>
#include <memory>
#include <vector>

#include "GameObject/abstract_projectile.h"
#include "GameObject/base.h"
#include "GameObject/building.h"
#include "GameObject/enemy.h"

enum class Exit {
  kWin,
  kLose,
  kMenu,
};

enum class Speed {
  kZeroSpeed,
  kNormalSpeed,
  kDoubleSpeed
};

enum class WindowType {
  kMainMenu=0,
  kSettings=1,
  kPauseMenu=2,
  kGame=3
};

// AbstractController is needed to avoid the problem with looping include
// All public methods of controller should also be written here
class AbstractController {
 public:
  virtual ~AbstractController() = default;

  virtual void StartGame(int level) = 0;
  virtual void Tick(int current_time) = 0;
  virtual void EndGame(Exit exit) = 0;
  virtual void SetSpeedCoefficient(Speed speed) = 0;

  virtual void MousePress(Coordinate position) = 0;
  virtual void MouseMove(Coordinate position) = 0;
  virtual void RescaleObjects(const SizeHandler& size_handler) = 0;

  virtual const std::list<std::shared_ptr<Enemy>>& GetEnemies() const = 0;
  virtual const std::list<std::shared_ptr<AbstractProjectile>>&
  GetProjectiles() const = 0;
  virtual const std::vector<std::shared_ptr<Building>>&
  GetBuildings() const = 0;

  virtual const Base& GetBase() const = 0;
  virtual int GetCurrentTime() const = 0;

  virtual const AnimationPlayer& GetBackGround(WindowType type) const = 0;
};

#endif  // CONTROLLER_ABSTRACT_CONTROLLER_H_
