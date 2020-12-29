#include <bitset>
#include <limits>
#include <ostream>

template <typename T, int N = std::numeric_limits<T>::digits>
std::bitset<N> bits(const T& value) {
  return std::bitset<N>(value);
}

template <typename T>
size_t countBits(T v) {
  // return std::bitset<std::numeric_limits<T>::digits>(v).count();

  static_assert(std::is_unsigned<T>::value, "T must be unsigned integral type");
  static_assert(std::numeric_limits<T>::digits <= 64,
                "Max 64 bits of T supported");

  constexpr const T m5 = static_cast<T>(0x5555555555555555U);
  constexpr const T m3 = static_cast<T>(0x3333333333333333U);
  constexpr const T m0F = static_cast<T>(0x0F0F0F0F0F0F0F0FU);
  v = v - ((v >> 1) & m5);         // put count of each 2 bits into those 2 bits
  v = (v & m3) + ((v >> 2) & m3);  // put count of each 4 bits into those 4 bits
  v = (v + (v >> 4)) & m0F;        // put count of each byte bits into those bytes
#if 0
    constexpr const T m01 = static_cast<T>(0x0101010101010101U);
    v = (v * m01);                 // B7B6..B0 --> (B7+B6+...+B0) + (B6+B5+...+B0) + ... + B0
    return v >> (std::numeric_limits<T>::digits - 8);
#else
  if constexpr (std::numeric_limits<T>::digits > 8)
    v = (v + (v >> 8));
  if constexpr (std::numeric_limits<T>::digits > 16)
    v = (v + (v >> 16));
  if constexpr (std::numeric_limits<T>::digits > 32)
    v = (v + (v >> 32));
  return v & 0xFF;
#endif
}

unsigned IsCompact(unsigned x) {
#if 1
  return (x & (x + (x & static_cast<unsigned>(-static_cast<long long>(x))))) ==
         0;

  // 00111111000000000000000000000000 is compact
  // 00111111000000000000000011000000 is not compact
  // x & -x gives the lowest bit set in x (or zero if x is zero).
  // x + (x & -x) converts the lowest string of consecutive 1s to a single 1 (or
  // wraps to zero).
  // x & x + (x & -x) clears those 1 bits.
  // (x & x + (x & -x)) == 0 tests whether any other 1 bits remain.
  // Longer:
  //
  // -x equals ~x+1. After the bits are flipped in ~x, adding 1 carries so that
  // it flips back the low 1 bits in ~x and the first 0 bit but then stops.
  // Thus, the low bits of -x up to and including its first 1 are the same as
  // the low bits of x, but all higher bits are flipped. (Example: ~10011100
  // gives 01100011, and adding 1 gives 01100100, so the low 100 are the same,
  // but the high 10011 are flipped to 01100.) Then x & -x gives us the only bit
  // that is 1 in both, which is that lowest 1 bit (00000100). (If x is zero, x
  // & -x is zero.)
  //
  // Adding this to x causes a carry through all the consecutive 1s, changing
  // them to 0s. It will leave a 1 at the next higher 0 bit (or carry through the
  // high end, leaving a wrapped total of zero) (10100000.)
  //
  // When this is ANDed with x, there are 0s in the places where the 1s were
  // changed to 0s (and also where the carry changed a 0 to a 1). So the result
  // is not zero only if there is another 1 bit higher up.
#else
  unsigned const y = x | (x - 1);
  // Test if the 1's is one solid block.
  return !(y & (y + 1));
#endif
}
