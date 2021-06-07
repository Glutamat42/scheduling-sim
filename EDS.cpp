//
// Created by markus on 06.06.21.
//

#include "EDS.h"

EDS::EDS(std::vector<Process> processes) : Scheduler(processes) {
    this->stopAfterSteps = EDS::getLeastRequiredSteps(processes);
    this->vs = VisualizeSchedule(cv::Point2i(this->stopAfterSteps, processes.size()));
    this->vs.windowTitle = "EDS Scheduler";

    // generate labels for visualization
    std::vector<std::string> primLabels;
    for (int i = 0; i < this->processes.size(); ++i) {
        primLabels.push_back(std::string("T" + std::to_string(i)));
    }
    this->vs.setPrimaryLabels(primLabels);
}

int EDS::chooseNextTask() {
    int pid = -1;
    int deadline = INT32_MAX;

    for (int i = 0; i < this->processes.size(); ++i) {
        int curPDeadline = ceil((double)(this->curStep - this->processes[i].start+1) / this->processes[i].deadline); // index of current interval
        curPDeadline *= this->processes[i].deadline; // next deadline without delayed start
        curPDeadline += this->processes[i].start; // next deadline with delayed start
        curPDeadline -= 1;
        if (this->processes[i].remaining > 0 && curPDeadline < deadline) {
            pid = i;
            deadline = curPDeadline;
        }
    }

    // currently no job
    return pid;
}

void EDS::run() {
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

int EDS::getLeastRequiredSteps(std::vector<Process> processes) {
    int latestStart = 0;
    int leastDuration = 0;

    if (!processes.empty()) {
        latestStart = processes[0].start;
        leastDuration = processes[0].interval;
    }
    if (processes.size() > 1) {
        for (int i = 1; i < processes.size(); ++i) {
            if (processes[i].start > latestStart) {
                latestStart = processes[i].start;
            }
            leastDuration = std::lcm<int, int>(leastDuration, processes[i].interval);
        }
    }

    std::cout << "at least "
              << latestStart + leastDuration
              << " steps are required, "
              << latestStart
              << " is the last starting process + "
              << leastDuration
              << " steps after all processes started"
              << std::endl;

    return latestStart + leastDuration;
}
