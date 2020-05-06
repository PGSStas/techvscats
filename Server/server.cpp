#include "server.h"
#include "QtWebSockets/qwebsocketserver.h"
#include "QtWebSockets/qwebsocket.h"

QT_USE_NAMESPACE

bool GameClient::operator==(const GameClient& other) const {
  return other.socket == socket;
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
    timer_.start();
  }
}

Server::~Server() {
  web_socket_server_->close();
  for (auto& client : clients_) {
    client.socket->close();
  }
}

void Server::ProcessReceivedMessage(const ServerMessages& message,
                                    QWebSocket* owner_socket) {
  GameClient* client;
  for (auto& client_tmp:clients_) {
    if (client_tmp.socket == owner_socket) {
      client = &client_tmp;
    }
  }

  switch (message.GetType()) {
    case MessageType::kNewConnection: {
      ProcessNewConnectionMessage(message, client);
    }
    case MessageType::kEnterRoom: {
      ProcessRoomEnter(message, client);
    }
    default: { break; }
  }
}

void Server::ProcessNewConnectionMessage(const ServerMessages& message,
                                         GameClient* client) {
  client->nick_name = message.GetMessage();
  qDebug() << "new name" << client->nick_name;
}

void Server::OnNewConnection() {
  QWebSocket* other_socket = web_socket_server_->nextPendingConnection();
  connect(other_socket, &QWebSocket::binaryMessageReceived,
          this, &Server::ReceiveMessage);
  connect(other_socket, &QWebSocket::disconnected,
          this, &Server::OnDisconnect);
  clients_.emplace_back(other_socket);
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
  clients_.remove_if([&client_socket, this](const GameClient& client) {
    if (client.socket == client_socket) {
      if (client.room != nullptr) {
        LeaveRoom(client);
      }
      return true;
    }
    return false;
  });
  client_socket->deleteLater();
}

void Server::ProcessRoomEnter(const ServerMessages& message,
                              GameClient* client) {
  for (auto& room : rooms_) {
    if (room.level_id == message.GetNumber() && room.is_in_active_search
        && room.wait_time > 1000) {
      room.wait_time += 10000;
      room.player_count++;
      client->room = &room;
      return;
    }
  }
  rooms_.emplace_back(timer_.elapsed(), message.GetNumber());
  client->room = &rooms_.back();
  qDebug() << "new_room";
}

void Server::LeaveRoom(const GameClient& client) {
  client.room->player_count--;
  rooms_.remove_if([](const Room& room) { return room.player_count == 0; });
  // for all players in room send message
}
