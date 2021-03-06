/*
 String Rotation: Assumeyou have a method isSubstringwhich checks if one word is
 a substring of another. Given two strings, sl and s2, write code to check if s2
 is a rotation of sl using only one call to isSubstring (e.g., "waterbottle" is
 a rotation of "erbottlewat").
 */

#if defined(_MSC_VER)
#include <malloc.h>
#else
#include <alloca.h>
#endif
#include <stdio.h>
#include <string.h>

int checkRotation(const char* one, const char* two) {
  const size_t len = strlen(one);
  if (len != strlen(two))
    return 0;

  char* oneone = alloca(2 * len + 1);

  strcpy(oneone, one);
  strcpy(oneone + len, one);
  return strstr(oneone, two) != NULL;
}

void test(int (*func)(const char*, const char*),
          const char* one,
          const char* two) {
  printf("\"%s\" %s rotated \"%s\"\n", two, func(one, two) ? "is" : "is not",
         one);
}

int main(int argc, char** argv) {
  test(checkRotation, "TestRotation", "RotationTest");
  test(checkRotation, "TestRotation", "rotationTest");
  test(checkRotation, "TestRottation", "Rotationtest");
  test(checkRotation, "waterbottle", "erbottlewat");
  return 0;
}
