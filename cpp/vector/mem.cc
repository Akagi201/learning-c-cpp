#include <iostream>
#include <vector>

using namespace std;

// vector <string> v;
char ch;

int main() {
  vector <string> v;
  for (int i = 0; i < 1000000; i++) {
    v.push_back("abcdefghijklmn");
  }
  cin >> ch;
  // 检查内存 35M

  v.clear();
  cin >> ch;
  // 检查内存 35M

  cout << "Vector 的容量 " << v.capacity() << endl;

  vector<string>(v).swap(v);
  cout << "Vector 的容量 " << v.capacity() << endl;

  cin >> ch;
  return 0;
}
