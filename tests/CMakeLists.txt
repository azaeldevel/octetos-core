PROJECT(octetos-core-TDD)
cmake_minimum_required(VERSION 3.12)

add_definitions(-DOCTETOS_CORE_V3_TDD)


FIND_PACKAGE(PkgConfig REQUIRED)
FIND_PACKAGE(libconfig CONFIG REQUIRED)
FIND_PACKAGE(cunit CONFIG REQUIRED)

add_executable(TDD-3 main.cc v3.cc)
target_link_libraries(TDD-3 PRIVATE libconfig::config libconfig::config++ unofficial::cunit::cunit)
set_property(TARGET TDD-3 PROPERTY CXX_STANDARD 20)
