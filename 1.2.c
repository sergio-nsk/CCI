/*
 Check Permutation: Given two strings, write a method to decide if one is a permutation of the
 other.
 */

#include <string.h>
#include <stdio.h>

int checkPermutation(const char *one, const char *two)
{
    const int len = strlen(one);
    if (len != strlen(two))
        return 0;

    char oneone[2 * len + 1];

    strcpy(oneone, one);
    strcpy(oneone + len, one);
    return strstr(oneone, two) != NULL;
}

void test(int (*func)(const char *, const char *), const char *one, const char *two)
{
    printf("\"%s\" %s permutation of \"%s\"\n", two, func(one, two) ? "is" : "is not", one);
}


int main(int argc, char **argv)
{
    test(checkPermutation, "TestPermutation", "PermutationTest");
    test(checkPermutation, "TestPermutation", "RotationTest");
    test(checkPermutation, "TestPermutation", "Permutationtest");
     return 0;
}
