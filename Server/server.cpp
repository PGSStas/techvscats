#include "server.h"

bool GameClient::operator==(const GameClient& other) const {
  return other.socket == socket;
}

Server::Server(uint32_t port) : web_socket_server_(new QWebSocketServer(
    QString("TechVsCats Server"),
    QWebSocketServer::NonSecureMode, this)) {
  if (web_socket_server_->listen(QHostAddress::Any, port)) {
    connect(web_socket_server_, &QWebSocketServer::newConnection,
            this, &Server::OnNewConnection);
    connect(web_socket_server_, &QWebSocketServer::closed,
            this, &Server::closed);
    timer_id_ = startTimer(20);
    timer_.start();
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
  for (auto& client_tmp : clients_) {
    if (client_tmp.socket == owner_socket) {
      message_owner = &client_tmp;
      break;
    }
  }
  if (message_owner) {
    return;
  }
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
      SendMessageToClient(Message(MessageType::kChatUpdate,
                                  {global_chat_.join("\n")}), *message_owner);
      RoomLeave(*message_owner);
      message_owner->room = nullptr;
      break;
    }
    case MessageType::kGlobalChat: {
      ProcessGlobalChatMessage(message, message_owner);
      break;
    }
    default: {
      break;
    }
  }
}

void Server::ProcessNewConnectionMessage(const Message& message,
                                         GameClient* owner) {
  owner->nick_name = message.GetArgument(0);
  SendMessageToClient(Message(MessageType::kChatUpdate,
                              {global_chat_.join("\n")}), *owner);
}

void Server::ProcessRoomEnterMessage(const Message& message,
                                     GameClient* owner) {
  int room_number = message.GetArgument(0).toInt();
  for (auto& room : rooms_) {
    if (room.level_id == room_number && room.is_in_active_search
        && room.wait_time > kRoomSmallPrepareTime) {
      int additional_time = kLifeRoomTimeForOneNewPlayer;
      additional_time =
          std::max(0, additional_time - 1000 * room.max_time_add_times_--);
      room.wait_time += additional_time;
      room.players_count++;
      owner->room = &room;
      SendMessageToClient(Message(MessageType::kChatUpdate,
                                  {room.room_chat_.join("\n")}), *owner);

      SendMessageToRoom(Message(MessageType::kNickNameJoinedTheRoom,
                                {owner->nick_name}), *owner);
      return;
    }
  }
  rooms_.emplace_back(timer_.elapsed(), room_number);
  owner->room = &rooms_.back();
  owner->room->timer_id_ = startTimer(1000);
  SendMessageToRoom(Message(MessageType::kYouCreatedRoom), *owner, true);
  for (auto& client : clients_) {
    if (!client.nick_name.isEmpty() && client.room == nullptr) {
      SendMessageToClient(Message(MessageType::kGoToRoom,
                                  {QString::number(room_number)}), client);
    }
  }
}

void Server::ProcessRoundCompletedByPlayer(const Message& message,
                                           GameClient* owner) {
  GameProcess game_process = static_cast<GameProcess>(
      message.GetArgument(1).toInt());
  switch (game_process) {
    case GameProcess::kLoose: {
      owner->game_process = GameProcess::kLoose;
      owner->room->players_loose_++;
      SendMessageToRoom(Message(MessageType::kNickNameDead, {owner->nick_name}),
                        *owner,
                        true);
      break;
    }
    case GameProcess::kWin: {
      owner->game_process = GameProcess::kWin;
      owner->room->players_win_++;
      SendMessageToRoom(Message(MessageType::kNickNameWinWithHp, {
          owner->nick_name,
          QString::number(message.GetArgument(0).toInt())}), *owner, true);
      break;
    }
    default: {
      owner->game_process = GameProcess::kPlay;
      SendMessageToRoom(Message(MessageType::kNickNameFinishRoundWithHp, {
          owner->nick_name,
          QString::number(message.GetArgument(0).toInt())}), *owner, true);
      break;
    }
  }
  owner->room->players_in_round--;
  if (owner->room->players_in_round == 0) {
    owner->room->wait_time = 3000;
  }
}

