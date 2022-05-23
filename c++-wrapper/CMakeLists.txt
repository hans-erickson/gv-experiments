cmake_minimum_required(VERSION 3.10)
project(gvcpp)

add_subdirectory(test)

set(CMAKE_CXX_STANDARD 20)

find_package(PkgConfig REQUIRED)

pkg_check_modules(Libgvc REQUIRED IMPORTED_TARGET libgvc)

include_directories(${Libgvc_INCLUDE_DIRS})

add_compile_options(-fconcepts-diagnostics-depth=4)

set(COMMON_SRC
#  impl/context.cpp
  impl/edge.cpp
  impl/graph.cpp
  #impl/layout.cpp
  impl/node.cpp
  impl/object.cpp)

add_library(${PROJECT_NAME}
  ${COMMON_SRC})

