#include <unordered_set>
#include <vector>
#include "6.10.hpp"

// Get results that are positive for a particular day, excluding prior results.
int getPositiveOnDay(const std::deque<TestStrip> &testStrips, int day, std::unordered_set<int> &previousResults);

int findPoisonedBottle(std::list<Bottle> *bottles, std::deque<TestStrip> &strips)
{
	if (bottles->size() > 1000 || strips.size() < 10)
        return -1;
	int tests = 4; // three digits, plus one extra
	int nTestStrips = strips.size();

    // Run tests.
	for (int day = 0; day < tests; ++day)
		runTestSet(*bottles, strips, day);

	// Get results.
    std::unordered_set<int> previousResults;
	std::vector<int> digits(tests);
	for (int day = 0; day < tests; ++day)
    {
		int resultDay = day + TestStrip::DAYS_FOR_RESULT;
		digits[day] = getPositiveOnDay(strips, resultDay, previousResults);
		previousResults.insert(digits[day]);
	}

	// If day l's results matched day 0's, update the digit.
	if (digits[1] == -1)
		digits[1] = digits[0];

	// If day 2 matched day 0 or day 1, check day 3. Day 3 is the same as day 2,
    // but incremented by 1.
	if (digits[2] == -1)
    {
		if (digits[3] == -1)
        {
            // Day 3 didn't give new result
			// Digit 2 equals digit 0 or digit 1. But, digit 2, when incremented also
			// matches digit 0 or digit 1. This means that digit 0 incremented matches
			// digit 1, or the other way around.
			digits[2] = ((digits[0] + 1) % nTestStrips) == digits[1] ? digits[0] : digits[1];
		}
        else
			digits[2] = (digits[3] - 1 + nTestStrips) % nTestStrips;
	}
	return digits[0] * 100 + digits[1]* 10 + digits[2];
}

// Get strip that should be used on this bottle on this day.
int getTestStripindexForDay(const Bottle &bottle, int day, int nTestStrips);

// Run set of tests for this day.
void runTestSet(const std::list<Bottle> &bottles, std::deque<TestStrip> &strips, int day)
{
	if (day > 3)
        return; // only works for 3 days (digits)+one extra
	for (auto &bottle : bottles)
    {
		int index = getTestStripindexForDay(bottle, day, strips.size());
		TestStrip testStrip = strips.at(index);
		testStrip.addDropOnDay(day, bottle);
	}
}

int getTestStripindexForDay(const Bottle &bottle, int day, int nTestStrips)
{
	int id = bottle.getId();
	switch (day)
    {
	case 0:
        return id / 100;
	case 1:
        return (id % 100) / 10;
	case 2:
        return id % 10;
	case 3:
        return (id % 10 + 1) % nTestStrips;
	default:
        return -1;
	}
}

int getPositiveOnDay(const std::deque<TestStrip> &testStrips, int day, std::unordered_set<int> &previousResults)
{
	for (auto &testStrip : testStrips)
    {
		int id = testStrip.getId();
		if (testStrip.isPositiveOnDay(day) && previousResults.find(id) == previousResults.end())
			return testStrip.getId();
	}
	return -1;
}
