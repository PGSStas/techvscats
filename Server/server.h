#ifndef SERVER_SERVER_H_
#define SERVER_SERVER_H_

#include <QtCore/QObject>
#include <QElapsedTimer>
#include <QTimerEvent>

#include <list>

#include "message.h"

QT_FORWARD_DECLARE_CLASS(QWebSocketServer)
QT_FORWARD_DECLARE_CLASS(QWebSocket)

// Room to hold players in one game
struct Room {
  Room(int start_time, int level_id)
      : start_time(start_time), level_id(level_id) {}
  int start_time;
  int level_id;
  int players_count = 1;
  int players_in_process = 0;
  int wait_time = 8000;
  bool is_in_active_search = true;
  QStringList room_chat_;
};

struct GameClient {
  GameClient() = default;
  explicit GameClient(QWebSocket* socket) : socket(socket) {}
  bool operator==(const GameClient& other) const;
  QWebSocket* socket = nullptr;
  QString nick_name;
  Room* room = nullptr;
};

// The server is responsible for forwarding messages between users.
// It also supports global chats and rooms.
class Server : public QObject {
 Q_OBJECT

 public:
  explicit Server(quint16 port);
  ~Server();

 private:
  // Received Messages
  void ProcessReceivedMessage(const Message& message, QWebSocket* onwer);
  void ProcessNewConnectionMessage(const Message& message, GameClient*);
  void ProcessRoomEnterMessage(const Message& message, GameClient* owner);
  void ProcessRoundCompletedByPlayer(const Message& message, GameClient*);
  void ProcessGlobalChatMessage(const Message& message, GameClient*);
  // Room methods
  void StartRoom(Room* room);
  void SendMessageToRoom(const QByteArray& array, const GameClient& owner,
                         bool self_message = false);
  void RoomLeave(const GameClient& client);

 signals:  // NOLINT
  void closed();

 private slots:  // NOLINT
  void OnNewConnection();
  void ReceiveMessage(const QByteArray& array);
  void OnDisconnect();

 private:
  QStringList global_chat_;
  void timerEvent(QTimerEvent*);
  QWebSocketServer* web_socket_server_;
  std::list<GameClient> clients_;
  std::list<Room> rooms_;
  QElapsedTimer timer_;
  int current_time_;

  const int kMaxChatSize = 5;
};

#endif  // SERVER_SERVER_H_
