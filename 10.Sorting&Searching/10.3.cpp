// Search in Rotated Array: Given a sorted array of n integers that has been rotated an unknown
// number of times, write code to find an element in the array. You may assume that the array was
// originally sorted in increasing order.
// EXAMPLE
// Input: find 5 in {15, 16, 19, 20, 25, 1, 3, 4, 5, 7, 10, 14}
// Output: 8 (the index of 5 in the array)

#include "all.hpp"

int search(const std::vector<int> &rotatedArray, int value, int left, int right)
{
    if (right < left)
        return -1;

    int middle = (left + right) / 2;
    if (rotatedArray[middle] == value)
        return middle;

    if (rotatedArray[left] < rotatedArray[middle])
    {
        // Left side is normally sorted
        if (rotatedArray[left] <= value && value < rotatedArray[middle])
            return search(rotatedArray, value, left, middle - 1);
        else
            return search(rotatedArray, value, middle + 1, right);
    }
    else if (rotatedArray[middle] < rotatedArray[right])
    {
        // Right side is normally sorted
        if (rotatedArray[middle] < value && value <= rotatedArray[right])
            return search(rotatedArray, value, middle + 1, right);
        else
            return search(rotatedArray, value, left, middle - 1);
    }
    else if (rotatedArray[left] == rotatedArray[middle])
    {
        // Left or right half side elements are repeated
        if (rotatedArray[middle] != rotatedArray[right])
            return search(rotatedArray, value, middle + 1, right);
        else
        {
            // Search in both halves
            int idx = search(rotatedArray, value, left, middle - 1);
            if (idx == -1)
                idx = search(rotatedArray, value, middle + 1, right);
            return idx;
        }
    }
    return -1;
}

int search(const std::vector<int> &rotatedArray, int value)
{
    return search(rotatedArray, value, 0, rotatedArray.size() - 1);
}

int main()
{
    std::vector<int> rotatedArray = {15, 16, 19, 20, 25, 1, 3, 4, 5, 7, 10, 14};
    std::cout << search(rotatedArray, 5) << std::endl;
    std::cout << search(rotatedArray, 6) << std::endl;
    std::cout << search(rotatedArray, 0) << std::endl;
    std::cout << search(rotatedArray, 30) << std::endl;

    rotatedArray = {9, 9, 9, 9, 9, 9, 1, 1, 5, 5, 7, 7, 8};
    std::cout << search(rotatedArray, 5) << std::endl;
    std::cout << search(rotatedArray, 8) << std::endl;
    std::cout << search(rotatedArray, 9) << std::endl;
    std::cout << search(rotatedArray, 30) << std::endl;
}
