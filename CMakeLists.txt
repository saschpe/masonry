cmake_minimum_required(VERSION 2.6)
project(masonry)

set(CMAKE_MODULE_PATH "${masonry_SOURCE_DIR}/cmake/modules")

find_package(Qt4 4.5 COMPONENTS QtCore QtGui QtOpenGL REQUIRED)
find_package(Tulip REQUIRED)

include(${QT_USE_FILE})
include_directories(${QT_INCLUDE_DIR} ${TULIP_INCLUDE_DIR})

set(masonry_UIS
    src/gui/mainwindow.ui
)
set(masonry_SRCS
    src/gui/mainwindow.cpp
    src/main.cpp
)

qt4_wrap_ui(masonry_UIS_H ${masonry_UIS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})
qt4_automoc(${masonry_SRCS})

add_executable(masonry ${masonry_SRCS} ${masonry_UIS})
target_link_libraries(masonry ${QT_LIBRARIES} ${TULIP_LIBRARIES})

#install(TARGETS masonry DESTINATION ${INSTALL_TARGETS_DEFAULT_ARGS})
