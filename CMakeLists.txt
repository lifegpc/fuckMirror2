cmake_minimum_required(VERSION 3.0)

project(fuckmirror2)

if (NOT WIN32)
    message(FATAL_ERROR "WIN32 only.")
endif()

set(ENABLE_ICONV OFF CACHE BOOL "libiconv is not needed.")

add_subdirectory(utils)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/utils)
add_executable(Mirror2.ProjectX.Launcher main.cpp)
target_link_libraries(Mirror2.ProjectX.Launcher utils)
