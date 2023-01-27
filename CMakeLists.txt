cmake_minimum_required(VERSION 3.0)
project(MYENGINE)

include_directories(
	src
	contrib/windows-cl-amd64/include
)

link_directories(
	${PROJECT_SOURCE_DIR}/contrib/windows-cl-amd64/lib
)

add_library(rend
	src/rend/Animation.cpp
	src/rend/Buffer.cpp
	src/rend/Mesh.cpp
	src/rend/Model.cpp
	src/rend/ModelRenderer.cpp
	src/rend/RenderTexture.cpp
	src/rend/Renderer.cpp
	src/rend/Shader.cpp
	src/rend/Texture.cpp
	src/rend/rendmath.cpp
)

target_link_libraries(rend GLEW32 OPENGL32)

add_library(myengine
	src/myengine/myengine.h

	src/myengine/Core.h
	src/myengine/Core.cpp

	src/myengine/Entity.h
	src/myengine/Entity.cpp

	src/myengine/Component.h
	src/myengine/Component.cpp

	src/myengine/TriangleRenderer.h
	src/myengine/TriangleRenderer.cpp

	src/myengine/Transform.h
	src/myengine/Transform.cpp

	src/myengine/SoundSource.h
	src/myengine/SoundSource.cpp

	src/myengine/Camera.h
	src/myengine/Camera.cpp

	src/myengine/Resources.h
	src/myengine/Resources.cpp

	src/myengine/Resource.h
	src/myengine/Resource.cpp

	src/myengine/Texture.h
	src/myengine/Texture.cpp
	
	src/myengine/Sound.h
	src/myengine/Sound.cpp

	src/myengine/Model.h
	src/myengine/Model.cpp

	src/myengine/Input.h
	src/myengine/Input.cpp

	src/myengine/BoxCollider.h
	src/myengine/BoxCollider.cpp

	src/myengine/RigidBody.h
	src/myengine/RigidBody.cpp

	src/myengine/stb_vorbis.c
)

target_link_libraries(myengine SDL2 SDL2Main rend openal32)

add_executable(game
	src/game/main.cpp
)

target_link_libraries(game myengine)
