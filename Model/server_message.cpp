
#include "server_message.h"

QString ServerMessage::ToCode() const {
  return "Ok";
}

void ServerMessage::ToDecode(const QString& message) {
  from_id = 0;
  to_id = 1;
}

