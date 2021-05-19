#include <iostream>
#include "Scheduler.h"
#include "RoundRobin.h"

int main() {
    int selection;
    Scheduler* scheduler;

    std::cout << "Select scheduler\n1) Round Robin\n2) RMS" << std::endl;
    std::cin >> selection;

    switch (selection) {
        case 1:
            scheduler = new RoundRobin(RoundRobin::getProcessesFromCin());
            break;
        case 2:
        default:
            std::cout << "Not implemented" << std::endl;
            exit(1);
    }

    scheduler->run();


    return 0;
}
