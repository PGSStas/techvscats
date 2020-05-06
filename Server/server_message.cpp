#include "server_message.h"

QByteArray ServerMessages::NewConnectionMessage(QString nick_name) {
  message_ = nick_name;
  type_ = MessageType::kNewConnection;
  return ToCode();
}

QByteArray ServerMessages::ToCode() const {
  QJsonDocument json_document;
  QJsonObject json_object;
  json_object["message"] = message_;
  json_object["type"] = static_cast<int>(type_);
  json_document.setObject(json_object);
  return json_document.toBinaryData();
}

void ServerMessages::ToDecode(const QByteArray& array) {
  QJsonDocument json_document = QJsonDocument::fromBinaryData(array);
  message_ = json_document["message"].toString();
  type_ = static_cast<MessageType>(json_document["type"].toInt());
}

QString ServerMessages::GetMessage() {
  return message_;
}

