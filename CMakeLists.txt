cmake_minimum_required(VERSION 2.8)
project(scutum)

FIND_PACKAGE(Qt4 REQUIRED)

INCLUDE(${QT_USE_FILE})
ADD_DEFINITIONS(${QT_DEFINITIONS})

QT4_ADD_RESOURCES(QtApp_RCC_SRCS ${QtApp_RCCS})

include_directories("/usr/include/qt4/QtWebKit")

SET (CMAKE_EXE_LINKER_FLAGS "-lQtWebKit")

SET(QtApp_RCCS jquery.qrc)
SET(QT_USE_QTWEBKIT TRUE)

SET(scutum_HEADERS mainwindow.h webtabwidget.hpp)

QT4_WRAP_CPP(scutum_HEADERS_MOC ${scutum_HEADERS})

set(scutum_SOURCES
main.cpp
mainwindow.cpp
webtabwidget.cpp
)

#target_link_libraries(scutum "")

ADD_EXECUTABLE(scutum ${scutum_SOURCES} 
    ${scutum_HEADERS_MOC})
TARGET_LINK_LIBRARIES(scutum ${QT_LIBRARIES})

