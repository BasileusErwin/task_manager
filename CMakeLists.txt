cmake_minimum_required(VERSION 3.28)
project(task_manager VERSION 0.1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED True)

include_directories(${PROJECT_SOURCE_DIR}/src/include)

file(GLOB SOURCES
  "${PROJECT_SOURCE_DIR}/src/*.c"
)

add_executable(task_manager ${SOURCES})

set(CMAKE_BUILD_TYPE Debug)

add_executable(task_manager_debug ${SOURCES})

target_compile_options(task_manager_debug PRIVATE -g)

add_custom_target(clean-all
  COMMAND ${CMAKE_COMMAND} -P clean-all.cmake
)

file(REMOVE_RECURSE
  ${CMAKE_BINARY_DIR}/*
)

