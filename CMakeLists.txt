cmake_minimum_required(VERSION 3.10)
project(the-elder-maze)

set(CMAKE_CXX_STANDART 17)
set(CMAKE_CXX_STANDART_REQUIRED True)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

find_package(fmt CONFIG REQUIRED)
find_package(libtcod CONFIG REQUIRED)
find_package(tomlplusplus CONFIG REQUIRED)

include_directories(include)

file(GLOB SRC_FILES "src/*.cpp")
list(APPEND SRC_FILES "main.cpp")

if (WIN32)
    set(RESOURCE_FILES ${RESOURCE_FILES} "icon.rc")
endif()

add_executable(TEM ${SRC_FILES} ${RESOURCE_FILES})

if (WIN32)
    set_target_properties(TEM PROPERTIES
        LINK_FLAGS "-mwindows"
        RC_FLAGS "-i icon.ico"
    )
endif()

add_custom_command(
  TARGET TEM POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different
        ${CMAKE_CURRENT_SOURCE_DIR}/resources/
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/resources/
    COMMENT "Copying resources/ to build directory..."
)

add_custom_command(
    TARGET TEM POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_CURRENT_SOURCE_DIR}/terminal.png
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/terminal.png
    COMMENT "Copying terminal.png to build directory..."
)

add_custom_command(
    TARGET TEM POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_CURRENT_SOURCE_DIR}/config.toml
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/config.toml
    COMMENT "Copying config.toml to build directory..."
)

target_link_libraries(TEM PRIVATE fmt::fmt PRIVATE libtcod::libtcod PRIVATE tomlplusplus::tomlplusplus)
