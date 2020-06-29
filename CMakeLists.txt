cmake_minimum_required(VERSION 3.16)
project(learnopengl
        VERSION 1.0.0
        DESCRIPTION "Learn OpenGL")

set(CMAKE_CXX_STANDARD 17)
set(HEADER_FILES
        shader.h)
set(SOURCE_FILES
        main.cpp
        deps/glad/src/glad.c
        deps/stb_image/src/stb_image.cpp)

add_subdirectory(deps)

include_directories(deps/glad/include)
include_directories(deps/glm/glm)
include_directories(deps/glfw/include)
include_directories(deps/stb_image/include)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/resources DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(learnopengl ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries(learnopengl glfw glm)