cmake_minimum_required(VERSION 3.16)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(mintty LANGUAGES CXX)

add_executable(mintty 
    src/main.cpp
    src/mintty.cpp
)
target_compile_features(mintty PRIVATE cxx_std_17)
target_include_directories(mintty PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
