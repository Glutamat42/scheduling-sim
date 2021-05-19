//
// Created by markus on 19.05.21.
//

#ifndef SCHEDULING_SIM_RMS_H
#define SCHEDULING_SIM_RMS_H


#include "Scheduler.h"

class RMS: public Scheduler {
private:
    int curStep = -1;
    int stopAfterSteps = 20;
    std::vector<int> priorityList;
    int chooseNextTask() override;
public:
    explicit RMS(std::vector <Process> processes);

    void run() override;

    static std::vector<Process> getProcessesFromCin();
};


#endif //SCHEDULING_SIM_RMS_H
