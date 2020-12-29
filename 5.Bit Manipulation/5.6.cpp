// Conversion: Write a function to determine the number of bits you would need to flip to convert
// integer A to integer B.
// EXAMPLE
// Input: 29 (or: 11101), 15 (or: 01111)
// Output: 2

#include <bitset>
#include <limits>
#include <iostream>

template <typename T>
size_t bitSwapRequired(T a, T b)
{
    return std::bitset<std::numeric_limits<T>::digits>(a ^ b).count();
}

int main()
{
    std::cout << bitSwapRequired(0b11101, 0b01111) << std::endl;
}
