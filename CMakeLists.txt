cmake_minimum_required(VERSION 3.0)
project(HW2 CXX)

option(BUILD_FOR_TEST "Build for test" OFF)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories("include/")

set(SRCS
        )

add_executable(${PROJECT_NAME} main.cpp
        ${SRCS}
        )

if (BUILD_FOR_TEST)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov" )
endif ()

enable_testing()

add_subdirectory(Tests)
