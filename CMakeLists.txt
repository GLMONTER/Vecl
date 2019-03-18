cmake_minimum_required(VERSION 3.13)
project(Vecl)

set(CMAKE_CXX_STANDARD 17)

add_executable(Vecl main.cpp)

target_link_libraries(Vecl /usr/lib/x86_64-linux-gnu/libglfw.so /usr/lib/x86_64-linux-gnu/libvulkan.so)