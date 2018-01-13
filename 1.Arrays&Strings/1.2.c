/*
 Check Permutation: Given two strings, write a method to decide if one is a
 permutation of the other.
 */

#include <stdio.h>
#include <string.h>

int checkPermutation(const char* one, const char* two) {
  int charCount[256] = {0};
  int len = 0;  // with len we will get only two iterations instead of four.

  for (; *one; ++one) {
    ++len;
    ++charCount[(int)*one];
  }
  for (; *two; ++two) {
    --len;
    // if (--charCount[(int)*two] < 0 || len < 0)
    // The condition len < 10 is not needed: if strlen(two) > strlen(one) then
    // the condition for charCount will false on the next step.
    if (--charCount[(int)*two] < 0)
      return 0;
  }
  return len == 0;
}

void test(int (*func)(const char*, const char*),
          const char* one,
          const char* two) {
  printf("\"%s\" %s permutation of \"%s\"\n", two,
         func(one, two) ? "is" : "is not", one);
  fflush(stdout);
}

int main(int argc, char** argv) {
  test(checkPermutation, "TestPermutation", "PermutationTest");
  test(checkPermutation, "TestPermutation", "PermuTestttaion");
  test(checkPermutation, "TestPermutation", "PermutationTests");
  test(checkPermutation, "TestPermutation", "RotationTest");
  test(checkPermutation, "TestPermutation", "Permutation");
  test(checkPermutation, "TestPermutation", "Permutationtest");
  return 0;
}
