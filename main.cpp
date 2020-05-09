#include <QApplication>

#include <memory>
#include <QSettings>

#include "Controller/controller.h"

int main(int argc, char* argv[]) {
  QApplication a(argc, argv);

  QCoreApplication::setOrganizationName(constants::kCompanyName);
  QCoreApplication::setApplicationName(constants::kApplicationName);

  QSettings settings(constants::kCompanyName, constants::kApplicationName);

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
    if (!QProcess::startDetached(QApplication::applicationFilePath())) {
      return_code = 1;
    } else {
      return_code = 0;
    }
  }
  return return_code;
}
