find_package(Qt4 4.5 COMPONENTS QtCore QtGui QtOpenGL REQUIRED)

set(QT_USE_OPENGL TRUE)

include(${QT_USE_FILE})
include_directories(${QT_INCLUDE_DIR})

set(masonry_UIS
    gui/mainwindow.ui
)
set(masonry_SRCS
    gui/mainwindow.cpp
    main.cpp
)

qt4_wrap_ui(masonry_UIS_H ${masonry_UIS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})
qt4_automoc(${masonry_SRCS})

add_executable(masonry ${masonry_SRCS} ${masonry_UIS})
target_link_libraries(masonry ${QT_LIBRARIES})

#install(TARGETS masonry DESTINATION ${INSTALL_TARGETS_DEFAULT_ARGS})
