#ifndef SERVER_H
#define SERVER_H

#include <QtCore/QObject>
#include <QElapsedTimer>
#include <QTimerEvent>

#include "message.h"

QT_FORWARD_DECLARE_CLASS(QWebSocketServer)
QT_FORWARD_DECLARE_CLASS(QWebSocket)

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
  GameClient(QWebSocket* socket) : socket(socket) {}
  bool operator==(const GameClient& other) const;
  QWebSocket* socket = nullptr;
  QString nick_name;
  Room* room = nullptr;
};

class Server : public QObject {
 Q_OBJECT

 public:
  explicit Server(quint16 port);
  ~Server();

 Q_SIGNALS:
  void closed();

 private Q_SLOTS:
  void ProcessReceivedMessage(const Message& message, QWebSocket* onwer);
  void ProcessNewConnectionMessage(const Message& message, GameClient*);
  void ProcessRoomEnter(const Message& message, GameClient*);
  void ProcessRoundCompletedByPlayer(const Message& message, GameClient*);
  void ProcessGlobalChatMessage(const Message& message, GameClient*);

  void StartRoom(Room* room);
  void SendMessageToRoom(const QByteArray& array, const GameClient& owner,
                         bool self_message = false);
  void LeaveRoom(const GameClient& client);

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

  const int kMaxChatSize = 3;
};

#endif //SERVER_H
