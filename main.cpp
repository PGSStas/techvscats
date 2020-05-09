#include <QApplication>

#include <memory>
#include <QSettings>

#include "Controller/controller.h"

int main(int argc, char* argv[]) {
  QApplication a(argc, argv);

  QCoreApplication::setOrganizationName("Giggling Penguin");
  QCoreApplication::setApplicationName("Tech vs Cats");

  QSettings settings("Giggling Penguin", "Tech vs Cats");

  QString language = settings.value("locale", "en_US").toString();
  QTranslator translator;

  if (!translator.load(":resources/translations/translation_" + language)) {
    translator.load(":resources/translations/translation_en_US");
    language = "en_US";
  }
  QApplication::installTranslator(&translator);

  auto controller = std::make_shared<Controller>();

  int return_code = a.exec();
  if (return_code == constants::kApplicationRestartCode) {
    auto proc = new QProcess();
    proc->start(QApplication::applicationFilePath());
  }
  return return_code;
}
