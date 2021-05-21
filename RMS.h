//
// Created by markus on 19.05.21.
//

#ifndef SCHEDULING_SIM_RMS_H
#define SCHEDULING_SIM_RMS_H


#include <string>
#include <iostream>
#include "Scheduler.h"
#include "VisualizeSchedule/VisualizeSchedule.h"

class RMS: public Scheduler {
private:
    int curStep = -1;
    int stopAfterSteps = 35;
    std::vector<int> priorityList;
    int chooseNextTask() override;

    VisualizeSchedule vs;
public:
    explicit RMS(std::vector <Process> processes);

    void run() override;

    static std::vector<Process> getProcessesFromCin();
};


#endif //SCHEDULING_SIM_RMS_H
