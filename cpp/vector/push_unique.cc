#include <vector>
#include <iostream>

using namespace std;

int main() {
  vector<string> name;
  name.push_back("world");
  name.push_back("hello");
  if (find(name.begin(), name.end(), "hello") == name.end()) {
    name.push_back("hello");
  }
  cout << name[0] << " " << name.size() << endl;
  return 0;
}