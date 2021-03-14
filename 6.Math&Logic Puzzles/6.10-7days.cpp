#include <algorithm>
#include <deque>
#include <iostream>
#include <iterator>
#include <list>
#include <random>
#include <vector>
#include "6.10.hpp"

// Add bottle contents to test strips
void runTests(std::list<Bottle>& bottles, std::deque<TestStrip>& testStrips);

// Create number by setting bits with indices specified in positive.
int setBits(const std::list<int>& positive);

// Get test strips that are positive on a particular day.
std::list<int> getPositiveOnDay(const std::deque<TestStrip>& testStrips,
                                int day);

int findPoisonedBottle(std::list<Bottle>& bottles,
                       std::deque<TestStrip>& strips) {
  runTests(bottles, strips);
  auto positive = getPositiveOnDay(strips, 7);
  return setBits(positive);
}

void runTests(std::list<Bottle>& bottles, std::deque<TestStrip>& testStrips) {
  for (auto& bottle : bottles) {
    int id = bottle.getId();
    int bitindex = 0;
    while (id > 0) {
      if ((id & 1) == 1)
        testStrips.at(bitindex).addDropOnDay(0, bottle);
      ++bitindex;
      id >>= 1;
    }
  }
}

std::list<int> getPositiveOnDay(const std::deque<TestStrip>& testStrips,
                                int day) {
  std::list<int> positive;
  for (auto& testStrip : testStrips) {
    int id = testStrip.getId();
    if (testStrip.isPositiveOnDay(day))
      positive.push_back(id);
  }
  return positive;
}

int setBits(const std::list<int>& positive) {
  int id = 0;
  for (int bitindex : positive)
    id |= 1 << bitindex;
  return id;
}

int main() {
  std::random_device rd;
  std::mt19937 rng(rd());
  const int poisened_bottle = rng() % 1000;
  std::list<Bottle> bottles;
  std::generate_n(std::back_inserter(bottles), 1000,
                  [n = 0, poisened_bottle]() mutable {
                    Bottle b(n);
                    if (n++ == poisened_bottle)
                      b.setPoisoned();
                    return b;
                  });
  std::deque<TestStrip> strips;
  std::generate_n(std::back_inserter(strips), 10,
                  [n = 0]() mutable { return TestStrip(n++); });
  const auto& r = findPoisonedBottle(bottles, strips);
  if (r == -1) {
    std::cout << "Poisoned bottle " << poisened_bottle
              << " not found in 7 days" << std::endl;
  } else if (r != poisened_bottle) {
    std::cout << "Wrong poisoned bottle " << r << " instead of the real "
              << poisened_bottle << " found in 7 days" << std::endl;
  } else {
    std::cout << "Poisoned bottle " << r << " found in 7 days" << std::endl;
    return 0;
  }
  return 1;
}
