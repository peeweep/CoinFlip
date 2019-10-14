cmake_minimum_required(VERSION 3.5)

project(CoinFlip LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets Multimedia MultimediaWidgets REQUIRED)
SET(QT_USE_MULTIMEDIA TRUE)
SET(QT_USE_MULTIMEDIAWIDGETS TRUE)

add_executable(
        CoinFlip
        main.cpp
        src/mainscene.cpp
        src/mainscene.h
        src/mainscene.ui
        src/mypushbutton.cpp
        src/mypushbutton.h
        src/chooselevelscene.cpp
        src/chooselevelscene.h
        src/playscene.cpp
        src/playscene.h
        src/mycoin.cpp
        src/mycoin.h
        src/leveldataconfig.cpp
        src/leveldataconfig.h
        resource/resource.qrc
        )


target_link_libraries(CoinFlip PRIVATE Qt5::Widgets Qt5::Multimedia Qt5::MultimediaWidgets)
