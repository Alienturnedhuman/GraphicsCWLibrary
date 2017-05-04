cmake_minimum_required(VERSION 3.7)
project(library)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES library.cpp library.h Color.cpp Color.h Texture.cpp Texture.h)
add_library(library ${SOURCE_FILES})