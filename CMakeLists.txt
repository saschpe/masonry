cmake_minimum_required(VERSION 2.6)
project(masonry)

set(CMAKE_MODULE_PATH "${masonry_SOURCE_DIR}/cmake/modules")

find_package(Qt4 4.6 COMPONENTS QtCore QtGui REQUIRED)
include(${QT_USE_FILE})
include_directories(${QT_INCLUDE_DIR} "src/")

if(WIN32 AND NOT UNIX)
    set(MASONRY_BIN_DIR "${CMAKE_INSTALL_PREFIX}")
    set(MASONRY_DATA_DIR "${CMAKE_INSTALL_PREFIX}/data")
    set(MASONRY_DOC_DIR "${CMAKE_INSTALL_PREFIX}/docs")
    set(MASONRY_MISC_DOC_DIR ${MASONRY_BIN_DIR})
    set(MASONRY_TRANS_DIR "${CMAKE_INSTALL_PREFIX}/translations")
    set(MASONRY_ICON_DIR "${CMAKE_INSTALL_PREFIX}/icons")
else()
    set(MASONRY_BIN_DIR "${CMAKE_INSTALL_PREFIX}/bin")
    set(MASONRY_DATA_DIR "${CMAKE_INSTALL_PREFIX}/share/masonry")
    set(MASONRY_DOC_DIR "${CMAKE_INSTALL_PREFIX}/share/doc/masonry")
    set(MASONRY_MISC_DOC_DIR ${MASONRY_DOC_DIR})
    set(MASONRY_TRANS_DIR "${CMAKE_INSTALL_PREFIX}/share/masonry/translations")
    set(MASONRY_ICON_DIR "${CMAKE_INSTALL_PREFIX}/share/icons")
    # Unix only desktop file installation dir
    set(MASONRY_DESKTOP_DIR "${CMAKE_INSTALL_PREFIX}/share/applications")
endif()
# Make some variables available in the source code
set_property(DIRECTORY PROPERTY COMPILE_DEFINITIONS
    #"MASONRY_BIN_DIR=\"${MASONRY_BIN_DIR}\""
    "MASONRY_DATA_DIR=\"${MASONRY_DATA_DIR}\""
    #"MASONRY_DOC_DIR=\"${MASONRY_DOC_DIR}\""
    #"MASONRY_MISC_DOC_DIR=\"${MASONRY_MISC_DOC_DIR}\""
    "MASONRY_TRANS_DIR=\"${MASONRY_TRANS_DIR}\""
    "MASONRY_ICON_DIR=\"${MASONRY_ICON_DIR}\"")

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
install(TARGETS masonry DESTINATION ${MASONRY_BIN_DIR})
install(DIRECTORY data/ DESTINATION ${MASONRY_DATA_DIR})
install(DIRECTORY docs/ DESTINATION ${MASONRY_DOC_DIR})
install(FILES AUTHORS.txt README.rst LICENSE.txt DESTINATION ${MASONRY_MISC_DOC_DIR})
install(FILES ${masonry_TRANSLATIONS} DESTINATION ${MASONRY_TRANS_DIR})

if(WIN32 AND NOT UNIX)
    install(DIRECTORY icons/ DESTINATION ${MASONRY_ICON_DIR})
    # Some extra convenience for Windows builds allows simpler distribution
    install(FILES ${QT_BINARY_DIR}/QtCore4.dll ${QT_BINARY_DIR}/QtGui4.dll DESTINATION ${CMAKE_INSTALL_PREFIX})
else()
    # Install desktop file
    install(FILES desktop/masonry.desktop DESTINATION ${MASONRY_DESKTOP_DIR})
endif()
