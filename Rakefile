desc "build it"
task :default => :scutum do
end

desc "show errors"
task :err do
	sh "cd src && make err"
end

desc "test"
task :test do
	sh "cd src && make test"
end

desc "build it"
task :scutum do
	sh "qmake"
	sh "make"
end

desc "clean"
task :clean do
	sh "make clean"
	sh "rm -f scutum Makefile"
end
