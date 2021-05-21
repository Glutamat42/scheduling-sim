cmake_minimum_required(VERSION 3.16)
project(scheduling_sim)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(scheduling_sim main.cpp Scheduler.h RoundRobin.cpp RoundRobin.h Scheduler.cpp RMS.cpp RMS.h VisualizeSchedule/VisualizeSchedule.cpp VisualizeSchedule/VisualizeSchedule.h VisualizeSchedule/Colors.cpp VisualizeSchedule/Colors.h VisualizeSchedule/MapField.cpp VisualizeSchedule/MapField.h VisualizeSchedule/constants.h)
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})