//
// Created by markus on 19.05.21.
//

#include "Scheduler.h"

Scheduler::Scheduler(std::vector <Process> processes) {
    this->processes = std::move(processes);
}