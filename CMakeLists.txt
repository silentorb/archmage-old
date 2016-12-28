cmake_minimum_required(VERSION 3.6)
enable_language(CXX) # SINCE Compiler/Platform variables do not normally exist before a project command in CMake.

get_filename_component(PARENT_DIR ${CMAKE_SOURCE_DIR} DIRECTORY)

include(config.cmake OPTIONAL)

SET(CMAKE_EXE_LINKER_FLAGS "-static")
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
include("${CMAKE_TOOLS_PATH}/scripts/generator-key.cmake")

set(LOCAL_HEADER 1)
include(local-config.cmake OPTIONAL)

if (NOT MINGW)
  project(archmage)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
else ()
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
endif ()

include("${CMAKE_TOOLS_PATH}/cmake-tools.cmake")

add_subdirectory(projects/archmage)

finish_cmake()
