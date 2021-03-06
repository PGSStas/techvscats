#ifndef SERVER_SERVER_H_
#define SERVER_SERVER_H_

#include <QObject>
#include <QElapsedTimer>
#include <QTimerEvent>
#include <QWebSocketServer>
#include <QWebSocket>

#include <algorithm>
#include <list>

#include "message.h"

enum class GameProcess {
  kWin,
  kLoose,
  kPlay
};

// Room to hold players in one game
// The game begins with automatic selection of enemies.
// Room lives kLifeRoomTimeForOneNewPlayer*number of
// players count and after starts
struct Room {
  Room(int start_time, int level_id)
      : start_time(start_time), level_id(level_id) {}

  int start_time;
  int level_id;
  int wait_time = 8000;
  int timer_id_ = 0;
  bool is_in_active_search = true;
  bool is_game_end = false;
  QStringList room_chat_;
  int players_count = 1;
  int players_in_round = 0;
  int players_loose_ = 0;
  int players_win_ = 0;
  int max_time_add_times_ = 6;
};

struct GameClient {
  GameClient() = default;
  explicit GameClient(QWebSocket* socket) : socket(socket) {}
  bool operator==(const GameClient& other) const;

  QWebSocket* socket = nullptr;
  QString nick_name;
  Room* room = nullptr;
  GameProcess game_process = GameProcess::kPlay;
};

// The server is responsible for forwarding messages between users.
// It also supports global chats and rooms.
class Server : public QObject {
  Q_OBJECT

 public:
  explicit Server(uint32_t port);
  ~Server() override;

 private:
  // Received Messages
  void ProcessReceivedMessage(const Message& message, QWebSocket* onwer);
  void ProcessNewConnectionMessage(const Message& message, GameClient*);
  void ProcessRoomEnterMessage(const Message& message, GameClient* owner);
  void ProcessRoundCompletedByPlayer(const Message& message, GameClient*);
  void ProcessGlobalChatMessage(const Message& message, GameClient*);

  // Room methods
  void StartRoom(Room* room);
  void SendMessageToRoom(const Message& message, const Room& room);
  void SendMessageToRoom(const Message& message, const GameClient& owner,
                         bool self_message = false);
  void SendMessageToClient(const Message& message, const GameClient& owner);

  void RoomLeave(const GameClient& client);
  void RoomTimer(Room* room);

 signals:  // NOLINT
  void closed();

 private slots:  // NOLINT
  void OnNewConnection();
  void ReceiveMessage(const QByteArray& array);
  void OnDisconnect();

 private:
  QStringList global_chat_;
  void timerEvent(QTimerEvent*) override;
  QWebSocketServer* web_socket_server_;
  std::list<GameClient> clients_;
  std::list<Room> rooms_;
  QElapsedTimer timer_;
  int timer_id_;

  const int kMaxChatSize = 40;
  const int kLifeRoomTimeForOneNewPlayer = 8000;
  const int kRoomSmallPrepareTime = 300;
};

#endif  // SERVER_SERVER_H_
