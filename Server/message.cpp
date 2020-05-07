#include "message.h"

QByteArray Message::NewConnectionMessage(QString nick_name) {
  message_ = nick_name;
  type_ = MessageType::kNewConnection;
  return ToCode();
}

QByteArray Message::EnterRoomMessage(int level_id) {
  number_ = level_id;
  type_ = MessageType::kEnterRoom;
  return ToCode();
}

QByteArray Message::StartRoundMessage() {
  type_=MessageType::kStartRound;
  return ToCode();
}

Message& Message::ToDecode(const QByteArray& array) {
  QJsonDocument json_document = QJsonDocument::fromBinaryData(array);
  type_ = static_cast<MessageType>(json_document["type"].toInt());
  message_ = json_document["message"].toString();
  number_ = json_document["number"].toInt();
  return *this;
}

QByteArray Message::ToCode() const {
  QJsonDocument json_document;
  QJsonObject json_object;
  json_object["type"] = static_cast<int>(type_);
  json_object["message"] = message_;
  json_object["number"] = number_;
  json_document.setObject(json_object);
  return json_document.toBinaryData();
}

MessageType Message::GetType() const {
  return type_;
}

QString Message::GetMessage() const {
  return message_;
}

int Message::GetNumber() const {
  return number_;
}

