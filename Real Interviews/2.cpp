// Implement the following function.
// The goal of this function is to return true if the first string is a subsequence of the second.

// Examples:
// isSubsequence("aba", "baaaxxxxxba") -> true
// isSubsequence("aba", "baaaxxxxxb") -> false
#include <string>
#include <iostream>

// Recursive, slow
bool isSubsequence(std::string first, std::string second) {
    if (first.length() > second.length())
        return false;
    if (first.empty())
        return true;
    auto it = second.find(first[0]);
    return it != second.length() && isSubsequence(first.substr(1), second.substr(it + 1));
}

// Iterative, quick
bool isSubsequenceQ(std::string first, std::string second)
{
    if (first.length() > second.length())
        return false;
    auto i = first.begin();
    for (auto j = second.begin(); i != first.end() && j != second.end(); ++j)
        if (*i == *j)
            ++i;
    return i == first.end();
}

int main()
{
    std::cout << (isSubsequence("aba", "baaaxxxxxba") ? "true" : "false") << std::endl;
    std::cout << (isSubsequenceQ("aba", "baaaxxxxxba") ? "true" : "false") << std::endl;
    std::cout << (isSubsequence("aba", "baaaxxxxxb") ? "true" : "false") << std::endl;
    std::cout << (isSubsequenceQ("aba", "baaaxxxxxb") ? "true" : "false") << std::endl;
}
