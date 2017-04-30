// Sparse Search: Given a sorted array of strings that is interspersed with empty strings, write a
// method to find the location of a given string.
// EXAMPLE
// Input: ball, {"at", "" , "" , "" , "ball", "" , "" , "car", "" , "" , "dad", "" , ""}
// Output : 4

#include "all.hpp"

int search(const std::vector<std::string> &strings, const std::string &str, int first, int last);

int search(const std::vector<std::string> strings, const std::string &str)
{
    if (strings.empty() || str.empty())
    {
        return -1;
    }
    return search(strings, str, 0, strings.size() - 1);
}

int search(const std::vector<std::string> &strings, const std::string &str, int first, int last)
{
    if (first > last)
        return -1;

    int mid = (last + first) / 2;

    // If mid is empty, find closest non-empty string.
    if (strings[mid].empty())
    {
        int left = mid - 1;
        int right = mid + 1;
        while (true)
        {
            if (left < first && right > last)
            {
                return -1;
            }
            else if (right <= last && !strings[right].empty())
            {
                mid = right;
                break;
            }
            else if (left >= first && !strings[left].empty())
            {
                mid = left;
                break;
            }
            ++right;
            --left;
        }
    }

    // Check for string, and recurse if necessary
    if (str == strings[mid])
    {
        //Found it!
        return mid;
    }
    else if (strings[mid].compare(str) < 0)
    {
        //Search right
        return search(strings, str, mid + 1, last);
    }
    else
    {
        //Search left
        return search(strings, str, first, mid - 1);
    }
}

int main()
{
    std::cout << search({"at", "", "", "", "ball", "", "", "car", "", "", "dad", "", ""}, "ball") << std::endl;
}
