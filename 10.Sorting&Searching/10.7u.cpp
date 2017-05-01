#include "all.hpp"

// Get count of items within each range.
std::vector<int> getCountPerBlock(const std::string &filename, int rangeSize);

// Find a block whose count is low.
int findBlockWithMissing(const std::vector<int> &blocks, int rangeSize);

// Create a bit vector for the values within a specific range.
std::vector<uint8_t> getBitVectorForRange(const std::string &filename, int blockindex, int rangeSize);

// Find a zero within the bit vector and return the index.
int findZero(const std::vector<uint8_t> &bitVector);

int findOpenNumber(std::string filename)
{
    int rangeSize = (1 << 20); // 2^20 bits (2^17 bytes)

    // Get count of number of values within each block.
    auto blocks = getCountPerBlock(filename, rangeSize);

    // Find a block with a missing value.
    int blockIndex  = findBlockWithMissing(blocks, rangeSize);
    if (blockIndex < 0)
        return -1;

    // Create bit vector for items within this range.
    auto bitVector = getBitVectorForRange(filename, blockIndex, rangeSize);

    // Find a zero in the bit vector
    int offset = findZero(bitVector);
    if (offset < 0)
        return -1;

    // Compute missing value.
    return blockIndex * rangeSize + offset;
}

std::vector<int> getCountPerBlock(const std::string &filename, int rangeSize)
{
    int arraySize = std::numeric_limits<int>::max() / rangeSize + 1;
    std::vector<int> blocks(arraySize);
    std::fstream in(filename, std::fstream::in);
    if (!in.is_open())
    {
        std::cerr << "Can not open file " << filename << std::endl;
        return blocks;
    }
    int value = 0;
    while (in >> value)
    {
        blocks[value / rangeSize]++;
    }
    in.close();
    return blocks;
}

int findBlockWithMissing(const std::vector<int> &blocks, int rangeSize)
{
    for (unsigned i = 0; i < blocks.size(); i++)
    {
        if (blocks[i] < rangeSize)
        {
            return i;
        }
    }
    return -1;
}

std::vector<uint8_t> getBitVectorForRange(const std::string &filename, int blockindex, int rangeSize)
{
    int startRange = blockindex * rangeSize;
    int endRange = startRange + rangeSize;
    std::vector<uint8_t> bitVector(rangeSize / std::numeric_limits<uint8_t>::digits);
    std::fstream in(filename, std::fstream::in);
    int value = 0;
    while (in >> value)
    {
        // If the number is inside the block that's missing numbers, we record it
        if (startRange <= value && value < endRange)
        {
            int offset = value - startRange;
            int mask = (1 << (offset % std::numeric_limits<uint8_t>::digits));
            bitVector[offset / std::numeric_limits<uint8_t>::digits] |= mask;
        }
    }
    in.close();
    return bitVector;
}

// Find bit index that is 0 within byte.
int findZero(uint8_t b)
{
    for (int i = 0; i < std::numeric_limits<uint8_t>::digits; i++)
    {
        int mask = 1 << i;
        if ((b & mask) == 0)
        {
            return i;
        }
    }
    return -1;
}

int findZero(const std::vector<uint8_t> &bitVector)
{
    for (unsigned i = 0; i < bitVector.size(); i++)
    {
        if (bitVector[i] != std::numeric_limits<uint8_t>::max())
        {
            // If not all bits are 1
            int bitindex = findZero(bitVector[i]);
            return i * std::numeric_limits<uint8_t>::digits + bitindex;
        }
    }
    return -1;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
        return -1;
    std::cout << findOpenNumber(argv[1]) << std::endl;
}
