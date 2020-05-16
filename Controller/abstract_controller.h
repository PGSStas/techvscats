#ifndef CONTROLLER_ABSTRACT_CONTROLLER_H_
#define CONTROLLER_ABSTRACT_CONTROLLER_H_

#include <list>
#include <memory>
#include <vector>

#include <QSettings>

#include "GameObject/abstract_projectile.h"
#include "GameObject/base.h"
#include "GameObject/building.h"
#include "GameObject/enemy.h"
#include "GameObject/particle.h"
#include "View/text_notification.h"
#include "Model/music_player.h"
#include "multiplayer_client.h"

enum class GameStatus {
  kWin = 0,
  kLose = 1,
  kPlay = 2
};

enum class Speed {
  kZeroSpeed,
  kNormalSpeed,
  kDoubleSpeed
};

enum class WindowType {
  kMainMenu,
  kSettings,
  kTitles,
  kPauseMenu,
  kGame,
};

// AbstractController is needed to avoid the problem with looping include
// All public methods of controller should also be written here
class AbstractController {
 public:
  virtual ~AbstractController() = default;

  virtual void SecondConstructorPart() = 0;

  virtual void StartGame(int level) = 0;
  virtual void Tick(int current_time) = 0;
  virtual void EndGame() = 0;
  virtual void SetSpeedCoefficient(Speed speed) = 0;
  virtual void SetBuilding(int index_in_buildings, int replacing_id) = 0;

  virtual void MouseEvent(Coordinate position, bool is_press) = 0;
  virtual void RescaleObjects(const SizeHandler& size_handler) = 0;

  virtual const Building& GetBuildingById(int instance_id) const = 0;
  virtual const std::list<Particle>& GetParticles() const = 0;
  virtual const std::list<std::shared_ptr<Enemy>>& GetEnemies() const = 0;
  virtual const std::list<std::shared_ptr<AbstractProjectile>>&
  GetProjectiles() const = 0;
  virtual const std::vector<std::shared_ptr<Building>>&
  GetBuildings() const = 0;
  virtual const std::list<TextNotification>& GetTextNotifications() const = 0;

  virtual const Base& GetBase() const = 0;
  virtual int GetCurrentTime() const = 0;
  virtual GameStatus GetCurrentStatus() const = 0;

  virtual const AnimationPlayer& GetBackground(WindowType type) const = 0;

  virtual const QImage& GetEmptyZoneTexture(WindowType type) const = 0;
  virtual const AnimationPlayer& GetInterface() const = 0;

  virtual int GetCurrentRoundNumber() const = 0;
  virtual int GetRoundsCount() const = 0;
  virtual void SetGameVolume(int volume) = 0;
  virtual void ChangeChatStyle() = 0;

  virtual void CreateTitles() = 0;
  virtual void EndTitles() = 0;

  virtual MusicPlayer* GetMusicPlayer() = 0;
  virtual MultiplayerClient* GetClient() = 0;
};

#endif  // CONTROLLER_ABSTRACT_CONTROLLER_H_
