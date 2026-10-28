
#ifndef NEURON_H
#define NEURON_H

#include <array>
#include <cstddef>
#include <cstdint>

namespace AgentAri
{
    class Neuron
    {
    public:
        static constexpr std::size_t ID_BYTES = 6;

        static constexpr std::size_t MAX_INPUT_SYNAPSES = 128;
        static constexpr std::size_t MAX_OUTPUT_SYNAPSES = 128;

        static constexpr std::size_t PROGRAM_MEMORY_BITS = 512;
        static constexpr std::size_t PROGRAM_MEMORY_BYTES =
            PROGRAM_MEMORY_BITS / 8;

        static constexpr std::size_t WORKSPACE_BITS = 1024;
        static constexpr std::size_t WORKSPACE_BYTES =
            WORKSPACE_BITS / 8;

        Neuron();
        virtual ~Neuron();

        // 48-bit neuron ID
        void setNeuronId(std::uint64_t id);
        std::uint64_t getNeuronId() const;

        // 8-bit properties
        void setWeight(std::int8_t weight);
        std::int8_t getWeight() const;

        void setImportance(std::int8_t importance);
        std::int8_t getImportance() const;

        // 16-bit relative synapse addresses
        bool setInputSynapse(
            std::size_t index,
            std::uint16_t address);

        bool getInputSynapse(
            std::size_t index,
            std::uint16_t& address) const;

        bool setOutputSynapse(
            std::size_t index,
            std::uint16_t address);

        bool getOutputSynapse(
            std::size_t index,
            std::uint16_t& address) const;

        // Program memory: individual bits and bytes
        bool setProgramBit(std::size_t bitIndex, bool value);
        bool getProgramBit(std::size_t bitIndex, bool& value) const;

        bool writeProgramByte(
            std::size_t byteIndex,
            std::uint8_t value);

        bool readProgramByte(
            std::size_t byteIndex,
            std::uint8_t& value) const;

        // Workspace: individual bits and bytes
        bool setWorkspaceBit(std::size_t bitIndex, bool value);
        bool getWorkspaceBit(std::size_t bitIndex, bool& value) const;

        bool writeWorkspaceByte(
            std::size_t byteIndex,
            std::uint8_t value);

        bool readWorkspaceByte(
            std::size_t byteIndex,
            std::uint8_t& value) const;

    protected:
        // Available to derived neuron types.

    private:
        // Bit-packed 48-bit identifier, stored in six bytes.
        std::array<std::uint8_t, ID_BYTES> id_;

        std::int8_t weight_;
        std::int8_t importance_;

        // Each entry is one 16-bit relative address.
        std::array<std::uint16_t, MAX_INPUT_SYNAPSES> inputSynapses_;
        std::array<std::uint16_t, MAX_OUTPUT_SYNAPSES> outputSynapses_;

        // Fixed-size memory owned by this neuron.
        std::array<std::uint8_t, PROGRAM_MEMORY_BYTES> programMemory_;
        std::array<std::uint8_t, WORKSPACE_BYTES> workspace_;
    };
}

#endif // NEURON_H

