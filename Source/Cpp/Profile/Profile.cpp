
#include "Profile.h"
#include "../Neuron/Neuron.h"

namespace AgentAri
{
    std::uint64_t NetworkProfile::estimatedSynapseCount() const
    {
        constexpr std::uint64_t synapsesPerNeuron =
            Neuron::MAX_INPUT_SYNAPSES +
            Neuron::MAX_OUTPUT_SYNAPSES;

        return neuronCount * synapsesPerNeuron;
    }
}
