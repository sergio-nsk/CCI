// The Egg Drop Problem: There is a building of 100 floors. If an egg drops from
// the Nth floor or above, it will break. If it's dropped from any floor below,
// it will not break.You're given two eggs. Find N, while minimizing the number
// of drops for the worst case.

#include <iostream>
#include <random>

class EggDropProblem {
 public:
  EggDropProblem(int floors) {
    std::random_device
        rd;  // Will be used to obtain a seed for the random number engine
    std::mt19937 gen(
        rd());  // Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> dis(1, floors);
    breakingPoint = dis(gen);
    std::cout << findBreakingPoint(floors);
    std::cout << ", solved in " << countDrops << " drops" << std::endl;
  }

 private:
  int breakingPoint;
  int countDrops = 0;

  bool drop(int floor) {
    ++countDrops;
    std::random_device
        rd;  // Will be used to obtain a seed for the random number engine
    std::mt19937 gen(
        rd());  // Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> dis(0, 1);

    return floor >= breakingPoint;
  }

  int findBreakingPoint(int floors) {
    int interval = static_cast<int>(
        std::ceil((-1.0 + std::sqrt(1.0 + 8.0 * floors)) / 2.0));
    int previousFloor = 0;
    int egg1 = interval;

    // Drop egg1 at decreasing intervals.
    while (!drop(egg1) && egg1 <= floors) {
      --interval;
      previousFloor = egg1;
      egg1 += interval;
    }

    // Drop egg2 at 1 unit increments.
    int egg2 = previousFloor + 1;
    while (egg2 < egg1 && egg2 <= floors && !drop(egg2))
      egg2 += 1;
    // If it didn't break, return -1.
    return egg2 > floors ? -1 : egg2;
  }
};

int main() {
  EggDropProblem(100);
}
