cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)

project (OrderYourMembers)

# Version
set(VERSION_MAJOR 1)
set(VERSION_MINOR 0)

# Export compile database
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Offset
add_executable(offset offset.cpp)
set_property(TARGET offset PROPERTY CXX_STANDARD 11)
target_compile_options(offset PRIVATE -O0)

# Cache Distance
add_executable(cache_distance cache_distance.cpp)
target_compile_options(cache_distance PRIVATE -O0)
set_property(TARGET cache_distance PROPERTY CXX_STANDARD 11)

# Cache Sharing
add_executable(cache_sharing cache_sharing.cpp)
target_compile_options(cache_sharing PRIVATE -O0)
set_property(TARGET cache_sharing PROPERTY CXX_STANDARD 11)
