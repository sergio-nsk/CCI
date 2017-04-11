// Check if a given string contains a substring that is a permutation of a second given string.
// "dabcd" - second string
// "cdfddbacg" -> true, "ddbac" is a permutation of "dabcd"
// "cddfdbacg" -> false.

#include <string>
#include <algorithm>
#include <bitset>
#include <vector>
#include <array>
#include <iostream>

//
// 1. Simple, not optimized
//
bool findPermutation(const std::string &str, const std::string &substr)
{
    for (auto i = str.begin(); i != str.end() - substr.length(); ++i)
    {
        if (std::is_permutation(i, i + substr.length(), substr.begin()))
            return true;
    }
    return false;
}

//
// 2. Optimized: if there is a char in the interval of length substr.length(), that is not in 'substr',
// skip and continue with the interval after that char.
//

// Check that all chars in substring with length 'substrlen' are in permutation.
// 'e' stores next position after last checked char.
bool checkUsed(const std::bitset<256> &usedchars, const std::string::const_iterator &b, std::string::const_iterator &e, int substrlen)
{
    while (e - b < substrlen)
    {
        if (!usedchars[*e++])
            return false;
    }
    return true;
}


//
// 3. More optimized: precompute array of counts of chars of 'substr'. Check if the current interval is a permutation.
// If char in the interval is not in the array, skip and continue with the interval after that char.
//

bool findPermutation2(const std::string &str, const std::string &substr)
{
    std::bitset<256> usedchars;
    for (auto c : substr)
        usedchars[c] = 1;

    std::string::const_iterator checked = str.begin();
    std::string::const_iterator current = str.begin();
    while (current != str.end() - substr.length())
    {
        if (!checkUsed(usedchars, current, checked, substr.length()))
            current = checked;
        else if (std::is_permutation(current, checked, substr.begin()))
            return true;
        else
            ++current;
    }

    return false;
}

bool checkPermutation(std::vector<int> charcount, const std::array<char, 256> &charmap, const std::string::const_iterator &b, std::string::const_iterator &e, int substrlen)
{
    while (e - b < substrlen)
    {
        auto i = charmap[*e++];
        if (i == -1 || --charcount[i] < 0)
            return false;
    }
    return std::find_if_not(charcount.begin(), charcount.end(), [](int cnt){return cnt == 0;}) == charcount.end();
}

bool findPermutation3(const std::string &str, const std::string &substr)
{
    std::vector<int> charcount;
    std::array<char, 256> charmap; // used to make vector as less as possible

    std::fill(&charmap[0], &charmap[0] + charmap.size(), -1);

    for (auto c : substr)
    {
        if (charmap[c] == -1)
        {
            charmap[c] = charcount.size();
            charcount.push_back(1);
        }
        else
            ++charcount[charmap[c]];
    }

    std::string::const_iterator checked = str.begin();
    std::string::const_iterator current = str.begin();

    while (current != str.end() - substr.length())
    {
        if (checkPermutation(charcount, charmap, current, checked, substr.length()))
            return true;
        else
            current = checked;
    }


    return false;
}

int main()
{
    std::cout << (findPermutation("cdfddbacg", "dabcd") ? "true" : "false") << std::endl;
    std::cout << (findPermutation("cddfdbacg", "dabcd") ? "true" : "false") << std::endl;
    std::cout << (findPermutation2("cdfddbacg", "dabcd") ? "true" : "false") << std::endl;
    std::cout << (findPermutation2("cddfdbacg", "dabcd") ? "true" : "false") << std::endl;
    std::cout << (findPermutation3("cdfddbacg", "dabcd") ? "true" : "false") << std::endl;
    std::cout << (findPermutation3("cddfdbacg", "dabcd") ? "true" : "false") << std::endl;
}
