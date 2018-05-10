#include <iostream>

using namespace std;

int main() {
  int array[10] = {0,1,2,3,4,5,6,7,8,9};
  auto it = std::find(std::begin(array), std::end(array), 5);
  
  if (it != std::end(array)) {
    cout << "found at position " << distance(array, it) << endl;
  } else {
    cout << "not found" << endl;
  }

  return 0;
}
