cmake_minimum_required(VERSION 3.23)
project(AI_learns_to_drive)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(nlohmann)

add_executable(AI_learns_to_drive
        nlohmann/json.hpp
        nlohmann/json_fwd.hpp
        controls.h
        grid.h
        main.cpp
        map.h
        mousegrid.h
        pallete.h
        sensor.h
        tank.h
        utils.h)
