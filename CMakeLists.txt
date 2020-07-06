cmake_minimum_required(VERSION 3.5)

if(DEFINED ENV{VCPKG_ROOT})
     if(${CMAKE_GENERATOR_PLATFORM} STREQUAL "x64")
         set(VCPKG_TARGET_TRIPLET "x64-windows" CACHE FILEPATH "vcpkg triplet")
     else()
         set(VCPKG_TARGET_TRIPLET "x86-windows" CACHE FILEPATH "vcpkg triplet")
     endif()
     if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
         set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
     endif()
 endif()

project(agent LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(Boost REQUIRED COMPONENTS
    system
)

include_directories(${Boost_INCLUDE_DIRS})


add_executable(agent main.cpp)
