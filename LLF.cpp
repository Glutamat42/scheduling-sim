//
// Created by markus on 07.06.21.
//

#include "LLF.h"

LLF::LLF(std::vector<Process> processes) : Scheduler(processes) {
    this->stopAfterSteps = Scheduler::getLeastRequiredSteps(processes);
    this->vs = VisualizeSchedule(cv::Point2i(this->stopAfterSteps, processes.size()));
    this->vs.windowTitle = "LLF Scheduler";

    // generate labels for visualization
    std::vector<std::string> primLabels;
    for (int i = 0; i < this->processes.size(); ++i) {
        primLabels.push_back(std::string("T" + std::to_string(i)));
    }
    this->vs.setPrimaryLabels(primLabels);
}

int LLF::chooseNextTask() {
    int pid = -1;
    int laxity = INT32_MAX;

    for (int i = 0; i < this->processes.size(); ++i) {
        int curPLaxity = ceil((double)(this->curStep - this->processes[i].start+1) / this->processes[i].deadline); // index of current interval
        curPLaxity *= this->processes[i].deadline; // next deadline without delayed start
        curPLaxity += this->processes[i].start; // next deadline with delayed start
        curPLaxity -= 1;
        curPLaxity -= this->curStep; //
        if (this->processes[i].remaining > 0 && curPLaxity < laxity) {
            pid = i;
            laxity = curPLaxity;
        }
    }

    // currently no job
    return pid;
}

void LLF::run() {
    while (this->curStep < this->stopAfterSteps - 1) {
        this->curStep++;
        // update remaining times and check deadlines
        for (int i = 0; i < this->processes.size(); ++i) {
            // deadline
            if ((this->curStep - this->processes[i].start) % this->processes[i].deadline == 0 && this->processes[i].remaining > 0) {
                this->vs.setBGColor(cv::Point2i(this->curStep, i), Colors::red);
                std::cout << i << " failed deadline" << std::endl;
            }

            // interval
            if ((this->curStep - this->processes[i].start) % this->processes[i].interval == 0) {
                this->vs.setLeftBorderColor(cv::Point2i(this->curStep, i), Colors::green);
                this->processes[i].remaining += this->processes[i].duration;
            }
        }

        int nextPid = this->chooseNextTask();
        if (nextPid != -1) {
            this->processes[nextPid].remaining -= 1;
            vs.setCross(cv::Point2i(this->curStep, nextPid), true);
        }
    }

    this->vs.show();
}
