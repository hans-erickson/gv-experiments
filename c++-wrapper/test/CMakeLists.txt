cmake_minimum_required(VERSION 3.10)
project(wrappertest)

set(CMAKE_CXX_STANDARD 17)

find_package(PkgConfig REQUIRED)

pkg_check_modules(Libgvc REQUIRED IMPORTED_TARGET libgvc)

include_directories(${Libgvc_INCLUDE_DIRS})

set(COMMON_SRC
  main.cpp
  wrapper-test.cpp)

add_executable(${PROJECT_NAME}
  ${COMMON_SRC})

target_link_libraries(${PROJECT_NAME}
  gtest
  pthread
  gvcpp
  PkgConfig::Libgvc) 