void Server::ProcessGlobalChatMessage(const Message& message,
                                      GameClient* owner) {
  auto chat = &global_chat_;
  bool is_room = false;
  if (owner->room != nullptr) {
    is_room = true;
    chat = &owner->room->room_chat_;
  }
  *chat += "> " + owner->nick_name + " : " + message.GetArgument(0);
  while (chat->size() > kMaxChatSize) {
    chat->removeAt(0);
  }
  for (auto& client : clients_) {
    if (client.nick_name.isEmpty()) {
      continue;
    }
    if (is_room && client.room == owner->room) {
      SendMessageToClient(Message(MessageType::kChatUpdate,
                                  {chat->back()}), client);
    }
    if (!is_room && client.room == nullptr) {
      SendMessageToClient(Message(MessageType::kChatUpdate,
                                  {chat->back()}), client);
    }
  }
}

void Server::StartRoom(Room* room) {
  room->is_in_active_search = false;
  room->players_in_round =
      room->players_count - room->players_win_ - room->players_loose_;
  SendMessageToRoom(Message(MessageType::kStartRound), *room);
}

void Server::SendMessageToRoom(const Message& message, const Room& room) {
  for (auto& client : clients_) {
    if (client.room == &room) {
      client.socket->sendBinaryMessage(Message::CodeToBinary(message));
    }
  }
}

void Server::SendMessageToRoom(const Message& message,
                               const GameClient& owner,
                               bool self_message) {
  for (auto& client : clients_) {
    if (client.room == owner.room && (self_message || !(client == owner))) {
      client.socket->sendBinaryMessage(Message::CodeToBinary(message));
    }
  }
}

void Server::SendMessageToClient(const Message& message,
                                 const GameClient& owner) {
  owner.socket->sendBinaryMessage(Message::CodeToBinary(message));
}

void Server::RoomLeave(const GameClient& client) {
  client.room->players_count--;
  if (!client.room->is_in_active_search) {
    switch (client.game_process) {
      case GameProcess::kPlay: {
        client.room->players_in_round--;
        break;
      }
      case GameProcess::kLoose: {
        client.room->players_loose_--;
        break;
      }
      case GameProcess::kWin: {
        client.room->players_win_--;
        break;
      }
    }
  }
  SendMessageToRoom(Message(MessageType::kNickNameLeft,
                            {client.nick_name}), client,
                    true);
  rooms_.remove_if([this](const Room& room) {
    if (room.players_count == 0) {
      killTimer(room.timer_id_);
    }
    return room.players_count == 0;
  });
}

void Server::RoomTimer(Room* room) {
  if (room->is_in_active_search) {
    SendMessageToRoom(
        Message(MessageType::kRoomStartsIn,
                {QString::number(room->wait_time / 1000)}), *room);
    return;
  }
  if (room->wait_time > 0) {
    SendMessageToRoom(
        Message(MessageType::kRoundStartsIn,
                {QString::number(room->wait_time / 1000)}), *room);
    return;
  }
}

void Server::OnNewConnection() {
  QWebSocket* other_socket = web_socket_server_->nextPendingConnection();
  connect(other_socket, &QWebSocket::binaryMessageReceived,
          this, &Server::ReceiveMessage);
  connect(other_socket, &QWebSocket::disconnected,
          this, &Server::OnDisconnect);
  clients_.emplace_back(other_socket);
}

void Server::ReceiveMessage(const QByteArray& array) {
  auto* client_socket = qobject_cast<QWebSocket*>(sender());
  if (client_socket) {
    ProcessReceivedMessage(Message().DecodeFromBinary(array), client_socket);
  }
}

void Server::OnDisconnect() {
  auto* client_socket = qobject_cast<QWebSocket*>(sender());
  clients_.remove_if([&client_socket, this](const GameClient& client) {
    if (client.socket == client_socket) {
      if (client.room != nullptr) {
        RoomLeave(client);
      }
      return true;
    }
    return false;
  });
  client_socket->deleteLater();
}

void Server::timerEvent(QTimerEvent* event) {
  if (clients_.empty()) {
    return;
  }
  if (event->timerId() == timer_id_) {
    int delta_time = timer_.elapsed();
    timer_.start();
    for (auto& room : rooms_) {
      room.wait_time -= delta_time;
      if (room.is_game_end) {
        continue;
      }
      if (room.players_loose_ + room.players_win_ == room.players_count) {
        SendMessageToRoom(Message(MessageType::kGameEnd), room);
        room.is_game_end = true;
      } else if (room.wait_time <= 100 && room.players_in_round == 0) {
        StartRoom(&room);
      }
    }
  }
  for (auto& room : rooms_) {
    if (event->timerId() == room.timer_id_ && !room.is_game_end) {
      RoomTimer(&room);
      break;
    }
  }
}
