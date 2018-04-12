#include "my_wrapper.h"
#include <stdio.h>

int main(int argc, char* argv[]) {
    MyClass* c = NewMyClass();
    MyClassIntSet(c, 3);
    printf("%i\n", MyClassIntGet(c));
    DeleteMyClass(c);

    return 0;
}
