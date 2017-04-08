// Check Permutation: Given two strings, write a method to decide if one is a permutation of the
// other.

#include "all.hpp"

bool checkPermutation(std::string &&one, std::string &&two)
{
    if (one.length() != two.length())
        return false;

    // I would use std::unordered_map instead of the array in case of std::wstring
    int charCount[256] = { 0 };

    for (int c : one)
        ++charCount[c];

    for (int c : two)
        if (--charCount[c] < 0)
            return false;

    return true;
}

bool checkPermutationStd(std::string &&one, std::string &&two)
{
    return std::is_permutation(one.begin(), one.end(), two.begin(), two.end());
}

void printResult(bool result, std::string &&one, std::string &&two)
{
    if (result)
        std::cout << '"' << two << '"' << " is permutation of " << '"' << one << '"'  << std::endl;
    else
        std::cout << '"' << two << '"' << " is not permutation of " << '"' << one << '"'  << std::endl;
}

int main()
{
    test(checkPermutation, printResult, "TestPermutation", "PermutationTest");
    test(checkPermutationStd, printResult, "TestPermutation", "PermutationTest");
    test(checkPermutation, printResult, "TestPermutation", "PeermutatTstion");
    test(checkPermutationStd, printResult, "TestPermutation", "PeermutatTstion");
    test(checkPermutation, printResult, "TestPermutation", "RotationTest");
    test(checkPermutationStd, printResult, "TestPermutation", "RotationTest");
    test(checkPermutation, printResult, "TestPermutation", "Permutationtest");
    test(checkPermutationStd, printResult, "TestPermutation", "Permutationtest");
    return 0;
}
