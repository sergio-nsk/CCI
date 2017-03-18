#include <vector>
#include "6.10.hpp"

// Add bottle contents to test strips
void runTests(std::list<Bottle> &bottles, std::deque<TestStrip> &testStrips);

// Create number by setting bits with indices specified in positive.
int setBits(const std::list<int> &positive);

// Get test strips that are positive on a particular day.
std::list<int> getPositiveOnDay(const std::deque<TestStrip> &testStrips, int day);

int findPoisonedBottle(std::list<Bottle> &bottles, std::deque<TestStrip> &strips)
{
	runTests(bottles, strips);
	auto positive = getPositiveOnDay(strips, 7);
	return setBits(positive);
}

void runTests(std::list<Bottle> &bottles, std::deque<TestStrip> &testStrips) {
	for (auto &bottle : bottles)
    {
		int id = bottle.getId();
		int bitindex = 0;
		while (id > 0)
        {
			if ((id & 1) == 1)
				testStrips.at(bitindex).addDropOnDay(0, bottle);
			++bitindex;
			id >>= 1;
		}
	}
}

std::list<int> getPositiveOnDay(const std::deque<TestStrip> &testStrips, int day)
{
	std::list<int> positive;
	for (auto &testStrip : testStrips)
    {
		int id = testStrip.getId();
		if (testStrip.isPositiveOnDay(day))
			positive.push_back(id);
	}
	return positive;
}

int setBits(const std::list<int> &positive)
{
	int id = 0;
	for (int bitindex : positive)
		id |= 1 << bitindex;
	return id;
}

