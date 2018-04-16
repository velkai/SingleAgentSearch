cmake_minimum_required(VERSION 3.10)
project(SAS)

set(CMAKE_CXX_STANDARD 11)

include_directories(Homework3/Homework3)

add_executable(SAS
        Homework3/Homework3/STP.h
        Homework3/Homework3/heuristic.h
        Homework3/Homework3/IDA.h
        Homework3/Homework3/Timer.h

        Homework3/Homework3/STP.cpp
        Homework3/Homework3/heuristic.cpp
        Homework3/Homework3/IDA.cpp
        Homework3/Homework3/main.cpp
        Homework3/Homework3/Timer.cpp)
