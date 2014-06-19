# Where your uic lives:
#UIC="build/uic"
UIC="qtchooser -run-tool=uic -qt5"

BUILD_DIR="build"
UI_FILES = FileList.new('ui/*.ui')
TMP_FILES = FileList.new('ui_*.h', BUILD_DIR, "CMakeLists.txt")
#TMP_FILES="#{BUILD_DIR} CMakeLists.txt"

desc "build it"
task :default => :build do
end

desc "build it"
task :build => :ui  do
  sh "rm -f build/scutum"
  sh "rake build/scutum"
end

desc "show errors"
task :err do
	sh "cd build && vi err"
end

desc "test"
task :test do
	sh "cd build && ./scutum"
end

desc "Make Delicious Login Menu"
file 'ui_deliciouspassword.h' do
	sh "#{UIC} ui/deliciouspassword.ui > ui_deliciouspassword.h"
end

desc "Make Delicious/RSS Reader Side Pane"
file 'ui_sidepane.h' do
	sh "#{UIC} ui/sidepane.ui > ui_sidepane.h"
end

desc "Build it if it has not yet been build."
file 'build/scutum' => ['ui_deliciouspassword.h', 'ui_sidepane.h'] do
	sh "cd build && make -j3 2>err; cat err"
end

desc "clean"
task :clean do
	sh "rm -rf #{TMP_FILES}"
end

desc "Setup for a qt4 build"
task :qt4 => :clean do
  sh "mkdir -p build && ln -s /usr/bin/uic-qt4 build/uic"
	sh "cp CMakeLists.txt.qt4 CMakeLists.txt && mkdir -p build && cd build && cmake .. && rake"
end

desc "Setup for a qt5 build"
desc "setup qt5"
task :qt5 do
  sh "mkdir -p build"
	sh "cp CMakeLists.txt.qt5 CMakeLists.txt && mkdir -p build && cd build && cmake .. && rake"
  puts "SUCCESS: built scutum for Qt5"
end

desc "Install app"
task :install => 'build/scutum' do
  sh "cp build/scutum /usr/local/bin"
end

rule "" do |t|
  target=t.name 
  sh "cd build && make #{target}.o"
end

desc "UI"
desc "Generate UI Files"
task :ui do
  UI_FILES.each do |fn|
    newui = "ui_"  + File::basename(fn).ext('.h')
    if not File.exist?(newui)
      sh "#{UIC} #{fn} > #{newui}"
    end
  end
end

desc "Clean temporary UI Files"
task :ui_clean do
  sh "rm -f ui_*.h"
end
