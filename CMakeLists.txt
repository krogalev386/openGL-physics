cmake_minimum_required(VERSION 3.11)

project(openGLexampl)

cmake_policy(SET CMP0076 NEW)

find_package(OpenGL)

include(FetchContent)

FetchContent_Declare(
	GLFW
	GIT_REPOSITORY https://github.com/glfw/glfw.git
)
FetchContent_MakeAvailable(GLFW)

FetchContent_Declare(
	GLAD
	GIT_REPOSITORY https://github.com/Dav1dde/glad.git
)
FetchContent_MakeAvailable(GLAD)

FetchContent_Declare(
	GLM
	GIT_REPOSITORY https://github.com/g-truc/glm.git
)
FetchContent_MakeAvailable(GLM)

set(CMAKE_CXX_FLAGS "-fsanitize=address")

add_subdirectory(${PROJECT_SOURCE_DIR}/gl_buffers)
add_subdirectory(${PROJECT_SOURCE_DIR}/src)

add_executable(example main.cpp)

target_link_libraries(example 
	PUBLIC
		program_base
		gl_buffers
		glad
		OpenGL::GL
		glfw
		glm
)
