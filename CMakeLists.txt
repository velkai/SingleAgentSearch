cmake_minimum_required(VERSION 3.10)
project(SAS)

set(CMAKE_CXX_STANDARD 11)

include_directories(Homework3/Homework3)
include_directories(SingleAgentSearch/Homework3/Homework3)

add_executable(SAS
        Homework3/Homework3/DFID.cpp
        Homework3/Homework3/DFID.h
        Homework3/Homework3/heuristic.cpp
        Homework3/Homework3/heuristic.hpp
        Homework3/Homework3/IDA.cpp
        Homework3/Homework3/IDA.hpp
        Homework3/Homework3/IDAData.hpp
        Homework3/Homework3/main.cpp
        Homework3/Homework3/STP.cpp
        Homework3/Homework3/STP.h
        Homework3/Homework3/Timer.cpp
        Homework3/Homework3/Timer.h
        SingleAgentSearch/Homework3/Homework3/heuristic.cpp
        SingleAgentSearch/Homework3/Homework3/heuristic.hpp
        SingleAgentSearch/Homework3/Homework3/IDA.cpp
        SingleAgentSearch/Homework3/Homework3/IDA.hpp
        SingleAgentSearch/Homework3/Homework3/IDAData.hpp
        SingleAgentSearch/Homework3/Homework3/main.cpp
        SingleAgentSearch/Homework3/Homework3/STP.cpp
        SingleAgentSearch/Homework3/Homework3/STP.h
        SingleAgentSearch/Homework3/Homework3/Timer.cpp
        SingleAgentSearch/Homework3/Homework3/Timer.h)
