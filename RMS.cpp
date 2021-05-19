//
// Created by markus on 19.05.21.
//

#include <string>
#include <iostream>
#include "RMS.h"

RMS::RMS(std::vector<Process> processes) : Scheduler(processes) {
    for (int i = 0; i < processes.size(); ++i) {
        if (this->priorityList.empty()) {
            this->priorityList.push_back(i);
        } else {
            for (int j = 0; j < this->priorityList.size(); ++j) {
                if (processes[this->priorityList[j]].duration > processes[i].duration) {
                    this->priorityList.insert(this->priorityList.begin()+j, i);
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
        std::cout << index << " - 1/" << processes[index].duration << std::endl;
    }
}

int RMS::chooseNextTask() {
    this->curStep++;
    // update remaining times and check deadlines
    for (int i = 0; i < this->processes.size(); ++i) {
        // deadline
        if ((this->curStep - this->processes[i].start) % this->processes[i].deadline == 0 && this->processes[i].remaining > 0) {
            std::cout << i << " failed deadline" << std::endl;
        }

        // interval
        if ((this->curStep - this->processes[i].start) % this->processes[i].interval == 0) {
            this->processes[i].remaining += this->processes[i].duration;
        }
    }

    // find next job
    for (int index: this->priorityList) {
        if (this->processes[index].remaining > 0) {
            return index;
        }
    }

    // currently no job
    return -1;
}

void RMS::run() {
    while (this->curStep < this->stopAfterSteps) {
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
}

std::vector<std::string> split(const std::string& str, const std::string& delim)
{
    std::vector<std::string> tokens;
    size_t prev = 0, pos = 0;
    do
    {
        pos = str.find(delim, prev);
        if (pos == std::string::npos) pos = str.length();
        std::string token = str.substr(prev, pos-prev);
        if (!token.empty()) tokens.push_back(token);
        prev = pos + delim.length();
    }
    while (pos < str.length() && prev < str.length());
    return tokens;
}

std::vector<Process> RMS::getProcessesFromCin() {
    std::vector<Process> plist;
    Process p1 = Process();
    p1.start = 0;
    p1.duration = 4;
    p1.interval = 8;
    p1.deadline = 8;
    Process p2 = Process();
    p2.start = 3;
    p2.duration = 1;
    p2.interval = 5;
    p2.deadline = 5;
    Process p3 = Process();
    p3.start = 5;
    p3.duration = 2;
    p3.interval = 20;
    p3.deadline = 20;
    Process p4 = Process();
    p4.start = 0;
    p4.duration = 3;
    p4.interval = 40;
    p4.deadline = 40;
    plist.push_back(p4);
    plist.push_back(p2);
    plist.push_back(p3);
    plist.push_back(p1);
    return plist;




    std::vector<Process> processes;
    bool finished = false;
    std::cout << "Enter tasks in following format: start,duration,interval,deadline (comma separated, no space)" << "\nempty line if finished" << std::endl;
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
            std::vector<std::string> parsedLine = split(line, ",");
            if (parsedLine.size() != 4) {
                throw std::invalid_argument("start,duration,interval,deadline");
            }
            newProcess.start = std::stoi(parsedLine[0]);
            newProcess.duration = std::stoi(parsedLine[1]);
            newProcess.interval = std::stoi(parsedLine[2]);
            newProcess.deadline = std::stoi(parsedLine[3]);
            if (newProcess.start == 0) {
                newProcess.remaining = newProcess.duration;
            } else {
                newProcess.remaining = 0;
            }

            processes.push_back(newProcess);
        }
    }
    return processes;
}

