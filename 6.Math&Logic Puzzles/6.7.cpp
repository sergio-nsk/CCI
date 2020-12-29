
// The Apocalypse: In the new post-apocalyptic world, the world queen is
// desperately concerned about the birth rate. Therefore, she decrees that all
// families should ensure that they have one girl or else they face massive
// fines. If all families abide by this policy-that is, they have continue to
// have children until they have one girl, at which point they immediately
// stop-what will the gender ratio of the new generation be? (Assume that the
// odds of someone having a boy or a girl on any given pregnancy is equal.)
// Solve this out logically and then write a computer simulation of it.

#include <array>
#include <iostream>
#include <random>

std::array<unsigned, 2> runOneFamily();

double runNFamilies(unsigned n) {
  unsigned boys = 0;
  unsigned girls = 0;

  for (unsigned i = 0; i < n; i++) {
    auto genders = runOneFamily();
    boys += genders[0];
    girls += genders[1];
  }
  return girls / static_cast<double>(boys + girls);
}

std::array<unsigned, 2> runOneFamily() {
  std::random_device
      rd;  // Will be used to obtain a seed for the random number engine
  std::mt19937 gen(rd());  // Standard mersenne_twister_engine seeded with rd()
  std::uniform_int_distribution<> dis(0, 1);

  int boys = 0;
  int girls = 0;
  while (girls == 0)  // until we have a girl
  {
    if (dis(gen)) {
      // girl
      ++girls;
    } else {
      // boy
      ++boys;
    }
  }
  std::array<unsigned, 2> genders;
  genders[0] = boys;
  genders[1] = girls;
  return genders;
}

int main() {
  std::cout << runNFamilies(100'000) << std::endl;
}
