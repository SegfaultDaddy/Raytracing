cmake_minimum_required(VERSION 3.5.0)
project(raytracing VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_C_STANDARD 23)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB files CONFIGURE_DEPENDS "headers/*.h" "source/*.cpp")
add_executable(raytracing ${files})
target_include_directories(raytracing PUBLIC header source)