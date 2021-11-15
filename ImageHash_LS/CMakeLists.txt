cmake_minimum_required(VERSION 3.10)
project(wet2)

set(CMAKE_CXX_STANDARD 11)

add_executable(wet2 main.cpp tests.cpp catch.hpp  image.h ImageTagger.cpp ImageTagger.h
        HashImages.cpp HashImages.h PixelLabel.cpp PixelLabel.h image.cpp mapTree.cpp mapTree.h
        nodeTree.cpp nodeTree.h library.cpp library.h)