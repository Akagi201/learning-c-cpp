#include "my_class.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
    MyClass *c = new MyClass();
    c->int_set(3);
    cout << c->int_get() << endl;
    delete c;
}
