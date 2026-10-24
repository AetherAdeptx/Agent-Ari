
#ifndef PROFILE_H
#define PROFILE_H

#include <cstdint>
#include <string>

namespace AgentAri
{
    struct NetworkProfile
    {
        std::string profileName = "Test Profile";
        std::string description = "Test Profile for building source.";
        std::string filePath = "/home/Ari/Desktop/AgentAriProject/AgentAri/Scratchpad/";

        std::uint64_t neuronCount = 10'000'000;
        std::uint32_t averageSynapsesPerNeuron = 256;
        std::uint32_t layers = 28;
        double immutableNeuronRatio = 0.01;

        std::uint32_t rateLimitCPU = 50;
        std::uint32_t checkpointFrequency = 500;
        std::uint32_t numCheckpoints = 5;
        std::uint32_t logLevel = 3;

        std::uint64_t estimatedSynapseCount() const;
    };
}

#endif
