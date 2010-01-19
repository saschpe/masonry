cmake_minimum_required(VERSION 2.6)
project(masonry)

set(CMAKE_MODULE_PATH "${masonry_SOURCE_DIR}/cmake/modules")

find_package(Qt4 4.6 COMPONENTS QtCore QtGui REQUIRED)

include(${QT_USE_FILE})
include_directories(${QT_INCLUDE_DIR} "src/")

set(masonry_UIS
    src/gui/dialogs/aboutdialog.ui
    src/gui/dialogs/configdialog.ui
    src/gui/mainwindow.ui
    src/gui/widgets/editdockwidget.ui
    src/gui/widgets/infodockwidget.ui
    src/gui/widgets/outputdockwidget.ui
)
set(masonry_SRCS
    src/gui/dialogs/aboutdialog.cpp
    src/gui/dialogs/configdialog.cpp
    src/gui/graph/arrowitem.cpp
    src/gui/graph/directededgeitem.cpp
    src/gui/graph/graphitem.cpp
    src/gui/graph/graphscene.cpp
    src/gui/graph/graphview.cpp
    src/gui/graph/layeritem.cpp
    src/gui/graph/nodeitem.cpp
    src/gui/graph/receiveritem.cpp
    src/gui/graph/transmitteritem.cpp
    src/gui/mainwindow.cpp
    src/gui/widgets/editdockwidget.cpp
    src/gui/widgets/infodockwidget.cpp
    src/gui/widgets/outputdockwidget.cpp
    src/main.cpp
)

qt4_wrap_ui(masonry_UIS_H ${masonry_UIS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})
qt4_automoc(${masonry_SRCS})

add_executable(masonry ${masonry_SRCS} ${masonry_UIS})
target_link_libraries(masonry ${QT_LIBRARIES})

install(TARGETS masonry DESTINATION ${CMAKE_INSTALL_PREFIX})
install(DIRECTORY data/ DESTINATION ${CMAKE_INSTALL_PREFIX}/data)
