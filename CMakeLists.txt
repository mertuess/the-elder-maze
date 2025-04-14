cmake_minimum_required(VERSION 3.10)
project(the-elder-maze)

set(CMAKE_CXX_STANDART 17)
set(CMAKE_CXX_STANDART_REQUIRED True)

find_package(fmt CONFIG REQUIRED)
find_package(libtcod CONFIG REQUIRED)

include_directories(include)

file(GLOB SRC_FILES "src/*.cpp")
list(APPEND SRC_FILES "main.cpp")

add_executable(TEM ${SRC_FILES})

add_custom_command(
  TARGET TEM POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different
        ${CMAKE_CURRENT_SOURCE_DIR}/resources/
        ${CMAKE_BINARY_DIR}/resources/
    COMMENT "Copying resources/ to build directory..."
)

target_link_libraries(TEM PRIVATE fmt::fmt PRIVATE libtcod::libtcod)
