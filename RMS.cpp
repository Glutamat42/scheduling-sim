//
// Created by markus on 19.05.21.
//

#include "RMS.h"

int RMS::getLeastRequiredSteps(std::vector<Process> processes) {
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


RMS::RMS(std::vector<Process> processes) : Scheduler(processes) {
    this->stopAfterSteps = RMS::getLeastRequiredSteps(processes);
    this->vs = VisualizeSchedule(cv::Point2i(this->stopAfterSteps, processes.size()));
    this->vs.windowTitle = "RMS Scheduler";

    // generate priority list
    for (int i = 0; i < processes.size(); ++i) {
        if (this->priorityList.empty()) {
            this->priorityList.push_back(i);
        } else {
            for (int j = 0; j < this->priorityList.size(); ++j) {
                if (processes[this->priorityList[j]].interval > processes[i].interval) {
                    this->priorityList.insert(this->priorityList.begin() + j, i);
                    break;
                } else if (this->priorityList.size() - 1 == j) {
                    this->priorityList.push_back(i);
                    break;
                }
            }
        }
    }

    std::cout << "priorityList: " << std::endl;
    for (int index: this->priorityList) {
        std::cout << index << " - 1/" << processes[index].interval << std::endl;
    }

    // generate labels for visualization
    std::vector<std::string> primLabels;
    std::vector<std::string> secLabels;
    for (int i = 0; i < this->processes.size(); ++i) {
        primLabels.push_back(std::string("T" + std::to_string(i)));
        secLabels.push_back(std::string("1/" + std::to_string(processes[i].interval)));
    }
    this->vs.setPrimaryLabels(primLabels);
    this->vs.setSecondaryLabels(secLabels);

    this->checkLL();
}

int RMS::chooseNextTask() {
    this->curStep++;
    // update remaining times and check deadlines
    for (int i = 0; i < this->processes.size(); ++i) {
        // deadline
        if ((this->curStep - this->processes[i].start) % this->processes[i].deadline == 0 && this->processes[i].remaining > 0) {
            vs.setBGColor(cv::Point2i(this->curStep, i), Colors::red);
            std::cout << i << " failed deadline" << std::endl;
        }

        // interval
        if ((this->curStep - this->processes[i].start) % this->processes[i].interval == 0) {
            vs.setLeftBorderColor(cv::Point2i(this->curStep, i), Colors::green);
            this->processes[i].remaining += this->processes[i].duration;
        }
    }

    // find next job
    for (int index: this->priorityList) {
        if (this->processes[index].remaining > 0) {
            vs.setCross(cv::Point2i(this->curStep, index), true);
            return index;
        }
    }

    // currently no job
    return -1;
}

void RMS::run() {
    while (this->curStep < this->stopAfterSteps - 1) {
        int nextPid = this->chooseNextTask();
        if (nextPid == -1) {
            std::cout << "currently nothing to do" << std::endl;
        } else {
            this->processes[nextPid].remaining -= 1;
            std::cout << nextPid << " gets this timeslot" << std::endl;
        }

        for (int i = 0; i < this->processes.size(); ++i) {
            Process p = this->processes[i];
            std::cout << "pid: " << i << " Time remaining: " << p.remaining << " Time needed: " << p.duration << std::endl;
        }

        std::cout << "-----------------" << std::endl;
    }


    vs.show();
}

void RMS::checkLL() {
    double utilization = 0;
    for (Process p: this->processes) {
        utilization += (double) p.duration / p.interval;
    }

    int n = this->processes.size();
    double capacityLimit = n * (std::pow(2, (double) 1 / n) - 1);

    std::cout << "\nutilization: " << utilization << " capacity limit: " << capacityLimit << " minimum capacity limit: 0,693" << std::endl;

    if (utilization < capacityLimit) {
        std::cout << "LL check successful" << std::endl;
    } else {
        std::cout << "LL check failed" << std::endl;
    }

    std::cout << "Press return to continue" << std::endl;
//    std::string test;
    std::cin.get();
}

