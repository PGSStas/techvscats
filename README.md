## Tech vs Cats

Tech vs Cats - некоммерческая 2D-игра, написанная на C++ с использованием 
[Qt framework (5.14.2+)](https://www.qt.io). Игра предназначена для ПК, но может
работать и на Android-смартфонах.

Суть игры: имеется некоторое количество дорог, по которым передвигаются враги. 
Они стремятся напасть на вашу базу - строение, которое вы должны защитить любой 
ценой. Помочь игроку предназначены различные башни, которые можно покупать и 
улучшать. Башни могут стрелять во врагов различными снарядами. Враги умеют 
понижать эффективность этих самых башен и ходить плотными группами в надежде 
прорвать вашу защиту. Уничтожив всех врагов, вы пройдете уровень.

![Tech vs Cats](https://user-images.githubusercontent.com/50747082/82308029-e18fdf00-99c9-11ea-9d93-37e21cefe14e.jpg)
![Tech vs Cats](https://user-images.githubusercontent.com/50747082/82308024-dfc61b80-99c9-11ea-9a8d-86e3129171bd.jpg)
![Tech vs Cats](https://user-images.githubusercontent.com/50747082/82308025-e05eb200-99c9-11ea-9e92-ae4ce10affcb.jpg)

Игра является учебным проектом студентов 5 группы 1 курса факультета
прикладной математики и информатики БГУ (2 семестр 2019-2020): 
* Кацубы Станислава ([@PGSStas](https://github.com/PGSStas))
* Козулина Владислава ([@watislaf](https://github.com/watislaf))
* Захарневой Марии ([@MariaZacharneva](https://github.com/MariaZacharneva))
* Федени Елизаветы ([@elizabethfeden](https://github.com/elizabethfeden))

В программе используется музыка 
[Crytek, Electronic Arts](https://www.crytek.com) и
[Emad Yaghoubi](https://emadyaghoubi.com).


## Статус разработки

Разработка завершена в мае 2020 года. Последняя версия программы - 
[1.0](https://github.com/PGSStas/techvscats/tree/v1.0.0).

В секции [releases](https://github.com/PGSStas/techvscats/releases/tag/v1.0.0) 
можно найти архив с файлами программы, с помощью которого игру можно 
запустить под 64-разрядной Windows, а также apk-файл для установки игры на
Android-смартфон. Если вы хотите запустить игру на другой ОС, склонируйте
репозиторий и скомпилируйте проект самостоятельно (инструкции можно найти
ниже). 

Для работы с игрой под Windows распакуйте загруженный архив и запустите
исполняемый файл *techvscats.exe*. 

Чтобы запустить игру на Android, установите опубликованный apk-файл. Если
Google Play Protect будет блокировать установку приложения, вы можете временно
отключить Google Play Protect (это можно сделать в настройках Play Market) или
установить программу через ADB.

Учтите, что приложение тестировалось только на Windows 10 1803, Ubuntu 18.04,
Android 7.0 с оболочкой MIUI 11 c соотношением сторон 16:9, 
Android 9.0 с оболочкой MIUI 11 c соотношением сторон 21:9. Корректная работа 
приложения на других ОС не гарантируется.

## Статус ветви master

[![Build Status](https://travis-ci.com/PGSStas/techvscats.svg?token=CVB2tNy7bYfWKHbaNP1q&branch=master)](https://travis-ci.com/PGSStas/techvscats)

После каждого нового коммита запускается автоматическая сборка и статический 
анализ кода проекта. Обычно это занимает до трех минут. Если виджет загорается
зелёным, всё в порядке. В противном случае (красный или серый цвет) на
каком-то этапе возникли ошибки. Чтобы увидеть их описания, кликните по виджету.
Чтобы просмотреть результаты сборки и проверки кода в другой ветви разработки,
пройдите по [данной ссылке](https://travis-ci.com/github/PGSStas/techvscats/branches)
 и выберите нужный коммит.

Узнать, на каком этапе произошла ошибка, можно с помощью логов Travis. 
Проблемная команда подсвечивается красным. Возможны следующие варианты:
* `make`: отвечает за сборку проекта.
* `cppcheck`: отвечает за статический анализ кода.
* `cpplint`: отвечает за статический анализ кода.

Сообщения, связанные со сборкой проекта, выводятся перед вердиктом выполнения
команды `make`. Сообщения cppcheck выводятся после выполнения команды 
`cppcheck`. Сообщения cpplint выводятся после выполнения команды `cpplint`. 

Замечания cppcheck не влияют на статус сборки, но подобные сообщения стоит 
изучать и при необходимости исправлять. Все остальные предупреждения влияют 
на статус сборки, и игнорировать их нельзя.

## Сборка проекта с помощью QMake

Для того, чтобы собрать проект с помощью QMake в составе Qt Creator, 
достаточно склонировать репозиторий и запустить файл *techvscats.pro*. 

Сборку проекта под Linux рекомендуется осуществлять с помощью **GCC64**, под
Windows - с помощью **MinGW64**.

Сборка проекта под Android - несколько более сложная процедура. Немного
подробнее об этом можно почитать в
[документации](https://doc.qt.io/qt-5/android-getting-started.html).

Для редактирования переводов приложения следует использовать входящие в состав
Qt утилиты [lupdate](https://doc.qt.io/qt-5/linguist-manager.html#using-lupdate)
и [lrelease](https://doc.qt.io/qt-5/linguist-manager.html#using-lrelease), а
также [Qt Linguist](https://doc.qt.io/qt-5/qtlinguist-index.html).

## Сборка проекта с помощью CMake

В некоторых случаях с проектом удобнее работать, например, в среде разработки
CLion, которая не поддерживает QMake. В этом случае проект нужно собирать с
помощью CMake. Это сложнее, чем в случае с QMake, но вполне реально.

Сначала необходимо склонировать репозиторий. Как можно видеть, в него включен
пример скрипта *CMakeLists.txt*, который можно использовать в качестве основы.
В нем достаточно поменять лишь одну строчку: указать путь к входящим в состав
Qt конфигурационным файлам CMake. Пример (строка из скрипта в репозитории):

`set(CMAKE_PREFIX_PATH "~/Qt/5.14.2/gcc_64/lib/cmake")`

После этого на Linux проект можно импортировать в CLion для дальнейшей работы.
Под Windows необходимы дополнительные действия. Нужно указать в *Path*
путь к компилятору в составе Qt, а также путь к библиотекам Qt. Например:

`C:\Qt\Tools\mingw730_64\bin`

`C:\Qt\5.14.2\mingw73_64\bin`

Настоятельно рекомендуется переместить эти строки в *Path* как можно 
выше. Дело в том, что Qt относительно часто используется в стороннем
ПО, ссылки на которое могут присутствовать в *Path*. При компиляции выбираются
первые найденные по адресам в *Path* библиотеки. В случае, если выбраны
принадлежащие сторонним программам библиотеки, корректно собрать и запустить
проект может и не получиться из-за различий в их версиях.

После внесения изменений в *Path* необходимо перезагрузить Windows. Далее
рекомендуется выбрать в CLion компилятор, входящий в состав Qt (указать путь к 
нему в **Settings - Toolchains**). После этого можно работать с проектом.

### Ограничения CLion

Учитывайте, что при использовании CLion вам придется смириться со следующими
ограничениями:
* По умолчанию приложение нельзя будет скомпилировать, подписать и запустить
под Android. Возможно, существуют частичные решения этой проблемы.
* Для редактирования и генерации файлов перевода все равно нужны утилиты
Qt.

## Известные проблемы при сборке проекта

При сборке проекта необходимо использовать самую актуальную
версию Qt (как минимум 5.14.2). Если собирать его с помощью более старой
версии Qt, игра не скомпилируется под Android.
