// URLify: Write a method to replace all spaces in a string with '%20'. You may assume that the string
// has sufficient space at the end to hold the additional characters, and that you are given the "true"
// length of the string. (Note: If implementing in Java, please use a character array so that you can
// perform this operation in place.)
// EXAMPLE
// Input:
//  "Mr John Smith", 13
// Output:
//  "Mr%20John%20Smith"

#include "all.hpp"

// I may assume but I don't assume that the string has sufficient space ath the end
bool encodeSpaces(std::string &url)
{
    int cnt = std::count(url.begin(), url.end(), ' ');
    if (cnt == 0)
        return true;

    url.insert(url.end(), cnt * 2, 0);
    auto to = url.end() - 1;
    auto from = to - cnt * 2;
    for ( ; to != from; --from)
    {
        if (*from == ' ')
        {
            *to-- = '0';
            *to-- = '2';
            *to-- = '%';
        }
        else
            *to-- = *from;
    }
    return true;
}

void printResult(bool, const std::string &result)
{
    std::cout << '"' << result << '"' << std::endl;
}

int main()
{
    std::string testUrl = std::string("Mr John Smith");
    test(encodeSpaces, printResult, testUrl);
    testUrl = std::string("a b c d e f g h i j k l m n o p q r s t u v x w z");
    test(encodeSpaces, printResult, testUrl);
    testUrl = std::string("a     ");
    test(encodeSpaces, printResult, testUrl);
    testUrl = std::string("     ");
    test(encodeSpaces, printResult, testUrl);
    testUrl = std::string("     b");
    test(encodeSpaces, printResult, testUrl);
    testUrl = std::string("a     b");
    test(encodeSpaces, printResult, testUrl);
    return 0;
}
