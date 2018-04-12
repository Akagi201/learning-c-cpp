#include <string>
#include <iostream>

#include <boost/bimap.hpp>

int main() {
  //std::string <-> int
  typedef boost::bimap<std::string, int> bimap;
  bimap animals;

  animals.insert({"cat", 4});
  animals.insert({"shark", 0});
  animals.insert({"spider", 8});

  auto res = animals.insert({"dog", 4});
  std::cout << "insert res second:" << res.second << std::endl;//0
  std::cout << "insert res first.left:" << res.first->left << std::endl;//cat
  std::cout << "insert res first.right:" << res.first->right << std::endl;//4

  std::cout << animals.left.count("cat") << std::endl; //1
  std::cout << animals.right.count(8) << std::endl; //1

  for (const auto& animal: animals) {
    std::cout << animal.left << " " << animal.right << std::endl;
  }

  return 0;
}