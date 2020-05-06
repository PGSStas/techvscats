#ifndef ECHOSERVER_H
#define ECHOSERVER_H

#include <QtCore/QObject>

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

class EchoServer : public QObject {
 Q_OBJECT

 public:
  explicit EchoServer(quint16 port,
                      QObject* parent = nullptr);
  ~EchoServer();

 Q_SIGNALS:
  void closed();

 private Q_SLOTS:
  void onNewConnection();
  void processTextMessage(QString message);
  void socketDisconnected();

 private:
  uint64_t user_counter_ = 0;
  QWebSocketServer* web_socket_server_;
  std::list<GameClient> clients_;
};

#endif //ECHOSERVER_H
