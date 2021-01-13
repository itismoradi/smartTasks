CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

PROJECT(smartTasks)

SET(CMAKE_CXX_STANDARD 11)

INCLUDE_DIRECTORIES(include)

ADD_EXECUTABLE(smartTasks
	./src/main.cpp
	./src/program.cpp
	./src/task.cpp
	./src/commands.cpp
              )