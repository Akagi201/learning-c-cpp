// 辅助哈希函数
#include <iostream>

typedef unsigned long PointerType;

// Returns a hash code based on an address
unsigned short Hash(void *p) {
	PointerType val = reinterpret_cast<PointerType>(p);
	return (unsigned short)(val ^ (val >> 16));
}

using namespace std;

int main() {
	int a[20];
	for (int i = 0; i < 20; i++) {
		cout << Hash(a + i) << endl;
	}
}
