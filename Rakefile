desc "build it"
task :default => :scutum do
end

desc "show errors"
task :err do
	sh "cd src && make err"
end

desc "test"
task :test do
	sh "cd build && ./scutum"
end

desc "build it"
task :scutum do
	sh "cd build && make"
end

desc "clean"
task :clean do
	sh "rm -rf scutum Makefile build"
end

desc "setup"
task :setup do
	sh "mkdir -p build && cd build && cmake .."
end
