//
// Created by markus on 19.05.21.
//

#ifndef SCHEDULING_SIM_ROUNDROBIN_H
#define SCHEDULING_SIM_ROUNDROBIN_H


#include "Scheduler.h"
#include "VisualizeSchedule.h"

class RoundRobin: public Scheduler{
private:
    int lastPid = -1;
    VisualizeSchedule vs;
    int chooseNextTask() override;
public:
    explicit RoundRobin(std::vector <Process> processes);

    void run() override;

    static std::vector<Process> getProcessesFromCin();
};


#endif //SCHEDULING_SIM_ROUNDROBIN_H
