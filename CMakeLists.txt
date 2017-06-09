cmake_minimum_required(VERSION 3.5)
project(julia_set_visualisation)

set(SOURCE_FILES
    bitmap.c
    bitmap.h
    main.c
    targetver.h)

add_executable(julia_set_visualisation ${SOURCE_FILES})