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
    startTimer(20);
  }
}

Server::~Server() {
  web_socket_server_->close();
  for (auto& client : clients_) {
    client.socket->close();
  }
}

void Server::ProcessReceivedMessage(const Message& message,
                                    QWebSocket* owner_socket) {
  GameClient* message_owner;
  for (auto& client_tmp:clients_) {
    if (client_tmp.socket == owner_socket) {
      message_owner = &client_tmp;
    }
  }
  qDebug() << "new message from:" << message_owner->nick_name;
  switch (message.GetType()) {
    case MessageType::kNewConnection: {
      ProcessNewConnectionMessage(message, message_owner);
      break;
    }
    case MessageType::kEnterRoom: {
      ProcessRoomEnterMessage(message, message_owner);
      break;
    }
    case MessageType::kRoundCompletedByPlayer: {
      ProcessRoundCompletedByPlayer(message, message_owner);
      break;
    }
    case MessageType::kLeaveRoom: {
      LeaveRoom(*message_owner);
      message_owner->room = nullptr;
      message_owner->socket->sendBinaryMessage(
          Message().DialogMessage(global_chat_.join("\n"),
                                  DialogType::kChat));
      break;
    }
    case MessageType::kGlobalChat: {
      ProcessGlobalChatMessage(message, message_owner);
      break;
    }
    default: {
      qDebug() << "error message";
      break;
    }
  }
}

void Server::ProcessNewConnectionMessage(const Message& message,
                                         GameClient* owner) {
  owner->nick_name = message.GetMessage();
  owner->socket->sendBinaryMessage(
      Message().DialogMessage(global_chat_.join("\n"),
                              DialogType::kChat));
  qDebug() << "new name" << owner->nick_name;
}

void Server::ProcessRoomEnterMessage(const Message& message,
                                     GameClient* owner) {
  for (auto& room : rooms_) {
    if (room.level_id == message.GetNumber() && room.is_in_active_search
        && room.wait_time > 1000) {
      room.wait_time += 8000;
      room.players_count++;
      owner->room = &room;
      owner->socket->sendBinaryMessage(
          Message().DialogMessage(room.room_chat_.join("\n"),
                                  DialogType::kChat));
      qDebug() << "connected_to_room";
      return;
    }
  }
  rooms_.emplace_back(timer_.elapsed(), message.GetNumber());
  owner->room = &rooms_.back();
  qDebug() << "new_room";
}

void Server::ProcessRoundCompletedByPlayer(const Message& message,
                                           GameClient* owner) {
  SendMessageToRoom(Message().DialogMessage(
      "finished the round with " + QString::number(message.GetNumber()) + "HP",
      DialogType::kWarning, owner->nick_name), *owner, true);
  owner->room->players_in_process--;
  if (owner->room->players_in_process == 0) {
    owner->room->wait_time = 2000;
  }
  qDebug() << "I have finished round";
}

void Server::ProcessGlobalChatMessage(const Message& message,
                                      GameClient* owner) {
  auto chat = &global_chat_;
  bool is_room = false;
  if (owner->room != nullptr) {
    is_room = true;
    chat = &owner->room->room_chat_;
  }
  *chat += "> " + owner->nick_name + " : " + message.GetMessage();
  while (chat->size() > kMaxChatSize) {
    chat->removeAt(0);
  }
  for (auto& client : clients_) {
    if (!is_room || client.room == owner->room) {
      client.socket->sendBinaryMessage(
          Message().DialogMessage(message.GetMessage(),
                                  DialogType::kChat,
                                  owner->nick_name));
    }
  }
}

void Server::StartRoom(Room* room) {
  room->is_in_active_search = false;
  room->players_in_process = room->players_count;
  for (auto& client: clients_) {
    if (client.room == room) {
      client.socket->sendBinaryMessage(Message().StartRoundMessage());
      qDebug() << "StartRoom";
    }
  }
}

void Server::SendMessageToRoom(const QByteArray& array, const GameClient& owner,
                               bool self_message) {
  for (auto& client: clients_) {
    if (client.room == owner.room && (self_message || !(client == owner))) {
      client.socket->sendBinaryMessage(array);
    }
  }
}

void Server::LeaveRoom(const GameClient& client) {
  client.room->players_count--;
  client.room->players_in_process--;
  SendMessageToRoom(Message().DialogMessage(
      " leave the game!",
      DialogType::kWarning, client.nick_name), client,
                    true);
  rooms_.remove_if([](const Room& room) {
    if (room.players_count == 0) { qDebug() << "room close"; }
    return room.players_count == 0;
  });
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
    ProcessReceivedMessage(Message().DecodeFromBinary(array), client_socket);
  }
}

void Server::OnDisconnect() {
  QWebSocket* client_socket = qobject_cast<QWebSocket*>(sender());
  clients_.remove_if([&client_socket, this](const GameClient& client) {
    if (client.socket == client_socket) {
      if (client.room != nullptr) {
        LeaveRoom(client);
      }
      qDebug() << "bye bye," << client.nick_name;
      return true;
    }
    return false;
  });
  client_socket->deleteLater();
}

void Server::timerEvent(QTimerEvent*) {
  if (clients_.empty()) {
    return;
  }
  int delta_time = timer_.elapsed() - current_time_;
  current_time_ += delta_time;
  for (auto& room : rooms_) {
    room.wait_time -= delta_time;
    if (room.wait_time <= 100 && room.players_in_process == 0) {
      StartRoom(&room);
    }
  }
}
