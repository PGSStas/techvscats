cmake_minimum_required(VERSION 3.10)
project(techvscats)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_AUTOMOC ON) # Enable Qt MOC compiler
set(CMAKE_AUTORCC ON) # Enable Qt resources compiler
set(CMAKE_AUTOUIC ON) # Enable Qt UI compiler

# You can set CMake prefix path here or pass it to CMake executable.
set(CMAKE_PREFIX_PATH "~/Qt/5.15.2/gcc_64/lib/cmake")
#set(CMAKE_PREFIX_PATH "C:/Qt/5.15.2/mingw81_64/lib/cmake")

if (NOT CMAKE_PREFIX_PATH)
    message(WARNING "CMAKE_PREFIX_PATH is not defined, you may need to set it "
            "(-DCMAKE_PREFIX_PATH=\"path/to/Qt/lib/cmake\")")
endif ()

set(QT_VERSION 5)
set(REQUIRED_LIBS Core Widgets Multimedia WebSockets)
set(REQUIRED_LIBS_QUALIFIED Qt5::Core Qt5::Widgets Qt5::Multimedia Qt5::WebSockets)
find_package(Qt${QT_VERSION} COMPONENTS ${REQUIRED_LIBS} REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-Wall -Wextra -O3")

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

qt5_add_big_resources(RESOURCES database.qrc music.qrc images.qrc)
add_executable(${PROJECT_NAME} ${SOURCES} ${RESOURCES})
target_link_libraries(${PROJECT_NAME} ${REQUIRED_LIBS_QUALIFIED})

add_executable(server
        Server/main.cpp
        Server/message.cpp
        Server/server.cpp)
