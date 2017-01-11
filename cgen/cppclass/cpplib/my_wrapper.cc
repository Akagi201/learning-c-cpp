#include "my_class.h"
#include "my_wrapper.h"

extern "C" {
    MyClass* NewMyClass() {
        return new MyClass();
    }

    void MyClassIntSet(MyClass* v, int i) {
        v->int_set(i);
    }

    int MyClassIntGet(MyClass* v) {
        return v->int_get();
    }

    void DeleteMyClass(MyClass* v) {
        delete v;
    }
}
