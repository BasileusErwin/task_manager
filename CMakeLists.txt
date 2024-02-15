cmake_minimum_required(VERSION 3.22)
project(task_manager VERSION 0.1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED True)

set(CMAKE_C_COMPILER "clang")
set(CMAKE_CXX_COMPILER "clang++")

include_directories(${PROJECT_SOURCE_DIR}/src/include)

find_library(JSONC_LIBRARY NAMES json-c)
find_library(UUID_LIBRARY NAMES uuid)

if(NOT JSONC_LIBRARY)
    message(FATAL_ERROR "json-c not found")
endif()

if(NOT UUID_LIBRARY)
    message(FATAL_ERROR "uuid not found")
endif()

file(GLOB SOURCES
  "${PROJECT_SOURCE_DIR}/src/*.c"
)

add_executable(task_manager ${SOURCES})
target_link_libraries(task_manager ${JSONC_LIBRARY})
target_link_libraries(task_manager ${UUID_LIBRARY})

set(CMAKE_BUILD_TYPE Debug)

add_executable(task_manager_debug ${SOURCES})

target_link_libraries(task_manager_debug ${JSONC_LIBRARY})
target_link_libraries(task_manager_debug ${UUID_LIBRARY})

target_compile_options(task_manager_debug PRIVATE -g)

add_custom_target(clean-all
  COMMAND ${CMAKE_COMMAND} -P clean-all.cmake
)

file(REMOVE_RECURSE
  ${CMAKE_BINARY_DIR}/*
)

