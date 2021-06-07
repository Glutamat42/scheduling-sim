#include <iostream>
#include "Scheduler.h"
#include "RoundRobin.h"
#include "RMS.h"
#include "EDS.h"

int main() {
    int selection;
    Scheduler* scheduler;

    std::cout << "Select scheduler\n1) Round Robin\n2) RMS\n3) EDS" << std::endl;
    std::cin >> selection;

    switch (selection) {
        case 1:
            scheduler = new RoundRobin(Scheduler::getProcessesFromCin());
            break;
        case 2:
            scheduler = new RMS(Scheduler::getProcessesFromCin());
            break;
        case 3:
            scheduler = new EDS(Scheduler::getProcessesFromCin());
            break;
        default:
            std::cout << "Not implemented" << std::endl;
            exit(1);
    }

    scheduler->run();



    delete scheduler;
    return 0;
}
