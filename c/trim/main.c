#include <stdio.h>
#include <string.h>
#include "trim.h"

int main() {
  {
    char str[] = "\t\n hello \t\n";
    printf("%s\n", trim(str));
  }
  return 0;
}
