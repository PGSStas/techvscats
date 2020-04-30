#ifndef CONTROLLER_ABSTRACT_CONTROLLER_H_
#define CONTROLLER_ABSTRACT_CONTROLLER_H_

#include <list>
#include <memory>
#include <vector>

#include "GameObject/abstract_projectile.h"
#include "GameObject/base.h"
#include "GameObject/building.h"
#include "GameObject/enemy.h"
#include "View/text_notification.h"

enum class Exit {
  kWin,
  kLose,
  kPlay
};

enum class Speed {
  kZeroSpeed,
  kNormalSpeed,
  kDoubleSpeed
};

enum class WindowType {
  kMainMenu,
  kSettings,
  kPauseMenu,
  kGame
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
  virtual void SetBuilding(int index_in_buildings, int replacing_id) = 0;

  virtual void MouseEvent(Coordinate position , bool is_press) = 0;
  virtual void RescaleObjects(const SizeHandler& size_handler)  = 0;

  virtual const Building& GetBuildingById(int instance_id) const = 0;
  virtual const std::list<std::shared_ptr<Enemy>>& GetEnemies() const = 0;
  virtual const std::list<std::shared_ptr<AbstractProjectile>>&
  GetProjectiles() const = 0;
  virtual const std::vector<std::shared_ptr<Building>>&
  GetBuildings() const = 0;
  virtual const std::list<TextNotification>& GetTextNotifications() const = 0;

  virtual const Base& GetBase() const = 0;
  virtual int GetCurrentTime() const = 0;
  virtual Exit GetCurrentStatus() const = 0;

  virtual const AnimationPlayer& GetBackground(WindowType type) const = 0;
};

#endif  // CONTROLLER_ABSTRACT_CONTROLLER_H_
