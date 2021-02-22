cmake_minimum_required(VERSION 3.10)
project(gvexp)

add_subdirectory(c++-wrapper)

set(CMAKE_CXX_STANDARD 17)

find_package(PkgConfig REQUIRED)

pkg_check_modules(Libgvc REQUIRED IMPORTED_TARGET libgvc)

include_directories(${Libgvc_INCLUDE_DIRS})

add_executable(demo demo.cpp)
target_link_libraries(demo PUBLIC
  PkgConfig::Libgvc)
