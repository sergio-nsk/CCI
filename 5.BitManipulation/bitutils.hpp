#include <ostream>
#include <bitset>
#include <limits>

template <typename T, int N = std::numeric_limits<T>::digits>
std::bitset<N> bits(const T &value)
{
    return std::bitset<N>(value);
}
