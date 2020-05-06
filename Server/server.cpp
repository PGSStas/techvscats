#include "server.h"
#include "QtWebSockets/qwebsocketserver.h"
#include "QtWebSockets/qwebsocket.h"

QT_USE_NAMESPACE

bool GameClient::operator==(const GameClient& other) const {
  return other.socket == socket && other.id == id;
}

Server::Server(quint16 port)
    : web_socket_server_(new QWebSocketServer(
    QString("TechVsCats Server"),
    QWebSocketServer::NonSecureMode, this)) {
  if (web_socket_server_->listen(QHostAddress::Any, port)) {
    qDebug() << "Echoserver listening on port" << port;
    connect(web_socket_server_, &QWebSocketServer::newConnection,
            this, &Server::OnNewConnection);
    connect(web_socket_server_, &QWebSocketServer::closed,
            this, &Server::closed);
  }
}

Server::~Server() {
  web_socket_server_->close();
  for (auto& client : clients_) {
    client.socket->close();
  }
}

void Server::ProcessReceivedMessage(const ServerMessages& message,
                                    QWebSocket* owner) {
  switch (message.GetType()) {
    case MessageType::kNewConnection: {
      ProcessNewConnectionMessage(message, owner);
    }
    default: { break; }
  }
}

void Server::ProcessNewConnectionMessage(const ServerMessages& message,
                                         QWebSocket* owner) {
  for (auto& client:clients_) {
    if (client.socket == owner) {
      client.nick_name = message.GetMessage();
      qDebug() << "new name" << client.nick_name;
      break;
    }
  }

}

void Server::OnNewConnection() {
  QWebSocket* other_socket = web_socket_server_->nextPendingConnection();
  connect(other_socket, &QWebSocket::binaryMessageReceived,
          this, &Server::ReceiveMessage);
  connect(other_socket, &QWebSocket::disconnected,
          this, &Server::OnDisconnect);
  clients_.emplace_back(other_socket, ++user_counter_);
  qDebug() << "new connection!";
}

void Server::ReceiveMessage(const QByteArray& array) {
  QWebSocket* client_socket = qobject_cast<QWebSocket*>(sender());
  if (client_socket) {
    ProcessReceivedMessage(ServerMessages().ToDecode(array), client_socket);
  }
}

void Server::OnDisconnect() {
  QWebSocket* client_socket = qobject_cast<QWebSocket*>(sender());
  clients_.remove_if([&client_socket](const GameClient& client) {
    return client.socket == client_socket;
  });
  client_socket->deleteLater();
}
