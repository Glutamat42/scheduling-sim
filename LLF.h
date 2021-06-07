//
// Created by markus on 07.06.21.
//

#ifndef SCHEDULING_SIM_LLF_H
#define SCHEDULING_SIM_LLF_H

#include <iostream>
#include <numeric>
#include "Scheduler.h"
#include "VisualizeSchedule/VisualizeSchedule.h"


class LLF: public Scheduler {
private:
    VisualizeSchedule vs;
    int curStep = -1;
    int stopAfterSteps;
    int chooseNextTask() override;
public:
    explicit LLF(std::vector <Process> processes);

    void run() override;
};


#endif //SCHEDULING_SIM_LLF_H
