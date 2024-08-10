PROJECT(octetos-core)
cmake_minimum_required(VERSION 3.12)

add_definitions(-DLINUX_ARCH -DOCTETOS_CORE_VERSION_MAJOR=3 -DOCTETOS_CORE_VERSION_MINOR=0 -DOCTETOS_CORE_VERSION_PATCH=0 )

if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

add_subdirectory(3)
#add_subdirectory(tests)
