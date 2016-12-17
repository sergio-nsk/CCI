// Palindrome Permutation: Given a string, write a function to check if it is a permutation of
// a palindrome. A palindrome is a word or phrase that is the same forwards and backwards. A
// permutation is a rearrangement of letters. The palindrome does not need to be limited to just
// dictionary words.
// EXAMPLE
// Input:
//  Tact Coa
// Output:
//  True (permutations: "taco cat'; "atc o eta·; etc.)

#include <string>
#include <array>
#include <algorithm>
#include <iostream>

#include "test.hpp"

bool isPalindromePermutation(const std::string &str)
{
    std::array<int, 26> charCount = { 0 };

    for (int c : str)
    {
        if (std::isalpha(c))
            ++charCount[std::tolower(c) - 'a'];
    }

    return std::count_if(charCount.begin(), charCount.end(), [](int cnt) { return cnt & 1; }) <= 1;
}

int main()
{
    auto print = [](bool result, const std::string &str)
    {
        std::cout << '"' << str << "\" " << (result ? "is" : "is not") << " Palindrome permutation" << std::endl;
    };

    test(isPalindromePermutation, print, "Tact Coa");
    test(isPalindromePermutation, print, "Tact Coat");
    test(isPalindromePermutation, print, "Tacto Coa");
    test(isPalindromePermutation, print, "Ota.c,t:o Co a");
    return 0;
}