cmake_minimum_required(VERSION 3.10)
project(techvscats)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_AUTOMOC ON) # Enable Qt MOC compiler for managing signals / slots
set(CMAKE_AUTORCC ON) # Enable Qt resources compiler
set(CMAKE_AUTOUIC ON) # Enable Qt UI compiler
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-Wall -Wextra -O3")

# set(CMAKE_PREFIX_PATH "~/Qt/5.13.2/gcc_64/lib/cmake")  # Linux
set(CMAKE_PREFIX_PATH "E:/QT/5.14.2/mingw73_64/lib/cmake")  # Windows

find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5WebSockets REQUIRED)
find_package(Qt5Multimedia REQUIRED)


set(SOURCES
        main.cpp
        Controller/controller.cpp
        Controller/multiplayer_client.cpp
        Controller/spawner.cpp
        GameObject/abstract_projectile.cpp
        GameObject/homing_projectile.cpp
        GameObject/auric_field.cpp
        GameObject/base.cpp
        GameObject/bomb_projectile.cpp
        GameObject/building.cpp
        GameObject/effect.cpp
        GameObject/enemy.cpp
        GameObject/game_object.cpp
        GameObject/laser_projectile.cpp
        GameObject/moving_object.cpp
        GameObject/particle_handler.cpp
        GameObject/particle.cpp
        Model/coordinate.cpp
        Model/model.cpp
        Model/music_player.cpp
        Model/road.cpp
        Model/size.cpp
        Server/message.cpp
        Model/sound_vector.cpp
        database.qrc music.qrc images.qrc
        View/animation_player.cpp
        View/animation_player.cpp
        View/button_handler.cpp
        View/info_field.cpp
        View/menu_button.cpp
        View/size_handler.cpp
        View/text_notification.cpp
        View/tower_menu.cpp
        View/view.cpp
        View/global_chat.cpp)

add_executable(server
        Server/main.cpp
        Server/message.cpp
        Server/server.cpp)


#qt5_add_big_resources(SOURCES database.qrc music.qrc images.qrc)
add_executable(techvscats ${SOURCES})

target_link_libraries(techvscats Qt5::Core)
target_link_libraries(techvscats Qt5::Widgets)
target_link_libraries(techvscats Qt5::Multimedia)
target_link_libraries(techvscats Qt5::WebSockets)

target_link_libraries(server Qt5::Core)
target_link_libraries(server Qt5::WebSockets)

