
#include "Neuron.h"

namespace AgentAri
{
    Neuron::Neuron()
        : id_{},
          weight_(0),
          importance_(0),
          inputSynapses_{},
          outputSynapses_{},
          programMemory_{},
          workspace_{}
    {
    }

    Neuron::~Neuron() = default;

    // --------------------------------------------------
    // 48-bit neuron ID
    // --------------------------------------------------

    void Neuron::setNeuronId(std::uint64_t id)
    {
        // Keep only the lowest 48 bits.
        id &= 0xFFFFFFFFFFFFULL;

        // Store the ID in little-endian byte order.
        for (std::size_t i = 0; i < ID_BYTES; ++i)
        {
            id_[i] = static_cast<std::uint8_t>(
                (id >> (i * 8)) & 0xFFULL);
        }
    }

    std::uint64_t Neuron::getNeuronId() const
    {
        std::uint64_t id = 0;

        for (std::size_t i = 0; i < ID_BYTES; ++i)
        {
            id |= static_cast<std::uint64_t>(id_[i])
                  << (i * 8);
        }

        return id;
    }

    // --------------------------------------------------
    // 8-bit properties
    // --------------------------------------------------

    void Neuron::setWeight(std::int8_t weight)
    {
        weight_ = weight;
    }

    std::int8_t Neuron::getWeight() const
    {
        return weight_;
    }

    void Neuron::setImportance(std::int8_t importance)
    {
        importance_ = importance;
    }

    std::int8_t Neuron::getImportance() const
    {
        return importance_;
    }

    // --------------------------------------------------
    // Input synapses
    // --------------------------------------------------

    bool Neuron::setInputSynapse(
        std::size_t index,
        std::uint16_t address)
    {
        if (index >= MAX_INPUT_SYNAPSES)
        {
            return false;
        }

        inputSynapses_[index] = address;
        return true;
    }

    bool Neuron::getInputSynapse(
        std::size_t index,
        std::uint16_t& address) const
    {
        if (index >= MAX_INPUT_SYNAPSES)
        {
            return false;
        }

        address = inputSynapses_[index];
        return true;
    }

    // --------------------------------------------------
    // Output synapses
    // --------------------------------------------------

    bool Neuron::setOutputSynapse(
        std::size_t index,
        std::uint16_t address)
    {
        if (index >= MAX_OUTPUT_SYNAPSES)
        {
            return false;
        }

        outputSynapses_[index] = address;
        return true;
    }

    bool Neuron::getOutputSynapse(
        std::size_t index,
        std::uint16_t& address) const
    {
        if (index >= MAX_OUTPUT_SYNAPSES)
        {
            return false;
        }

        address = outputSynapses_[index];
        return true;
    }

    // --------------------------------------------------
    // Internal bit-packing helpers
    // --------------------------------------------------

    namespace
    {
        bool writeBit(
            std::uint8_t* memory,
            std::size_t bitCount,
            std::size_t bitIndex,
            bool value)
        {
            if (bitIndex >= bitCount)
            {
                return false;
            }

            const std::size_t byteIndex = bitIndex / 8;
            const unsigned int bitOffset =
                static_cast<unsigned int>(bitIndex % 8);

            const std::uint8_t mask =
                static_cast<std::uint8_t>(1U << bitOffset);

            if (value)
            {
                memory[byteIndex] |= mask;
            }
            else
            {
                memory[byteIndex] &=
                    static_cast<std::uint8_t>(~mask);
            }

            return true;
        }

        bool readBit(
            const std::uint8_t* memory,
            std::size_t bitCount,
            std::size_t bitIndex,
            bool& value)
        {
            if (bitIndex >= bitCount)
            {
                return false;
            }

            const std::size_t byteIndex = bitIndex / 8;
            const unsigned int bitOffset =
                static_cast<unsigned int>(bitIndex % 8);

            value = (memory[byteIndex] &
                     static_cast<std::uint8_t>(1U << bitOffset)) != 0;

            return true;
        }
    }

    // --------------------------------------------------
    // Program memory
    // --------------------------------------------------

    bool Neuron::setProgramBit(
        std::size_t bitIndex,
        bool value)
    {
        return writeBit(
            programMemory_.data(),
            PROGRAM_MEMORY_BITS,
            bitIndex,
            value);
    }

    bool Neuron::getProgramBit(
        std::size_t bitIndex,
        bool& value) const
    {
        return readBit(
            programMemory_.data(),
            PROGRAM_MEMORY_BITS,
            bitIndex,
            value);
    }

    bool Neuron::writeProgramByte(
        std::size_t byteIndex,
        std::uint8_t value)
    {
        if (byteIndex >= PROGRAM_MEMORY_BYTES)
        {
            return false;
        }

        programMemory_[byteIndex] = value;
        return true;
    }

    bool Neuron::readProgramByte(
        std::size_t byteIndex,
        std::uint8_t& value) const
    {
        if (byteIndex >= PROGRAM_MEMORY_BYTES)
        {
            return false;
        }

        value = programMemory_[byteIndex];
        return true;
    }

    // --------------------------------------------------
    // Workspace memory
    // --------------------------------------------------

    bool Neuron::setWorkspaceBit(
        std::size_t bitIndex,
        bool value)
    {
        return writeBit(
            workspace_.data(),
            WORKSPACE_BITS,
            bitIndex,
            value);
    }

    bool Neuron::getWorkspaceBit(
        std::size_t bitIndex,
        bool& value) const
    {
        return readBit(
            workspace_.data(),
            WORKSPACE_BITS,
            bitIndex,
            value);
    }

    bool Neuron::writeWorkspaceByte(
        std::size_t byteIndex,
        std::uint8_t value)
    {
        if (byteIndex >= WORKSPACE_BYTES)
        {
            return false;
        }

        workspace_[byteIndex] = value;
        return true;
    }

    bool Neuron::readWorkspaceByte(
        std::size_t byteIndex,
        std::uint8_t& value) const
    {
        if (byteIndex >= WORKSPACE_BYTES)
        {
            return false;
        }

        value = workspace_[byteIndex];
        return true;
    }
}

