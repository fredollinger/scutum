cmake_minimum_required(VERSION 2.8)
project(scutum)

FIND_PACKAGE(Qt4 REQUIRED)

INCLUDE(${QT_USE_FILE})
ADD_DEFINITIONS(${QT_DEFINITIONS})

SET(scutum_RCCS jquery.qrc)
QT4_ADD_RESOURCES(scutum_RCC_SRCS ${scutum_RCCS})

include_directories("/usr/include/qt4/QtWebKit ")

set(CMAKE_CXX_FLAGS "-I /usr/include/qt4/QtNetwork" )

SET (CMAKE_EXE_LINKER_FLAGS "-lQtWebKit")

SET(QT_USE_QTWEBKIT TRUE)
SET(QT_USE_QTNETWORK)

SET(scutum_HEADERS 
deliciousbookmark.hpp
deliciouspassword.hpp
deliciousreply.hpp
mainwindow.h 
networkaccessmanager.hpp
scutnetworkreply.hpp
sidepane.hpp
scututil.hpp
scutrss.hpp
scutview.hpp
webtab.hpp
webtabwidget.hpp
webfilter.hpp
)

QT4_WRAP_CPP(scutum_HEADERS_MOC ${scutum_HEADERS})

set(scutum_SOURCES
deliciousbookmark.cpp
deliciouspassword.cpp
deliciousreply.cpp
jsondelicious.cpp
main.cpp
mainwindow.cpp
networkaccessmanager.cpp
scutnetworkreply.cpp
scututil.cpp
scutrss.cpp
scutview.cpp
sidepane.cpp
webfilter.cpp
webtab.cpp
webtabwidget.cpp
)

#target_link_libraries(scutum "")

ADD_EXECUTABLE(scutum ${scutum_SOURCES} 
    ${scutum_RCC_SRCS}
    ${scutum_HEADERS_MOC})
TARGET_LINK_LIBRARIES(scutum ${QT_LIBRARIES})

