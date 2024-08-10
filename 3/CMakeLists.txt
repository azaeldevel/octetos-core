PROJECT(liboctetos-core-3)
cmake_minimum_required(VERSION 3.12)

set(VCPKG_ROOT $ENV{VCPKG_ROOT})
include(${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake)

FIND_PACKAGE(PkgConfig REQUIRED)
find_package(libconfig CONFIG REQUIRED)

add_library(octetos-core-3 SHARED Buffer.cc Configuration.cc numbers.cc platform.cc string.cc tree.cc version.cc)
target_link_libraries(octetos-core-3 PRIVATE libconfig::config libconfig::config++)
set_property(TARGET octetos-core-3 PROPERTY CXX_STANDARD 20)
