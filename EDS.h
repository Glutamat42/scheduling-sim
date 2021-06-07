//
// Created by markus on 06.06.21.
//

#ifndef SCHEDULING_SIM_EDS_H
#define SCHEDULING_SIM_EDS_H


#include <iostream>
#include <numeric>
#include "Scheduler.h"
#include "VisualizeSchedule/VisualizeSchedule.h"

class EDS: public Scheduler {
private:
    VisualizeSchedule vs;
    int curStep = -1;
    int stopAfterSteps;
    int chooseNextTask() override;
    static int getLeastRequiredSteps(std::vector<Process> processes);
public:
    explicit EDS(std::vector <Process> processes);

    void run() override;
};


#endif //SCHEDULING_SIM_EDS_H
