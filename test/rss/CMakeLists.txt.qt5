cmake_minimum_required(VERSION 2.8.3)
project(scutum)

# Tell CMake to run moc when necessary:
set(CMAKE_AUTOMOC ON)
# As moc files are generated in the binary dir, tell CMake
# to always look for includes there:
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Widgets finds its own dependencies (QtGui and QtCore).
find_package(Qt5Widgets REQUIRED)

# The Qt5Widgets_INCLUDES also includes the include directories for
# dependencies QtCore and QtGui
include_directories(${Qt5Widgets_INCLUDES} 
/opt/qt5/include/Qt
/opt/qt5/include/QtGui
/opt/qt5/include/QtCore 
/opt/qt5/include/QtNetwork
/opt/qt5/include/QtWidgets 
/opt/qt5/include/QtWebKit 
)

# We need add -DQT_WIDGETS_LIB when using QtWidgets in Qt 5.
add_definitions(${Qt5Widgets_DEFINITIONS})

# Executables fail to build with Qt 5 in the default configuration
# without -fPIE. We add that here.
set(CMAKE_CXX_FLAGS "${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS} -I/opt/qt5/include -L/opt/qt5/lib -L.. -DQT5" )

SET (CMAKE_EXE_LINKER_FLAGS "-lQtWebKit")

qt5_wrap_ui(ui_delicious.h ui/delicious.ui)

SET(scutum_HEADERS 
../../scutrss.hpp
)

set(scutum_SOURCES
../scutrss.cpp
main.cpp
)


add_executable(scutum 
${scutum_SOURCES} 
)

# The Qt5Widgets_LIBRARIES variable also includes QtGui and QtCore
 target_link_libraries(scutum ${Qt5Widgets_LIBRARIES})
