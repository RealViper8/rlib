cmake_minimum_required(VERSION 3.40)
project(rlib VERSION 0.0.1 LANGUAGES C)

option(EXAMPLE "Build Example" OFF)
option(SHARED "Build Shared Lib" OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(include)

set(LIB_SOURCES
    "src/rlib.c"
)

if(SHARED)
    add_library(${PROJECT_NAME} SHARED ${LIB_SOURCES})
else()
    add_library(${PROJECT_NAME} STATIC ${LIB_SOURCES})
endif()

if(EXAMPLE)
    add_executable(example example/main.c)
    target_link_libraries(example ${PROJECT_NAME})
endif()
