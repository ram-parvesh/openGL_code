cmake_minimum_required(VERSION 3.15)

project(opengl CXX C)

set(SET_CXX_STANDARD 20)

#submodule automatic checkout code
#check for git.
find_package(Git QUIET)
if(NOT Git_FOUND)
        message(FATAL_ERROR "Git is required to update submodules. Please install Git and try again.")
elseif (NOT EXISTS ${CMAKE_SOURCE_DIR}/.git)
        message(FATAL_ERROR "Git not initialised")
else()
    execute_process(
        COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        RESULT_VARIABLE GIT_SUB_RESULT
    )

    if(NOT ${GIT_SUB_RESULT} EQUAL 0)
        message(FATAL_ERROR "Failed to update Git submodules.")
    endif()
endif()

set(HEADER_FOLDERS
	include
	external,
	external/glad/include
	external/glfw/include
	external/glm
)

set(SRC_FILES
	src/main.cpp
	src/shaders.cpp
)

set(EXTERNAL_PROJECT_FILES
	external/glad/src/glad.c	
)

set(LIB_SUB_DIR
	external/glfw
)

add_subdirectory(${LIB_SUB_DIR})

find_package(OpenGL REQUIRED)

set(EXTERNAL_LIBS
	glfw
	OpenGL::GL
)

add_executable(${PROJECT_NAME} 
	${SRC_FILES}
	${EXTERNAL_PROJECT_FILES}
)

set(SHADERS
  "${CMAKE_CURRENT_BINARY_DIR}/shaders/vertex.glsl"
  "${CMAKE_CURRENT_BINARY_DIR}/shaders/fragment.glsl"
)

add_custom_target(copy-runtime-files ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/shaders ${CMAKE_BINARY_DIR}/shaders
    ##COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/resources/textures ${CMAKE_BINARY_DIR}/textures
    )



target_link_libraries(${PROJECT_NAME} PUBLIC ${EXTERNAL_LIBS})

target_include_directories(${PROJECT_NAME} PRIVATE ${HEADER_FOLDERS})

