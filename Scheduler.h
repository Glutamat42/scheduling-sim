//
// Created by markus on 19.05.21.
//

#ifndef SCHEDULING_SIM_SCHEDULER_H
#define SCHEDULING_SIM_SCHEDULER_H

#include <utility>
#include <vector>

struct Process {
    int duration{};
    int remaining = 0;
    int start=0;
    int interval{};
    int deadline{};
};

class Scheduler {
protected:
    std::vector<Process> processes;
    virtual int chooseNextTask() = 0;
public:
    explicit Scheduler(std::vector<Process> processes);
    virtual void run() = 0;
};

#endif //SCHEDULING_SIM_SCHEDULER_H
