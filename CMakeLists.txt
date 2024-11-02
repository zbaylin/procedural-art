cmake_minimum_required(VERSION 3.14)
project(ProceduralArt VERSION 0.0.1 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Debug)

find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2 REQUIRED IMPORTED_TARGET sdl2)
pkg_check_modules(GLFW REQUIRED IMPORTED_TARGET glfw3)

include(cmake/CPM.cmake)

set(BOOST_VERSION "1.86.0")
set(SPDLOG_VERSION "1.14.1")

CPMAddPackage(
  NAME Boost
  URL "https://github.com/boostorg/boost/releases/download/boost-${BOOST_VERSION}/boost-${BOOST_VERSION}-cmake.tar.xz"
  VERSION ${BOOST_VERSION}
)
CPMAddPackage(
  NAME spdlog
  GITHUB_REPOSITORY "gabime/spdlog"
  VERSION ${SPDLOG_VERSION}
)

if(NOT DEFINED SKIA_ROOT)
  message(FATAL_ERROR "SKIA_ROOT is not set")
endif()

add_subdirectory(src)
