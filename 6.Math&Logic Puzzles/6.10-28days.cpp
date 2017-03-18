#include "6.10.hpp"

int findPoisonedBottle(const std::list<Bottle> *bottles, std::deque<TestStrip> strips)
{
    int today = 0;
    while (bottles->size() > 1 && strips.size() > 0)
    {
        // Run tests.
        runTestSet(*bottles, strips, today);
        // Wait for results.
        today+= TestStrip::DAYS_FOR_RESULT;
        // Check results.
        for (auto strip = strips.begin(); strip != strips.end(); ++strip)
        {
            if (strip->isPositiveOnDay(today))
            {
                bottles = strip->getLastWeeksBottles(today);
                strips.erase(strip);
                break;
            }
        }
        if (bottles->size() == 1)
            return bottles->front().getId();
    }
    return -1;
}

 // Distribute bottles across test strips evenly.
void runTestSet(const std::list<Bottle> &bottles, std::deque<TestStrip> &strips, int day)
{
    auto index = strips.begin();
    for (auto &bottle : bottles)
    {
        TestStrip &strip = *index;
        strip.addDropOnDay(day, bottle);
        if  (++index == strips.end())
            index = strips.begin();
    }
 }
