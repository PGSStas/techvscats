#include "message.h"

Message::Message(MessageType type, QStringList list)
    : message_type_(type), arguments_(std::move(list)) {
  arguments_number_ = arguments_.size();
}

QByteArray Message::CodeToBinary(const Message& message) {
  QJsonDocument json_document;
  QJsonObject json_object;
  json_object["type"] = static_cast<int>(message.message_type_);
  json_object["arguments_number_"] = message.arguments_number_;
  for (int i = 0; i < message.arguments_number_; i++) {
    json_object["argument_" + QString::number(i)] = message.arguments_[i];
  }
  json_document.setObject(json_object);
  return json_document.toBinaryData();
}

Message& Message::SetVisibleMessage(const QString& message, VisibleType type,
                                    const QString& nick_name) {
  message_type_ = MessageType::kVisibleMessage;
  dialog_type_ = type;
  arguments_ = QStringList({""});
  arguments_number_ = 1;
  if (!nick_name.isEmpty()) {
    arguments_[0] = "> " + nick_name + " : ";
  }
  arguments_[0] += message;
  return *this;
}

Message& Message::SetCommandMessage(const QString& message,
                                    CommandType type) {
  message_type_ = MessageType::kControllerCommand;
  command_type_ = type;
  arguments_ = QStringList({message});
  arguments_number_ = 1;
  return *this;
}

Message& Message::DecodeFromBinary(const QByteArray& array) {
  QJsonDocument json_document = QJsonDocument::fromBinaryData(array);
  auto object = json_document.object();
  message_type_ = static_cast<MessageType>(object["type"].toInt());
  arguments_number_ = object["arguments_number_"].toInt();
  for (int i = 0; i < arguments_number_; i++) {
    arguments_.push_back(object["argument_" + QString::number(i)].toString());
  }
  return *this;
}

MessageType Message::GetType() const {
  return message_type_;
}

QString Message::GetArgument(int arg_num) const {
  if (arg_num >= arguments_number_) {
    return "";
  }
  return arguments_[arg_num];
}

const QStringList& Message::GetArguments() const {
  return arguments_;
}

CommandType Message::GetCommandType() const {
  return command_type_;
}

VisibleType Message::GetDialogType() const {
  return dialog_type_;
}
