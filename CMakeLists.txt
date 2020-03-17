cmake_minimum_required(VERSION 3.10)
project(techvscats)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_AUTOMOC ON) # Enable Qt MOC compiler for managing signals / slots
set(CMAKE_AUTORCC ON) # Enable Qt resources compiler
set(CMAKE_AUTOUIC ON) # Enable Qt UI compiler
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-Wall -Wextra ")

#set(CMAKE_PREFIX_PATH "~/Qt/5.13.2/gcc_64/lib/cmake")  # Linux
set(CMAKE_PREFIX_PATH "C:/Qt/5.13.2/mingw73_64/lib/cmake")  # Windows

find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)

add_executable(techvscats
        main.cpp
        Controller/Controller.cpp
        Controller/Enemy.cpp
        Controller/Spawner.cpp
        View/View.cpp
        Model/Model.cpp
        Model/Road.cpp
        )

target_link_libraries(techvscats Qt5::Core)
target_link_libraries(techvscats Qt5::Widgets)