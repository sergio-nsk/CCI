/*
 Palindrome Permutation: Given a string, write a function to check if it is a
 permutation of a palindrome. A palindrome is a word or phrase that is the same
 forwards and backwards. A permutation is a rearrangement of letters. The
 palindrome does not need to be limited to just dictionary words.

 EXAMPLE Input:
  Tact Coa
 Output:
  True (permutations: "taco cat'; "atc o eta·; etc.)
*/

#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

int isPalindromePermutation(const char* str) {
  int charCount[26] = {0};

  for (; *str; ++str) {
    if (isalpha(*str))
      ++charCount[tolower(*str) - 'a'];
  }

  int oddCnt = 0;
  for (int* cnt = charCount;
       oddCnt < 2 && cnt < charCount + sizeof(charCount) / sizeof(*charCount);
       ++cnt)
    if ((*cnt) & 1)
      ++oddCnt;

  return oddCnt < 2;
}

int isPalindromePermutationBetter(const char* str) {
  uint32_t oddChars = 0;

  for (; *str; ++str) {
    if (isalpha(*str)) {
      uint32_t bit = 1U << (tolower(*str) - 'a');
      if (oddChars & bit)
        oddChars &= ~bit;
      else
        oddChars |= bit;
    }
  }

  return oddChars == 0 || ((oddChars - 1) & oddChars) == 0;
  // 00100000 -> 00011111 & 00100000 -> 0
  // 00110000 -> 00101111 & 00110000 -> 00100000
}

void test(const char* str) {
  printf("\"%s\" %s %s\n", str, isPalindromePermutation(str) ? "is" : "is not",
         "palindrome permutation");
  printf("\"%s\" %s %s\n", str,
         isPalindromePermutationBetter(str) ? "is" : "is not",
         "palindrome permutation");
}

int main(int argc, char** argv) {
  test("Tact Coa");
  test("Tact Coat");
  test("Tacto Coa");
  test("Ota.c,t:o Co a");
}
