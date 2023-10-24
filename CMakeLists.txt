cmake_minimum_required(VERSION 3.22.1)

project(fps_gl LANGUAGES CXX )

file( GLOB_RECURSE SOURCE_FILES source/*.cpp)
file( GLOB_RECURSE HEADER_FILES source/*.hpp )

add_executable( ${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES})

# LIBRARIES
find_package( OpenGL REQUIRED )
find_package( SDL2 REQUIRED )
find_package( glm REQUIRED )
find_package( assimp REQUIRED )

add_subdirectory(dependencies/GLAD)
add_subdirectory(dependencies/STB_IMAGE)

# PROJECT SETUP
target_link_libraries(fps_gl PUBLIC
	glad
	stb_image
	glm::glm
	SDL2
	assimp
	${OPENGL_LIBRARIES}
)

target_include_directories(fps_gl PUBLIC
	${SDL2_INCLUDE_DIRS}
	source
)

target_compile_features(fps_gl PUBLIC cxx_std_17)