# Tech vs Cats

[![en](https://img.shields.io/badge/lang-en-yellow.svg)](README.md)
[![ru](https://img.shields.io/badge/lang-ru-yellow.svg)](README.ru.md)

Tech vs Cats is a non-profit 2D game written in C++ with the usage of
[Qt framework (5.14.2+)](https://www.qt.io). The game is designed for PC and Android
phones.

Tech vs Cats is a Tower Defense game. This means that there is a number of roads
that are followed by the enemies. Their aim is to attack the player's base, so the player, 
in return, must protect it - at all costs! To do this, you can build or upgrade 
existing towers, which shoot the enemies with the different missiles. The enemies
would cast different spells on the towers and come in tight groups, hoping to breach
the player's defences. To complete the level, you will need to destroy all of them.

![Tech vs Cats](https://user-images.githubusercontent.com/50747082/82308029-e18fdf00-99c9-11ea-9d93-37e21cefe14e.jpg)

![Tech vs Cats](https://user-images.githubusercontent.com/50747082/82308024-dfc61b80-99c9-11ea-9a8d-86e3129171bd.jpg)

![Tech vs Cats](https://user-images.githubusercontent.com/50747082/82308025-e05eb200-99c9-11ea-9e92-ae4ce10affcb.jpg)

### Features

* Two regular and one boss level, flexible system of adding new levels;
* Four tower types with different characteristics, behaviour and missile types 
(such as bombs and lasers);
* More than five enemy types, varying in health, speed and effects they apply to
allies or towers;
* All the actions of the player, enemies and towers are animated and sounded;
* Possibility to adjust the volume and other parameters, and to choose the language
(the translations were made with Qt Linguist);
* Multiplayer: the possibility to chat with other players and compete in passing
the levels.

### Authors

The game is a team study project of the BSU Faculty of Applied Mathematics and Computer
Science students (February-May 2020), developed by: 
* Stanislau Katsuba ([@PGSStas](https://github.com/PGSStas))
* Vladislav Kozulin ([@watislaf](https://github.com/watislaf))
* Maria Zacharneva ([@MariaZacharneva](https://github.com/MariaZacharneva))
* Elizabeth Fedenya ([@elizabethfeden](https://github.com/elizabethfeden))

The music 
[Crytek, Electronic Arts](https://www.crytek.com) and
[Emad Yaghoubi](https://emadyaghoubi.com) was used in the software.


## Development status

The development was finished in May 2020. The last version: 
[1.0](https://github.com/PGSStas/techvscats/tree/v1.0.0).

In [releases](https://github.com/PGSStas/techvscats/releases/tag/v1.0.0) 
one can find the zip-archive with the program files needed to run the game on 
Windows, and the apk-file needed to install the game to an Android phone.
To run the program on another OS, clone the repository and compile the game 
according to the instructions below.

To run the game on Windows, unpack the archive and run *techvscats.exe*. 

To run the game on Android, install the apk-file. If
Google Play Protect doesn't allow the installation, you can temporarily turn it
off in the Play Market settings, or install the program using ADB.

The app was tested on Windows 10 1803, Ubuntu 18.04,
Android 7.0 (MIUI 11) with aspect ratio 16:9, 
Android 9.0 (MIUI 11) with aspect ratio 21:9. We don't guarantee the correct 
performance on machines with other OS.

## Master status

[![Build Status](https://travis-ci.com/PGSStas/techvscats.svg?token=CVB2tNy7bYfWKHbaNP1q&branch=master)](https://travis-ci.com/PGSStas/techvscats)

The automatic build and static analysis run after every commit. Usually it takes
up to three minutes. If the widget turns green, the commit has passed the checks.
Otherwise some errors have occurred. To see the description of the errors, click
on the widget. To see the build and checks results in other git branches, follow
[this link](https://travis-ci.com/github/PGSStas/techvscats/branches)
 and choose the required commit.

Travis logs help to determine the step on which an error has occurred. The command
that caused the error turns red:
* `make`: project build.
* `cppcheck`: static code analysis.
* `cpplint`: static code analysis.

Messages about the build are printed before the result of running `make`. Cppcheck 
messages are printed after running `cppcheck`. Cpplint messages are printed
after running `cpplint`. 

Cppcheck notes don't change the build status, but it is recommended to read an fix them
if it is needed. Other messages can't be ignored.

## Building the project with QMake

To build the project with Qt Creator's QMake, clone the repository and run *techvscats.pro*. 

It is recommended to build the project with **GCC64** if you're using Linux, and
with **MinGW64** if you're using Windows.

The instructions on building the project for Android can be found in
[Qt documentation](https://doc.qt.io/qt-5/android-getting-started.html).

To edit the translations of the app you will need the Qt utilities 
[lupdate](https://doc.qt.io/qt-5/linguist-manager.html#using-lupdate),
[lrelease](https://doc.qt.io/qt-5/linguist-manager.html#using-lrelease) and
[Qt Linguist](https://doc.qt.io/qt-5/qtlinguist-index.html).

## Building the project with CMake

Sometimes you might want to work, for example, in Clion IDE, which doesn't support
QMake. You will need to build the project with CMake, which takes a few additional
steps.

First, clone the repository. You will need to edit the file *CMakeLists.txt*.
Change the line describing the path to CMake config files contained in Qt.
For example, as in the script in the repository,

`set(CMAKE_PREFIX_PATH "~/Qt/5.14.2/gcc_64/lib/cmake")`

If you work with Linux, the job is done. You can now import the project into CLion.

For Windows, do the following. Add the path to Qt compiler and libraries to the
Windows variable *Path*. For example:

`C:\Qt\Tools\mingw730_64\bin`

`C:\Qt\5.14.2\mingw73_64\bin`

We recommend to move these lines to the top (beginning) of the value of *Path*.
The reason is that Qt might be used in other software, so the paths to it might
have been already present in *Path*. During the compilation the first found 
libraries are used, so some problems might occur if their versions differ.

After editing *Path*, reboot Windows. Then, we recommend to choose the Qt compiler 
in CLion (write the path to it to **Settings - Toolchains**). After that you can work
with the project.

### CLion restrictions

Note that some Qt features are not accessible via CLion, such as
* CLion doesn't support compilation and building for Android.
* CLion doesn't support generation and editing of the translations. Use Qt
utilities.

## Known build problems

Use the latest Qt version (5.14.2+) while building the project. Otherwise, the game
won't compile for Android.
