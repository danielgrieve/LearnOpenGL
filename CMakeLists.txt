cmake_minimum_required(VERSION 3.16)
project(airshow
        VERSION 1.0.0
        DESCRIPTION "Learn OpenGL")

set(CMAKE_CXX_STANDARD 17)
set(HEADER_FILES)
set(SOURCE_FILES
        main.cpp
        deps/glad/src/glad.c)

add_subdirectory(deps)

include_directories(deps/glad/include)
include_directories(deps/glfw/include)

add_executable(learnopengl ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries(learnopengl glfw)