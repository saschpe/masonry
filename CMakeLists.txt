cmake_minimum_required(VERSION 2.6)
project(masonry)

set(CMAKE_MODULE_PATH "${masonry_SOURCE_DIR}/cmake/modules")

find_package(Qt4 4.6 COMPONENTS QtCore QtGui REQUIRED)

option(INSTALL_SYSTEM_LIBS "Install required system libraries too (only in shared mode)" OFF)

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
    src/gui/graph/graphscene.cpp
    src/gui/graph/graphview.cpp
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

# install required shared libraries
if(WIN32 AND INSTALL_SYSTEM_LIBS)
    set(QT_QTCORE_LIBRARY ${QT_LIBRARY_DIR}/../bin/QtCore4.dll)
    set(QT_QTGUI_LIBRARY ${QT_LIBRARY_DIR}/../bin/QtGui4.dll)
    set(QT_QTNETWORK_LIBRARY ${QT_LIBRARY_DIR}/../bin/QtNetwork4.dll)
    install_files(FILES ${QT_QTCORE_LIBRARY})
    install_files(FILES ${QT_QTGUI_LIBRARY})
    install_files(FILES ${QT_QTNETWORK_LIBRARY})

    if (MINGW)
        find_file(MINGW_DLL mingwm10.dll)
        install_files(FILES  ${MINGW_DLL})
    else()
        include(InstallRequiredSystemLibraries)
    endif()
endif()
