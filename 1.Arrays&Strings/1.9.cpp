// String Rotation: Assumeyou have a method isSubstringwhich checks if one word
// is a substring of another. Given two strings, sl and s2, write code to check
// if s2 is a rotation of sl using only one call to isSubstring (e.g.,
// "waterbottle" is a rotation of "erbottlewat").

#include "all.hpp"

bool checkRotation(std::string&& one, std::string&& two) {
  if (one.length() != two.length())
    return false;

  one += one;
  return one.find(two) != one.npos;
}

void printResult(bool result, std::string&& one, std::string&& two) {
  if (result)
    std::cout << '"' << two << '"' << " is rotated " << '"' << one << '"'
              << std::endl;
  else
    std::cout << '"' << two << '"' << " is not rotated " << '"' << one << '"'
              << std::endl;
}

int main() {
  test(checkRotation, printResult, "TestRotation", "RotationTest");
  test(checkRotation, printResult, "TestRotation", "rotationTest");
  test(checkRotation, printResult, "TestRotation", "Rotationtest");
  test(checkRotation, printResult, "waterbottle", "erbottlewat");
  return 0;
}
