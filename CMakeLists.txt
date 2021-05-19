cmake_minimum_required(VERSION 3.19)
project(scheduling_sim)

set(CMAKE_CXX_STANDARD 17)

add_executable(scheduling_sim main.cpp Scheduler.h RoundRobin.cpp RoundRobin.h Scheduler.cpp)