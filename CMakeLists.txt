cmake_minimum_required(VERSION 3.10)

project(mkvparser LANGUAGES C VERSION 0.0.0)

# Compiler Config
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)  

# Build Options
option(BUILD_SHARED_LIBS "Build shared libraries (rather than static ones)" OFF)

add_library(uebml
    ${CMAKE_CURRENT_SOURCE_DIR}/src/uebml.c
)

target_include_directories(uebml PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_executable(mkvdump
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/dump.c
)

target_link_libraries(mkvdump PRIVATE uebml)
