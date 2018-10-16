// String 1: int b1 is base of input number and b2 is base of output number.
// String 2: 1-12 digits + optional point of the input string in the base b1.
// Output:
// If b1 < 2 or b1 > 16 or b2 < 2 or b2 > 16: "bad input".
// If input number is not in the base b1: "bad input".
// Dump the number in the base b2, max 12 digits after the point if any.

#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void error() {
  printf("bad input\n");
  exit(1);
}

void output(long long integral, double frac, int b2) {
  static const char matrix[] = "0123456789abcdef";
  char output[256] = {0};
  char* ch = output + sizeof(output) - 1;

  do {
    *(--ch) = matrix[integral % b2];
    integral /= b2;
  } while (integral > 0);
  printf("%s", ch);

  if (frac >= DBL_MIN) {
    printf(".");
    for (int i = 0; i < 12 && frac >= DBL_MIN; ++i) {
      frac *= b2;
      int digit = (int)frac;
      printf("%c", matrix[digit]);
      frac -= digit;
    }
  }
}

int main(int argc, char** argv) {
  int b1, b2;
  char input[14] = {0};
  char* end = input;
  long long integral = 0;
  double frac = 0.0;

  if (scanf("%d %d", &b1, &b2) != 2)
    error();
  if (b1 < 2 || b1 > 16 || b2 < 2 || b2 > 16)
    error();
  if (scanf("%13s", input) != 1)
    error();

  integral = strtoll(input, &end, b1);
  if (input == end || (*end && *end != '.'))
    error();
  if (*end == '.') {
    const char* str = end + 1;
    frac = strtoll(str, &end, b1);
    if (str == end || *end)
      error();
    frac /= pow(b1, end - str);
  }
  output(integral, frac, b2);
  printf("\n");
  return 0;
}
