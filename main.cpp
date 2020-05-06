#include <QApplication>

#include <memory>

#include "Controller/controller.h"

int main(int argc, char* argv[]) {
  QApplication a(argc, argv);
  auto controller = std::make_shared<Controller>();

  // Получение текущей системной локали. Чаще всего используется
  // формат вида "en_US" (сначала код языка по ISO 639, затем код
  // страны по ISO 3166).
  QString language = "en_US";
  QTranslator translator;

  // Попытка загрузить необходимый ресурс. Всегда следует проверять,
  // удалась ли загрузка, при необходимости загружая то, что загрузить
  // точно получится. Вы можете забыть подключить файл ресурсов,
  // системная локаль может быть очень странной, в общем, может возникнуть
  // множество различных проблем.
  if (!translator.load(":resources/translations/translation_" + language)) {
    translator.load(":resources/translations/translation_en_US");
    language = "en_US";
  }

  // Установка текущего ресурса (языка) в качестве языка приложения.
  QApplication::installTranslator(&translator);

  return a.exec();
}
