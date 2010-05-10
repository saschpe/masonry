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
    src/gui/widgets/nodedetaildockwidget.ui
    src/gui/widgets/outputdockwidget.ui
)

set(masonry_HDRS
    src/gui/dialogs/aboutdialog.h
    src/gui/dialogs/configdialog.h
    src/gui/graph/items/arrowitem.h
    src/gui/graph/items/directededgeitem.h
    src/gui/graph/items/graphitem.h
    src/gui/graph/items/nodeitem.h
    src/gui/graph/graphscene.h
    src/gui/graph/graphview.h
    src/gui/widgets/editdockwidget.h
    src/gui/widgets/nodedetaildockwidget.h
    src/gui/widgets/outputdockwidget.h
    src/gui/mainwindow.h
)

set(masonry_SRCS
    src/gui/dialogs/aboutdialog.cpp
    src/gui/dialogs/configdialog.cpp
    src/gui/graph/items/arrowitem.cpp
    src/gui/graph/items/directededgeitem.cpp
    src/gui/graph/items/graphitem.cpp
    src/gui/graph/items/nodeitem.cpp
    src/gui/graph/graphscene.cpp
    src/gui/graph/graphview.cpp
    src/gui/widgets/editdockwidget.cpp
    src/gui/widgets/nodedetaildockwidget.cpp
    src/gui/widgets/outputdockwidget.cpp
    src/gui/mainwindow.cpp
    src/main.cpp
)

set(masonry_TRANS
    translations/cs_CZ.ts
    translations/de_DE.ts
    translations/fr_FR.ts
)

qt4_wrap_ui(masonry_UIS_H ${masonry_UIS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})
qt4_automoc(${masonry_SRCS})

qt4_add_translation(masonry_TRANSLATIONS ${masonry_TRANS})

add_executable(masonry ${masonry_SRCS} ${masonry_UIS} ${masonry_TRANSLATIONS})
target_link_libraries(masonry ${QT_LIBRARIES})

# Installation
if(WIN32 AND NOT UNIX)
    install(TARGETS masonry DESTINATION ${CMAKE_INSTALL_PREFIX})
    install(DIRECTORY data/ DESTINATION ${CMAKE_INSTALL_PREFIX}/data)
    install(DIRECTORY docs/ DESTINATION ${CMAKE_INSTALL_PREFIX}/docs)
    install(FILES ${masonry_TRANSLATIONS} DESTINATION ${CMAKE_INSTALL_PREFIX}/data/locale)
    install(FILES AUTHORS.txt README.txt LICENSE.txt DESTINATION ${CMAKE_INSTALL_PREFIX})
    # Some extra convenience for Windows builds allows simpler distribution
    install(FILES ${QT_BINARY_DIR}/QtCore4.dll ${QT_BINARY_DIR}/QtGui4.dll DESTINATION ${CMAKE_INSTALL_PREFIX})
else()
    install(TARGETS masonry DESTINATION bin/)
    install(DIRECTORY data/ DESTINATION share/masonry/)
    install(DIRECTORY docs/ DESTINATION share/doc/masonry)
    install(FILES AUTHORS.txt README.txt LICENSE.txt DESTINATION share/doc/masonry)
    install(FILES ${masonry_TRANSLATIONS} DESTINATION share/masonry/locale)
endif()
