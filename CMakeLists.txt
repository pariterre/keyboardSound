cmake_minimum_required(VERSION 3.8)
project(keyboardSound)

find_package(Qt5 COMPONENTS Core Widgets REQUIRED)
find_package(Qt5Multimedia REQUIRED)
set(CMAKE_AUTOMOC ON)

add_executable(${PROJECT_NAME}
    main.cpp
    MainWindow.cpp
)

target_link_libraries(${PROJECT_NAME}
    ${Qt5Core_LIBRARIES}
    ${Qt5Widgets_LIBRARIES}
    ${Qt5Multimedia_LIBRARIES}
)
