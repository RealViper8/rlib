cmake_minimum_required(VERSION 3.40)

add_executable(example main.c)
target_link_libraries(example rlib)

add_executable(serializer serializer.c)
target_link_libraries(serializer rlib)
