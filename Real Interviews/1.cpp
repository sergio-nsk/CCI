// A data source generates a continueuse stream of data packets of varying length, These are to be passed
// through a processor that requires fixed-length blocks. The data is in the form of a sequence of complex
// numbers encoded as a pair of float values.
// Write a class that accepts variable length packets, generates fixed length packets and passes these to an
// internal 'process' method. No assumptions should be made about the sizes or relative sizes of the packets
// to be processed or the size of packets arriving.

#include <random>
#include <array>
#include <vector>
#include <memory>
#include <deque>
#include <future>
#include <cassert>
#include <iostream>
#include <unistd.h>

using ComplexNumber = std::array<float, 2>;

//
// Generates randomly sized packets with randmom complex numbers
//
class RundomGenerator
{
public:
    static void init()
    {
        std::random_device randomDevice;
        randomEngine = std::mt19937(randomDevice());
        randomGenerator = std::uniform_real_distribution<float>(); // Let [0, 1) floats by default
    }

    // Fill max N complex numbers
    static size_t fillPacket(ComplexNumber *buffer, size_t N)
    {
        size_t count = std::uniform_int_distribution<size_t>(1, N)(randomEngine); // Let packet size from 1 till N randomly
        for (size_t i = 0; i < count; ++i, ++buffer)
        {
            auto complex = getComplexNumber();
            (*buffer)[0] = complex[0];
            (*buffer)[1] = complex[1];
        }
        return count;
    }

    RundomGenerator() = delete;

private:
    static std::array<float, 2> getComplexNumber()
    {
        return {randomGenerator(randomEngine), randomGenerator(randomEngine)};
    }

    static std::mt19937 randomEngine;
    static std::uniform_real_distribution<float> randomGenerator;
};

//
// Sends data in fixed packets of N complex numbers.
//
template <size_t N, class Processor>
class Transmitter
{
public:
    Transmitter(Processor &p) : process(p)
    {
        outBuffer.reserve(N);
    }

    // Push received data to transmitter
    void push(const ComplexNumber *packet, size_t count)
    {
        while (count-- > 0)
        {
            outBuffer.push_back(*packet++);

            if (outBuffer.size() == N)
            {
                processFuture = send();
                outBuffer.reserve(N);
            }
        }
    }

    // Wait until transmitter sends all data.
    size_t wait()
    {
        auto left = outBuffer.size();
#if 0
        // If not enough data left to fill buffer of N complex numbers, data is padded with (NaN, NaN).
        if (!outBuffer.empty())
        {
            float NaN = std::nanf("");
            while (outBuffer.size() != N)
                outBuffer.push_back({NaN, NaN});
            processFuture = send();
        }
#endif
        if (processFuture.valid())
            processFuture.get();
        return left;
    }

private:
    // Send fixed buffer asynchronously.
    std::future<size_t> send()
    {
        // Do not hold push(), thus call process() asynchronously
        std::vector<ComplexNumber> out;
        out.swap(outBuffer);
        auto call = [](Processor process, std::vector<ComplexNumber> &&out)
        {
            assert(out.size() == N);
            process(&out[0], N);
            return N;
        };
        return std::async(std::launch::async, call, process, std::move(out));
    }

    std::vector<ComplexNumber> outBuffer;
    Processor process;
    std::future<size_t> processFuture;
};

// Prohibit N = 0
template <class Processor>
class Transmitter<0, Processor>
{
public:
    Transmitter() = delete;
};

std::mt19937 RundomGenerator::randomEngine;
std::uniform_real_distribution<float> RundomGenerator::randomGenerator;

// Sample process() operator. Counts sent complex numbers
struct Processor
{
    Processor(std::atomic_size_t &c) : count(c)
    {

    }

    size_t operator()(const ComplexNumber *buffer, size_t count)
    {
        return (this->count += count);
    }

private:
    std::atomic_size_t &count;
};


int main()
{
    RundomGenerator::init();

    size_t ReceivedNumberCount = 0;
    std::atomic_size_t SentNumberCount;
    Processor processor(SentNumberCount);

    std::array<ComplexNumber, 1000> buffer;
    Transmitter<10, Processor> transmitter(processor);

    for (int i = 0; i < 100; ++i)
    {
        auto count = RundomGenerator::fillPacket(buffer.data(), buffer.size());
        ReceivedNumberCount += count;
        transmitter.push(buffer.data(), count);
    }

    auto &&left = transmitter.wait();
    std::cout << "Received " << ReceivedNumberCount << " complex numbers" << std::endl;
    std::cout << "Transmitted " << SentNumberCount << " complex numbers";
    if (left > 0)
        std::cout << ", " << left << " left pending";
    std::cout << std::endl;
    return 0;
}
