#include "View.h"

View::View(AbstractController* controller) : controller_(controller) {
  show();
}

