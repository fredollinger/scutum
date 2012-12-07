desc "build it"
task :default => :scutum do
end

desc "show errors"
task :err do
	sh "cd build && vi err"
end

desc "test"
task :test do
	sh "cd build && ./scutum"
end

desc "build it"
task :scutum do
	sh "cd build && make 2>err; cat err"
end

desc "clean"
task :clean do
	sh "rm -rf scutum Makefile build CMakeLists.txt"
end

desc "Setup for a qt4 build"
task :qt4 => :clean do
	sh "cp CMakeLists.txt.qt4 CMakeLists.txt && mkdir -p build && cd build && cmake .. && rake scutum"
end

desc "Setup for a qt5 build"
desc "setup qt5"
task :qt5 do
	sh "export QMAKESPEC=/opt/qt5/mkspecs/linux-g++ && export QTDIR=/opt/qt5 && export PATH=/opt/qt5/bin:$PATH && cp CMakeLists.txt.qt5 CMakeLists.txt && mkdir -p build && cd build && cmake .. && rake"
  puts "SUCCESS: set up for qt5. Now type 'rake'"
end
