
#ifndef PROFILE_H
#define PROFILE_H

#include <cstdint>
#include <string>

namespace AgentAri
{
    struct NetworkProfile
    {
        // Profile identity
        std::string profileName = "Test Profile";
        std::string description =
            "Test profile for AgentAri development.";

        // Network size
        std::uint64_t neuronCount = 10'000'000;

        // Network composition
        double immutableNeuronRatio = 0.01;

        // Processing limits
        std::uint32_t rateLimitCPU = 75;

        // Checkpoint management
        std::uint32_t checkpointFrequency = 500;
        std::uint32_t numCheckpoints = 5;

        // Logging
        std::uint32_t logLevel = 3;

        // Total allocated synapse capacity across the network
        std::uint64_t estimatedSynapseCount() const;
    };
}

#endif // PROFILE_H
