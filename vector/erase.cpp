#include <iostream>
#include <vector>

using namespace std;

int main() {
  vector<int> arr = {0, 1, 2, 3, 4};
  for (vector<int>::iterator it=arr.begin(); it != arr.end();) {
    if (*it == 0) {
      it = arr.erase(it);
    } else {
      ++it;
    }
  }
  cout << arr[0] << endl;
  return 0;
}