#include <stdio.h>

static void quickSort(int array[], int left, int right);

void qSort(int array[], int size) {
  quickSort(array, 0, size - 1);
}

static void quickSort(int array[], int left, int right) {
  int i = left;
  int j = right;
  int pivot = array[(left + right) / 2];
  int tmp;

  while (i < j) {
    while (array[i] < pivot)
      ++i;
    while (array[j] > pivot)
      --j;
    if (i <= j) {
      tmp = array[i];
      array[i++] = array[j];
      array[j--] = tmp;
    }
  }
  if (left < j)
    quickSort(array, left, j);
  if (i < right)
    quickSort(array, i, right);
}

int main(int argc, char** argv) {
  int array[] = {3, 7, 2, 8, 1, 9, 0, 10, 5, 5, 4};
  int size = sizeof(array) / sizeof(array[0]);
  int i = 0;

  qSort(array, size);
  for (i = 0; i < size; ++i)
    printf("%d ", array[i]);
  printf("\n");
  return 0;
}
