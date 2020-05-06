#ifndef SERVER_H
#define SERVER_H

#include <QtCore/QObject>
#include "server_message.h"

QT_FORWARD_DECLARE_CLASS(QWebSocketServer)
QT_FORWARD_DECLARE_CLASS(QWebSocket)

struct GameClient {
  GameClient(QWebSocket* socket, uint id) : socket(socket), id(id) {}
  bool operator==(const GameClient& other) const;
  QWebSocket* socket;
  QString nick_name;
  uint room_id = -1;
  uint id;
};

class Server : public QObject {
 Q_OBJECT

 public:
  explicit Server(quint16 port);
  ~Server();

 Q_SIGNALS:
  void closed();

 private Q_SLOTS:
  void OnNewConnection();
  void ReceiveMessage(const QByteArray& array);
  void OnDisconnect();

 private:
  uint64_t user_counter_ = 0;
  QWebSocketServer* web_socket_server_;
  std::list<GameClient> clients_;
};

#endif //SERVER_H
