#include <iostream>
#include <ctime>

#include "rand.hpp"

int main() {
  std::cout << "time: " << std::time(nullptr) << std::endl;
  auto r = eosio::random(uint64_t(std::time(nullptr)));
  std::cout << "rand: " << r.next() << std::endl;

  return 0;
}