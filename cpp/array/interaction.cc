#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

int interaction_count(vector<int>& a1, vector<int>& a2) {
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
  vector<int> a1;
  vector<int> a2;

  a1.push_back(1);
  a1.push_back(2);
  a1.push_back(3);

  a2.push_back(2);
  a2.push_back(3);
  a2.push_back(4);

  cout << interaction_count(a1, a2) << endl;

  return 0;
}