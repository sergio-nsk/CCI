// https://www.careercup.com/question?id=5657872336683008
// Google
// Generate a random 4-digit even number : the adjacent 2 digits must be different.
// public int getNumber()
// {
// }

#include <vector>
#include <algorithm>
#include <random>
#include <iostream>

std::random_device rd;  // will be used to obtain a seed for the random number engine
std::mt19937 gen(rd()); // standard mersenne_twister_engine seeded with rd()
std::uniform_int_distribution<> dis(0, 359);

// Returns random number from 1 till 9
int getRundom19() {
  return 1 + dis(gen) / (5 * 8);
}

// Returns random number from 1 till 8
int getRundom18()
{
  return 1 + dis(gen) / (5 * 9) ;
}

// Returns random even number from 0 till 8
int getRundomEven08()
{
  return 2 * (dis(gen) / (9 * 8));
}

int getNumber() {
  std::vector<int> digits(10);
  std::iota(digits.begin(), digits.end(), 0);

  int dig = getRundomEven08();
  int num = dig;  // lowest even digit from 0 till 8

  for (int mul = 10; mul <= 100; mul *= 10) {
    std::swap(digits[0], digits[dig]);  // digits[0] contains adjacent digit
    int d = digits[getRundom19()];      // random digit of digits[1] till digits[9]
    num += d * mul;
    std::swap(digits[0], digits[dig]);  // digits again is {0 .. 9}
    dig = d;
  }
  std::swap(digits[9], digits[dig]); // digits[9] contains adjacent digit, digits[0] contains useless 0
  dig = digits[getRundom18()];
  num += dig * 1000;
  return num;
}

int main() {
  for (int i = 0; i < 100; ++i)
    std::cout << getNumber() << "\n";
}
