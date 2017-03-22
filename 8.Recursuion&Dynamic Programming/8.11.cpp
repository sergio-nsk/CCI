// Coins: Given an infinite number of quarters (25 cents), dimes (1O cents), nickels (5 cents), and
// pennies (1 cent), write code to calculate the number of ways of representing n cents.

#include <vector>

int makeChange(int amount, std::vector<int> &denoms, unsigned index)
{
    if (index >= denoms.size() - 1)
        return 1; // last denom
    int denomAmount = denoms[index];
    int ways = 0;
    for (int i = 0; i * denomAmount <= amount; ++i)
    {
        //go to next denom, assuming i coins of denomAmount
        int amountRemaining = amount - i * denomAmount;
        ways += makeChange(amountRemaining, denoms, index + 1);
    }
    return ways;
}

int makeChange(int n)
{
    std::vector<int> denoms = {25, 10, 5, 1};
    return makeChange(n, denoms, 0);
}
