/*
 String Rotation: Assumeyou have a method isSubstringwhich checks if one word is a substring
 of another. Given two strings, sl and s2, write code to check if s2 is a rotation of sl using only one
 call to isSubstring (e.g., "waterbottle" is a rotation of "erbottlewat").
 */

#include <string.h>
#include <stdio.h>

int checkRotation(const char *one, const char *two)
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
    printf("\"%s\" %s rotated \"%s\"\n", two, func(one, two) ? "is" : "is not", one);
}


int main(int argc, char **argv)
{
    test(checkRotation, "TestRotation", "RotationTest");
    test(checkRotation, "TestRotation", "rotationTest");
    test(checkRotation, "TestRottation", "Rotationtest");
    test(checkRotation, "waterbottle", "erbottlewat");
    return 0;
}
