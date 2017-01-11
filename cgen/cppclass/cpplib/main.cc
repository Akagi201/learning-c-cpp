#include <iostream>
#include "my_class.h"

using namespace std;

int main(int argc, char* argv[]) {
	{
		MyClass c = MyClass();
		c.int_set(3);
		cout << c.int_get() << endl;
	}
	{
		MyClass* c = new MyClass();
		c->int_set(3);
		cout << c->int_get() << endl;
		delete c;
	}
}
