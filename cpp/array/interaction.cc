#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

int interaction_count(const vector<int>& a1, const vector<int>& a2) {
  unordered_set<int> s1(a1.begin(), a1.end());
  int count = 0;
  for (const int& i:a2) {
    if (s1.find(i) != s1.end()) {
      count++;
    }
  }
  return count;
}

int main() {
  vector<int> a1({1,2,3});
  vector<int> a2({2,3,4});

  cout << interaction_count(a1, a2) << endl;

  return 0;
}
