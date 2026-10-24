#ifndef HARDWARE_PLANNER_H
#define HARDWARE_PLANNER_H

namespace AgentAri
{
    struct HardwareProfile
    {
        unsigned int threadBudget = 10;
        unsigned int ramBudget = 12000;  // MiB
        unsigned int vramBudget = 3500;  // MiB
    };

    HardwareProfile detectHardware();
}

#endif
