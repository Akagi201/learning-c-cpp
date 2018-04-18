#include <iostream>

using namespace std;

int main() {
  const int const_a = 1;
  const int &a = const_a;
  auto b = a;
  b++;
  cout << b << endl;
  return 0;
}
