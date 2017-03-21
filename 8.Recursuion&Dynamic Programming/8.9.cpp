// Parens: Implement an algorithm to print all valid (i.e., properly opened and closed) combinations
// of n pairs of parentheses.
// EXAMPLE
// Input: 3
// Output: ((())) , ( ()()) , ( ())() , ()(() ) , ()()()

#include <deque>
#include <string>
#include <vector>
#include <iostream>

void addParen(std::deque<std::string> &list, int leftRem, int rightRem, char str[], int index)
{
    if (leftRem < 0 || rightRem < leftRem)
    return; // invalid state
    if (leftRem == 0 && rightRem == 0)
    {
        // Out of left and right parentheses
        list.emplace_back(str);
    }
    else
    {
        str[index] = '('; //Add left and recurse
        addParen(list, leftRem - 1, rightRem, str, index + 1);
        str[index] = ')'; //Add right and recurse
        addParen(list, leftRem, rightRem - 1, str, index + 1);
    }
 }

 std::deque<std::string> generateParens(int count)
 {
    std::vector<char> str(count * 2);
    std::deque<std::string> list;
    addParen(list, count, count, &str[0], 0);
    return list;
 }

 int main()
 {
     auto list = generateParens(4);
     for (auto &s : list)
        std::cout << s << '\n';
 }
