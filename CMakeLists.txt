cmake_minimum_required(VERSION 3.10)
project(techvscats)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_AUTOMOC ON) # Enable Qt MOC compiler for managing signals / slots
set(CMAKE_AUTORCC ON) # Enable Qt resources compiler
set(CMAKE_AUTOUIC ON) # Enable Qt UI compiler
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-Wall -Wextra ")

#set(CMAKE_PREFIX_PATH "~/Qt/5.13.2/gcc_64/lib/cmake")  # Linux
#set(CMAKE_PREFIX_PATH "D:/QT/5.14.1/mingw73_64/lib/cmake")  # Windows

find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)

add_executable(techvscats
        main.cpp
        Controller/controller.cpp
        GameObject/enemy.cpp
        Controller/spawner.cpp
        View/view.cpp
        Model/model.cpp
        Model/road.cpp
        GameObject/passive_tower.cpp
        GameObject/active_tower.cpp
        GameObject/projectile.cpp)

target_link_libraries(techvscats Qt5::Core)
target_link_libraries(techvscats Qt5::Widgets)
