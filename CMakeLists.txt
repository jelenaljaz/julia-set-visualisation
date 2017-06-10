cmake_minimum_required(VERSION 3.7)
project(julia_set_visualisation)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        .gitattributes
        .gitignore
        bitmap.c
        bitmap.h
        main.c
        README.md
        targetver.h)

add_executable(julia_set_visualisation ${SOURCE_FILES})