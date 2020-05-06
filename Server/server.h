#ifndef SERVER_H
#define SERVER_H

#include <QtCore/QObject>
#include <QElapsedTimer>

#include "server_message.h"

QT_FORWARD_DECLARE_CLASS(QWebSocketServer)
QT_FORWARD_DECLARE_CLASS(QWebSocket)

struct Room {
  Room(int start_time, int level_id)
      : start_time(start_time), level_id(level_id) {}
  int start_time;
  int level_id;
  int player_count = 1;
  int wait_time = 15000;
  bool is_in_active_search = true;
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
  void ProcessReceivedMessage(const ServerMessages& message, QWebSocket* onwer);
  void ProcessNewConnectionMessage(const ServerMessages& message, GameClient*);
  void ProcessRoomEnter(const ServerMessages& message, GameClient*);

  void LeaveRoom(const GameClient& client);
  void OnNewConnection();
  void ReceiveMessage(const QByteArray& array);
  void OnDisconnect();

 private:
  QWebSocketServer* web_socket_server_;
  std::list<GameClient> clients_;
  std::list<Room> rooms_;
  QElapsedTimer timer_;
};

#endif //SERVER_H
