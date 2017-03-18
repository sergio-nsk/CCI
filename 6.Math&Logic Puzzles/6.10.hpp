// Poison: You have 1000 bottles of soda, and exactly one is poisoned. You have 10 test strips which
// can be used to detect poison. A single drop of poison will turn the test strip positive permanently.
// You can put any number of drops on a test strip at once and you can reuse a test strip as many times
// as you'd like (as long as the results are negative). However, you can only run tests once per day and
// it takes seven days to return a result. How would you figure out the poisoned bottle in as few days
// as possible?
// Follow up: Write code to simulate your approach.

#include <list>
#include <deque>

class Bottle
{
public:
    Bottle(int id)
    {
        this->id= id;
    }
    int getId() const
    {
        return id;
    }
    void setAsPoisoned()
    {
        poisoned = true;
    }
    bool isPoisoned() const
    {
        return poisoned;
    }

private:
    bool poisoned = false;
    int id;
};

class TestStrip
{
public:
    static const int DAYS_FOR_RESULT = 7;

private:
    std::deque<std::list<Bottle>> dropsByDay;
    int id;

public:
    TestStrip(int id)
    {
        this->id = id;
    }
    int getId() const
    {
        return id;
    }

    // Resize list of days/drops to be large enough.
    void sizeDropsForDay(int day)
    {
        dropsByDay.resize(day);
    }
    // Add drop from bottle on specific day.
    void addDropOnDay(int day, Bottle bottle)
    {
        sizeDropsForDay(day);
        auto &drops = dropsByDay.at(day);
        drops.push_back(bottle);
    }

    // Checks if any of the bottles in the set are poisoned.
    bool hasPoison(const std::list<Bottle> &bottles) const
    {
        for (auto &b : bottles)
            if (b.isPoisoned())
                return true;
        return false;
    }

    // Gets bottles used in the test DAYS_FOR_RESULT days ago.
    std::list<Bottle> *getLastWeeksBottles(int day)
    {
        if (day < DAYS_FOR_RESULT)
            return nullptr;
        return &dropsByDay.at(day - DAYS_FOR_RESULT);
    }

    // Checks for poisoned bottles since before DAYS_FOR_RESULT
    bool isPositiveOnDay(int day) const
    {
        int testDay = day - DAYS_FOR_RESULT;
        if (testDay < 0 || static_cast<unsigned>(testDay) >= dropsByDay.size())
            return false;
        for (int d = 0; d <= testDay; d++)
        {
            auto &bottles = dropsByDay.at(d);
            if (hasPoison(bottles))
                return true;
        }
        return false;
    }
};

void runTestSet(const std::list<Bottle> &bottles, std::deque<TestStrip> &strips, int day);
