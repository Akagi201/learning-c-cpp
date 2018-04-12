#include <stdio.h>

int main(int argc, char *argv[]) {
  char *aa = argv[1];
  printf("%s\n", aa);
  int a = 4;
  int b = 6;
  int array[3];
  array[0] = 1;
  array[1] = 10;
  array[2] = 100;
  int *p;
  p = &a;
  int i = 0;
  while (i < 6) {
    printf("*p = %d\n", *p);
    p++;
    i++;
  }
  return 0;
}
