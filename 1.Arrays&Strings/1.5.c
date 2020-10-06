/*
 One Away: There are three types of edits that can be performed on strings:
 insert a character, remove a character, or replace a character. Given two
 strings, write a function to check if they are one edit (or zero edits) away.
 EXAMPLE
  pale, ple -> true
  pales, pale -> true
  pale, bale -> true
  pale, bake -> false
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isOneAway(const char* left, const char* right) {
  int modifiedCount = 0;
  const int leftLen = (int)strlen(left);
  const int rightLen = (int)strlen(right);
  if (abs(leftLen - rightLen) > 2)
    return 0;

  while (*left && *right) {
    if (*left != *right) {
      if (modifiedCount > 0)
        return 0;

      ++modifiedCount;
      if (leftLen > rightLen) {
        ++left;
        continue;
      } else if (leftLen < rightLen) {
        ++right;
        continue;
      }
    }
    ++left;
    ++right;
  }

  return modifiedCount < 2;
}

void print(const char* left, const char* right) {
  printf("\"%s\", \"%s\" --> %s \n", left, right,
         isOneAway(left, right) ? "true" : "false");
}

int main(int argc, char** argv) {
  print("pale", "ple");
  print("pales", "pale");
  print("pale", "bale");
  print("pale", "bake");
  print("palepale", "bale");
  fflush(stdout);
  return 0;
}
