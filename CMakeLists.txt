cmake_minimum_required(VERSION 3.0)
project(MYENGINE)

include_directories(
	src
	contrib/windows-cl-amd64/include
)

link_directories(
	${PROJECT_SOURCE_DIR}/contrib/windows-cl-amd64/lib
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

target_link_libraries(myengine SDL2 SDL2Main)