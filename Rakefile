UIC="/opt/qt5/bin/uic"
UI_FILES="ui/delicious.ui"
TMP_FILES="ui_delicious.h"

desc "build it"
task :default => 'build/scutum' do
end

desc "show errors"
task :err do
	sh "cd build && vi err"
end

desc "test"
task :test do
	sh "cd build && ./scutum"
end

desc "Delicious Login Menu"
file 'ui_delicious.h' do
  puts "using qt5 uic"
	sh "#{UIC} ui/delicious.ui > ui_delicious.h"
end

desc "build it"
file 'build/scutum' => 'ui_delicious.h' do
	sh "cd build && make 2>err; cat err"
end

desc "clean"
task :clean do
	sh "rm -rf scutum Makefile build CMakeLists.txt #{TMP_FILES}"
end

desc "Setup for a qt4 build"
task :qt4 => :clean do
	sh "cp CMakeLists.txt.qt4 CMakeLists.txt && mkdir -p build && cd build && cmake .. && rake"
end

desc "Setup for a qt5 build"
desc "setup qt5"
#task :qt5 => :clean do
task :qt5 do
	sh "export QMAKESPEC=/opt/qt5/mkspecs/linux-g++ && export QTDIR=/opt/qt5 && export PATH=/opt/qt5/bin:$PATH && cp CMakeLists.txt.qt5 CMakeLists.txt && mkdir -p build && cd build && cmake .. && rake"
  puts "SUCCESS: built scutum for Qt5"
end

desc "Install app"
task :install => 'build/scutum' do
  sh "cp build/scutum /usr/local/bin"
end


