find_package(Qt4 4.5 COMPONENTS QtCore QtGui QtOpenGL REQUIRED)
find_package(VTK 5.2.1 REQUIRED)

set(QT_USE_OPENGL TRUE)

include(${QT_USE_FILE} ${VTK_USE_FILE})
include_directories(${QT_INCLUDE_DIR} ${VTK_INCLUDE_DIRS})

set(sbslab_UIS
    gui/mainwindow.ui
)
set(sbslab_SRCS
    gui/mainwindow.cpp
    main.cpp
)

qt4_wrap_ui(sbslab_UIS_H ${sbslab_UIS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})
qt4_automoc(${sbslab_SRCS})

add_executable(sbslab ${sbslab_SRCS} ${sbslab_UIS})
target_link_libraries(sbslab ${QT_LIBRARIES} QVTK)

#install(TARGETS sbslab DESTINATION ${INSTALL_TARGETS_DEFAULT_ARGS})
