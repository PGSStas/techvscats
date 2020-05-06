#ifndef MODEL_SERVER_MESSAGE_H_
#define MODEL_SERVER_MESSAGE_H_

#include <QString>

enum class ResponseType {
  kOk = 0,
  kError = 1
};

enum class MessageType {
  kOk = 0,
  kError = 1,
  kDefaultInfo = 2,
  kBadNews = 3
};

struct ServerMessage {
  void ToDecode(const QString& message);
  QString ToCode() const;
  ResponseType response_type;
  MessageType message_type;
  QString message;
  unsigned int to_id;
  unsigned int from_id;
};

#endif  // SERVER_MESSAGE_H_
