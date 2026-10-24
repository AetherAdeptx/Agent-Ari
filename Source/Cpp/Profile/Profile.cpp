
#include "Profile.h"

namespace AgentAri
{
    std::uint64_t NetworkProfile::estimatedSynapseCount() const
    {
        return neuronCount * averageSynapsesPerNeuron;
    }
}
