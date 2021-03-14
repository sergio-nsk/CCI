#include "6.10.hpp"

#include <algorithm>
#include <iostream>
#include <iterator>
#include <list>
#include <random>
#include <utility>

std::pair<int, int> findPoisonedBottle(std::list<Bottle> bottles,
                                       std::deque<TestStrip>& strips) {
  int today = 0;
  while (bottles.size() > 1 && strips.size() > 0) {
    // Run tests.
    runTestSet(bottles, strips, today);
    // Wait for results.
    today += TestStrip::DAYS_FOR_RESULT;
    // Check results.
    for (auto strip = strips.begin(); strip != strips.end(); ++strip) {
      if (strip->isPositiveOnDay(today)) {
        bottles = *strip->getLastWeeksBottles(today);
        strips.erase(strip);
        break;
      }
    }
    if (bottles.size() == 1)
      return std::make_pair(bottles.front().getId(), today);
  }
  return std::make_pair(-1, today);
}

// Distribute bottles across test strips evenly.
void runTestSet(const std::list<Bottle>& bottles,
                std::deque<TestStrip>& strips,
                int day) {
  auto index = strips.begin();
  for (const auto& bottle : bottles) {
    TestStrip& strip = *index;
    strip.addDropOnDay(day, bottle);
    if (++index == strips.end())
      index = strips.begin();
  }
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
  if (r.first == -1) {
    std::cout << "Poisoned bottle " << poisened_bottle << " not found in "
              << r.second << " days" << std::endl;
  } else if (r.first != poisened_bottle) {
    std::cout << "Wrong poisoned bottle " << r.first << " instead of the real "
              << poisened_bottle << " found in " << r.second << " days"
              << std::endl;
  } else {
    std::cout << "Poisoned bottle " << r.first << " found in " << r.second
              << " days" << std::endl;
    return 0;
  }
  return 1;
}
