//
// Created by markus on 19.05.21.
//

#include "Scheduler.h"

Scheduler::Scheduler(std::vector<Process> processes) {
    this->processes = std::move(processes);
}

std::vector<std::string> split(const std::string &str, const std::string &delim) {
    std::vector<std::string> tokens;
    size_t prev = 0, pos = 0;
    do {
        pos = str.find(delim, prev);
        if (pos == std::string::npos) pos = str.length();
        std::string token = str.substr(prev, pos - prev);
        if (!token.empty()) tokens.push_back(token);
        prev = pos + delim.length();
    } while (pos < str.length() && prev < str.length());
    return tokens;
}

std::vector<Process> Scheduler::getProcessesFromCin() {
    std::vector<Process> processes;
    bool finished = false;
    std::cout << "Enter tasks in following format: start,duration,interval,deadline (comma separated, no space)"
              << "\nempty line if finished\nIf you dont enter any data (press return without entering data) some example data will be used\n"
              << "Omitted values will have default values. Eg for Round Robin it would be enough to enter the first two values 'start,duration'"
              << std::endl;

    std::cin.ignore(); // remove what ever might still be in stdin buffer. Another way would be cin.get()

    while (!finished) {
        std::string line;
        std::getline(std::cin, line);

        if (line.empty()) {
            finished = true;
        } else {
            // parse process line
            Process newProcess = Process();
            std::vector<std::string> parsedLine = split(line, ",");

            if (parsedLine.size() < 2) {
                throw std::invalid_argument("at least start,duration is required");
            } else if (parsedLine.size() > 4) {
                throw std::invalid_argument("there are only 4 parameters start,duration,interval,deadline defined");
            }

            newProcess.start = std::stoi(parsedLine[0]);
            newProcess.duration = std::stoi(parsedLine[1]);
            if (parsedLine.size() >= 3) {
                newProcess.interval = std::stoi(parsedLine[2]);
            }
            if (parsedLine.size() >= 4) {
                newProcess.deadline = std::stoi(parsedLine[3]);
            }

            processes.push_back(newProcess);
        }
    }

    // add dummy values if user did not provide any values
    if (processes.empty()) {
        Process p1 = Process();
        Process p2 = Process();
        Process p3 = Process();
//        p1.start = 0;
//        p1.duration = 1;
//        p1.interval = 3;
//        p1.deadline = 3;
//        p2.start = 0;
//        p2.duration = 2;
//        p2.interval = 5;
//        p2.deadline = 5;
//        p3.start = 0;
//        p3.duration = 2;
//        p3.interval = 9;
//        p3.deadline = 9;
        p1.start = 0;
        p1.duration = 2;
        p1.interval = 10;
        p1.deadline = 10;
        p2.start = 1;
        p2.duration = 1;
        p2.interval = 9;
        p2.deadline = 9;
        p3.start = 0;
        p3.duration = 4;
        p3.interval = 18;
        p3.deadline = 18;
        processes.push_back(p1);
        processes.push_back(p2);
        processes.push_back(p3);
    }

    return processes;
}

int Scheduler::getLeastRequiredSteps(std::vector<Process> processes) {
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
