cmake_minimum_required(VERSION 3.10)
project(gvcpp)

add_subdirectory(test)

set(CMAKE_CXX_STANDARD 20)

find_package(PkgConfig REQUIRED)

pkg_check_modules(Libgvc REQUIRED IMPORTED_TARGET libgvc)

include_directories(${Libgvc_INCLUDE_DIRS})

set(COMMON_SRC
  impl/context.cpp
  impl/graph.cpp
  impl/layout.cpp
  impl/node.cpp)

add_library(${PROJECT_NAME}
  ${COMMON_SRC})

