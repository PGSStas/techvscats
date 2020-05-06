#include "echoserver.h"
#include "QtWebSockets/qwebsocketserver.h"
#include "QtWebSockets/qwebsocket.h"

QT_USE_NAMESPACE

bool GameClient::operator==(const GameClient& other) const {
  return other.socket == socket && other.id == id;
}

EchoServer::EchoServer(quint16 port, QObject* parent)
    : QObject(parent), web_socket_server_(new QWebSocketServer(
    QString("TechVsCats Server"),
    QWebSocketServer::NonSecureMode, this)) {
  if (web_socket_server_->listen(QHostAddress::Any, port)) {
    qDebug() << "Echoserver listening on port" << port;
    connect(web_socket_server_, &QWebSocketServer::newConnection,
            this, &EchoServer::onNewConnection);
    connect(web_socket_server_, &QWebSocketServer::closed,
            this, &EchoServer::closed);
  }
}

EchoServer::~EchoServer() {
  web_socket_server_->close();
  for (auto& client : clients_) {
    client.socket->close();
  }
}

void EchoServer::onNewConnection() {
  QWebSocket* other_socket = web_socket_server_->nextPendingConnection();
  connect(other_socket, &QWebSocket::textMessageReceived,
          this, &EchoServer::processTextMessage);
  connect(other_socket, &QWebSocket::disconnected,
          this, &EchoServer::socketDisconnected);
  clients_.emplace_back(other_socket, ++user_counter_);
  qDebug()<<"new connection!";
}

void EchoServer::processTextMessage(QString message) {
  QWebSocket* client_socket = qobject_cast<QWebSocket*>(sender());
  if (client_socket) {
    message = client_socket->peerAddress().toString() + "  ->" + message;
        foreach(auto client, clients_) {
        client.socket->sendTextMessage(message);
      }
  }
  qDebug()<<"new message";
}

void EchoServer::socketDisconnected() {
  QWebSocket* client_socket = qobject_cast<QWebSocket*>(sender());
  clients_.remove_if([&client_socket](const GameClient& client) {
    return client.socket == client_socket;
  });
  client_socket->deleteLater();
}
