## SPDX-License-Identifier: MIT

cmake_minimum_required(VERSION 3.16)

set(PROJECT_NAME numero)
project(${PROJECT_NAME} LANGUAGES CXX)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
    message(STATUS "Build type not specified: Use Release by default.")
endif(NOT CMAKE_BUILD_TYPE)

find_package(Boost 1.71 REQUIRED COMPONENTS
             date_time program_options)

add_executable(${PROJECT_NAME} ${SRC_FILES})
target_sources(${PROJECT_NAME}
    PRIVATE
        numero/entity.h
        numero/entity.cpp
        numero/group.cpp
        numero/group.h
        numero/holiday.h
        numero/holiday.cpp
        numero/numero.h
        numero/numero.cpp
        numero/time_unit.h
        numero/time_unit.cpp)

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES)

target_link_libraries(${PROJECT_NAME} Boost::date_time Boost::program_options)
