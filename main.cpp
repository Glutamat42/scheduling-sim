#include <iostream>
#include "Scheduler.h"
#include "RoundRobin.h"
#include "RMS.h"
#include "EDS.h"
#include "LLF.h"

int main() {
    int selection;
    Scheduler* scheduler;

    std::cout << "Select scheduler\n1) Round Robin\n2) RMS - Rate Monotonic Scheduling \n3) EDS - Earliest Deadline First\n4) LLF - Least Laxity First" << std::endl;
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
        case 4:
            scheduler = new LLF(Scheduler::getProcessesFromCin());
            break;
        default:
            std::cout << "Not implemented" << std::endl;
            exit(1);
    }

    scheduler->run();



    delete scheduler;
    return 0;
}
