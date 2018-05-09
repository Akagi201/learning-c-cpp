#include <vector>
#include <iostream>

using namespace std;

int main() {
  vector<string> name;
  name.push_back("world");
  name.push_back("hello");
  // erase-remove idiom, C++ erase vector element by value rather than by position
  // https://en.wikipedia.org/wiki/Erase%E2%80%93remove_idiom
  name.erase(remove(name.begin(), name.end(), "world"), name.end());
  cout << name[0] << " " << name.size() << endl;
  
  return 0;
}