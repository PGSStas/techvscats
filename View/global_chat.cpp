#include "global_chat.h"

GlobalChat::GlobalChat(QMainWindow* window) {
  q_text_edit_ = new QTextEdit(window);
  send_button = new MenuButton(
      Size(20, kSize.width), window,
      ":resources/buttons_resources/inc_level_button.png",
      ":resources/buttons_resources/inc_level_button_active.png");

}

void GlobalChat::RescaleChat(const SizeHandler& size_handler) {
  send_button->SetGeometry(Coordinate(40, 700), size_handler);

  Coordinate text_edit_position =
      size_handler.GameToWindowCoordinate({40, 700});
  Size text_edit_size = size_handler.GameToWindowSize({50, 30});
  q_text_edit_->setGeometry(text_edit_position.x, text_edit_position.y,
                            text_edit_size.width, text_edit_size.height);

  Coordinate text_browser_position =
      size_handler.GameToWindowCoordinate({40, 700});
  Size text_browser_size = size_handler.GameToWindowSize({500, 200});
  q_text_browser_->setGeometry(text_browser_position.x,
                               text_browser_position.y,
                               text_browser_size.width,
                               text_browser_size.height);
}
