/*
 Palindrome Permutation: Given a string, write a function to check if it is a permutation of
 a palindrome. A palindrome is a word or phrase that is the same forwards and backwards. A
 permutation is a rearrangement of letters. The palindrome does not need to be limited to just
 dictionary words.
 EXAMPLE
 Input:
  Tact Coa
 Output:
  True (permutations: "taco cat'; "atc o eta·; etc.)
*/

#include <string.h>
#include <stdio.h>
#include <ctype.h>

int isPalindromePermutation(const char *str)
{
    int charCount[26] = { 0 };

    for ( ; *str; ++str)
    {
        if (isalpha(*str))
            ++charCount[tolower(*str) - 'a'];
    }

    int oddCnt = 0;
    for (int *cnt = charCount; oddCnt < 2 && cnt < charCount + sizeof(charCount) / sizeof(*charCount); ++cnt)
        if ((*cnt) & 1)
            ++oddCnt;

    return oddCnt < 2;
}

void test(const char *str)
{
    printf("\"%s\" %s %s\n", str, isPalindromePermutation(str) ? "is" : "is not", "palindrome permutation");
}

int main(int argc, char **argv)
{
    test("Tact Coa");
    test("Tact Coat");
    test("Tacto Coa");
    test("Ota.c,t:o Co a");
}