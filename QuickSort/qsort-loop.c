#include <limits.h>
#include <stdio.h>
#include <sys/types.h>

void swap(int* a, int* b) {
  if (a != b)
    *a ^= *b ^= *a ^= *b;
}

void qsort_loop(int* array, int size) {
  int stack[2 * sizeof(int) * CHAR_BIT] = {size - 1};
  int stack_pos = 2;

  do {
    int left = stack[--stack_pos];
    int right = stack[--stack_pos];
    do {
      int middle = (left + right) / 2;
      int pivot = array[middle];
      int i = left, j = right;
      while (i < j) {
        while (array[i] < pivot)
          ++i;
        while (array[j] > pivot)
          --j;
        if (i <= j)
          swap(array + i++, array + j--);
      }
      if (i <= middle) {
        if (i < right) {
          stack[stack_pos++] = right;
          stack[stack_pos++] = i;
        }
        right = j;
      } else {
        if (j > left) {
          stack[stack_pos++] = j;
          stack[stack_pos++] = left;
        }
        left = i;
      }
    } while (left < right);
  } while (stack_pos > 0);
}

int main(int argc, char** argv) {
  int array[] = {3, 7, 2, 8, 1, 9, 0, 10, 5, 5, 4};
  int size = sizeof(array) / sizeof(array[0]);
  int i = 0;

  qsort_loop(array, size);
  for (i = 0; i < size; ++i)
    printf("%d ", array[i]);
  printf("\n");
  return 0;
}
