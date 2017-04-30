// Missing Int: Given an input file with four billion non-negative integers, provide an algorithm to
// generate an integer that is not contained in the file. Assume you have 1 GB of memory available for
// this task.
// FOLLOW UP
// What if you have only 1O MB of memory? Assume that all the values are distinct and we now have
// no more than one billion non-negative integers.

#include "all.hpp"

constexpr long numberOfInts = static_cast<long>(std::numeric_limits<int>::max()) + 1;
std::array<uint8_t, numberOfInts / 8> bitfield;

void findOpenNumber()
{
    int n = 0;
    while (std::cin >> n)
    {
        /* Finds the corresponding number in the bitfield by using the OR operator to
         * set the nth bit of a byte (e.g., 10 would correspond to the 2nd bit of
         * index 2 in the byte array). */
        bitfield[n / 8] |= 1 << (n % 8);
    }
    for (unsigned i = 0; i < bitfield.size(); ++i)
    {
        for (int j = 0; j < 8; j++)
        {
            /* Retrieves the individual bits of each byte. When 0 bit is found, print
             * the corresponding value. */
            if ((bitfield[i] & (1 << j)) == 0)
            {
                std::cout << i * 8 + j << std::endl;
                return;
            }
        }
    }
}

int main()
{
    findOpenNumber();
}
