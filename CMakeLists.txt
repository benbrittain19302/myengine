cmake_minimum_required(VERSION 3.0)
project(MYENGINE)

include_directories(
	src
)

add_executable(game
	src/game/main.cpp
)

add_library(myengine
	src/myengine/myengine.h

	src/myengine/Core.h
	src/myengine/Core.cpp

	src/myengine/Entity.h
	src/myengine/Entity.cpp

	src/myengine/Component.h
	src/myengine/Component.cpp
)

target_link_libraries(game myengine)