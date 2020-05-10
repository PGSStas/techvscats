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

  int return_code = QApplication::exec();
  if (return_code != constants::kApplicationRestartCode) {
    return return_code;
  }

#ifdef Q_OS_ANDROID
  // Code after won't work for SDK >= 28/29
  qDebug() << QtAndroid::androidSdkVersion();

  auto activity = QtAndroid::androidActivity();
  auto packageManager = activity.callObjectMethod(
      "getPackageManager",
      "()Landroid/content/pm/PackageManager;");

  auto activityIntent = packageManager.callObjectMethod(
      "getLaunchIntentForPackage",
      "(Ljava/lang/String;)Landroid/content/Intent;",
      activity.callObjectMethod("getPackageName",
                                "()Ljava/lang/String;").object());

  auto pendingIntent = QAndroidJniObject::callStaticObjectMethod(
      "android/app/PendingIntent",
      "getActivity",
      "(Landroid/content/Context;ILandroid/content/Intent;I)"
      "Landroid/app/PendingIntent;",
      activity.object(),
      jint(0),
      activityIntent.object(),
      QAndroidJniObject::getStaticField<jint>("android/content/Intent",
                                              "FLAG_ACTIVITY_CLEAR_TOP"));

  auto alarmManager = activity.callObjectMethod(
      "getSystemService",
      "(Ljava/lang/String;)Ljava/lang/Object;",
      QAndroidJniObject::getStaticObjectField(
          "android/content/Context",
          "ALARM_SERVICE",
          "Ljava/lang/String;").object());

  alarmManager.callMethod<void>(
      "setExact",
      "(IJLandroid/app/PendingIntent;)V",
      QAndroidJniObject::getStaticField<jint>(
          "android/app/AlarmManager", "RTC"),
      jlong(QDateTime::currentMSecsSinceEpoch() + 1), pendingIntent.object());

  return 0;
#else
  if (!QProcess::startDetached(QApplication::applicationFilePath())) {
    std::cerr << "Starting a new process failed!" << std::endl;
    return 1;
  }
  return 0;
#endif
}
