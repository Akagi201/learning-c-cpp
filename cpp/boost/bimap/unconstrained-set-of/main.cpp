#include <string>
#include <iostream>

#include <boost/bimap.hpp>

int main() {
  typedef boost::bimap<boost::bimaps::set_of<std::string>, boost::bimaps::unconstrained_set_of<int>> bimap;
  bimap animals;

  animals.insert({"cat", 4});
  animals.insert({"shark", 0});
  animals.insert({"dog", 4});

  for (const auto& animal: animals) {
    std::cout << animal.left << " " << animal.right << std::endl;
  }

  auto it = animals.left.find("cat");
  //animals.left.modify_key(it, boost::bimaps::_key = "elephant");
  for (const auto& animal: animals) {
    std::cout << animal.left << " " << animal.right << std::endl;
  }

  return 0;
}