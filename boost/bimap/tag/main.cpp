#include <string>
#include <iostream>

#include <boost/bimap.hpp>

int main() {
  boost::bimap<boost::bimaps::tagged<int, struct id>, boost::bimaps::tagged<std::string, struct name>> bm;
  bm.by<id>().insert(std::make_pair(1, "samus"));
  bm.by<id>().insert(std::make_pair(2, "adam"));

  bm.by<name>().insert(std::make_pair("link", 10));
  bm.by<name>().insert(std::make_pair("zelda", 11));

  for (const auto& iter: bm) {
    std::cout << iter.left << "->" << iter.right << std::endl;
  }

  return 0;
}