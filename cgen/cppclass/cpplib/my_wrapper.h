#pragma once

#ifdef __cplusplus
extern "C" {
#endif

typedef struct MyClass MyClass;

// constructor
MyClass* NewMyClass();

// method setter
void MyClassIntSet(MyClass* v, int i);

// method getter
int MyClassIntGet(MyClass* v);

// destructor
void DeleteMyClass(MyClass* v);

#ifdef __cplusplus
}
#endif