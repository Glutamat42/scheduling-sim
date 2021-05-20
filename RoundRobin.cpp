//
// Created by markus on 19.05.21.
//

#include "RoundRobin.h"

#include <utility>
#include <iostream>

RoundRobin::RoundRobin(std::vector<Process> processes) : Scheduler(processes), vs(cv::Point2i(10, processes.size())) {

}

int RoundRobin::chooseNextTask() {
    int nextPid;

    // first guess pid
    if (this->lastPid == -1) {
        nextPid = 0;
    } else {
        nextPid = (this->lastPid + 1) % this->processes.size();
    }

    // now find next pid which has still work tbd
    for (int i = 0; i <= this->processes.size() - 1; ++i) {
        if (this->processes[nextPid].remaining > 0) {
            // current "nextPid" has still work tbd
            return nextPid;
        } else {
            nextPid = (nextPid + 1) % this->processes.size();
        }
    }
    // no processes left -> finished
    return -1;
}

std::vector<Process> RoundRobin::getProcessesFromCin() {
    std::vector<Process> processes;
    bool finished = false;
    std::cout << "Enter tasks in following format: duration" << "\nempty line if finished" << std::endl;
    while (!finished) {
        std::string line;
        std::getline(std::cin, line);

        if (line.empty()) {
            if (processes.empty()) {
                continue;
            }
            finished = true;
        } else {
            // parse process line
            Process newProcess = Process();
            newProcess.duration = std::stoi(line);
            newProcess.remaining = newProcess.duration;

            processes.push_back(newProcess);
        }
    }
    return processes;
}

void RoundRobin::run() {
    int nextPid = this->chooseNextTask();
    int step = 0;
    while (nextPid != -1) {
        // update current process
        this->processes[nextPid].remaining -= 1;


        // update visualization
        if (this->vs.getMatrixBounds().x <= step) { // if vs is too small increase it
            this->vs.resizeColumns(5);
        }
        this->vs.setCross(cv::Point2i(step, nextPid), true);


        // terminal log of whats happening
        for (int i = 0; i < this->processes.size(); ++i) {
            Process p = this->processes[i];
            std::cout << "pid: " << i << " Time computed: " << p.duration - p.remaining << " Time needed: " << p.duration << std::endl;
        }
        // log if a process finished
        if (this->processes[nextPid].remaining == 0) {
            std::cout << nextPid << " finished" << std::endl;
            this->vs.setBGColor(cv::Point2i(step, nextPid), Colors::green);
        }
        std::cout << "-----------------" << std::endl;


        // safe loop state
        this->lastPid = nextPid;
        step++;

        // prepare next iteration
        nextPid = this->chooseNextTask();
    }

    this->vs.show();

    std::cout << "finished process queue" << std::endl;
}
