/*
 Is Unique: Implement an algorithm to determine if a string has all unique characters. What if you
 cannot use additional data structures?
 */

#include <stdint.h>
#include <stdio.h>

int isUnique(const char *chars)
{
    // 8bit ASCII
    uint64_t testChars[4] = { 0 };
    for ( ; *chars; ++chars)
    {
        int i = (*chars) >> 6;
        uint64_t bit = 1ULL << ((*chars) & 0b00111111);
        if (testChars[i] & bit)
            return 0;
        testChars[i] |= bit;
    }
    return 1;
}

void test(int (*func)(const char *), const char *chars)
{
    printf("\"%s\" %s\n", chars, func(chars) ? " passed" : " failed");
}

int main(int argc, char **argv)
{
    test(isUnique, "IsUnique");
    test(isUnique, "IsUniqueTest");
    return 0;
}