cmake_minimum_required(VERSION 3.40)
project(
  rlib
  VERSION 0.0.1
  LANGUAGES C)

option(EXAMPLE "Build Example" OFF)

include_directories(include)
add_compile_options(-Wall -Wextra)

set(LIB_SOURCES "src/rlib.c")

add_library(${PROJECT_NAME} STATIC ${LIB_SOURCES})

if(EXAMPLE)
  add_subdirectory(examples)
endif()
