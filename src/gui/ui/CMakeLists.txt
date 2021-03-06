cmake_minimum_required(VERSION 3.1.0)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)
# Create code from a list of Qt designer ui files
set(CMAKE_AUTOUIC ON)

# Find the QtWidgets library
find_package(Qt5Core CONFIG REQUIRED)
find_package(Qt5Widgets CONFIG REQUIRED)
find_package(Qt5Gui CONFIG REQUIRED)

include_directories(
    ${Qt5Core_INCLUDE_DIRS}
    ${Qt5Widgets_INCLUDE_DIRS}
    ${Qt5Gui_INCLUDE_DIRS}
    ${GDAL_INCLUDE_DIR}
    )

add_definitions(${Qt5Widgets_DEFINITIONS})

qt5_add_resources(NINJA_RESOURCES ${CMAKE_CURRENT_SOURCE_DIR}/windninja.qrc)

# Populate a CMake variable with the sources
set(NINJA_GUI_SRCSXXX
    mainwindow.ui
    mainwindow.cpp
    main.cpp
)
# Tell CMake to create the helloworld executable
add_executable(windninja5 ${NINJA_GUI_SRCSXXX} ${NINJA_RESOURCES})
# Use the Widgets module from Qt 5
target_link_libraries(windninja5
    ${Qt5Core_LIBRARIES}
    ${Qt5Widgets_LIBRARIES}
    ${Qt5Gui_LIBRARIES}
    ${GDAL_LIBRARIES}
    )
