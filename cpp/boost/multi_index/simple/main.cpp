#include <algorithm>
#include <iostream>
#include <string>

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/ordered_index.hpp>

int main() {
  boost::multi_index::multi_index_container<std::string> employees;

  employees.insert("Jeff Dean");
  employees.insert("Google");
  employees.insert("Baidu");
  employees.insert("Markus Heule");
  employees.insert("Vlad Losev");
  employees.insert("Ufo");

  for (const auto& employee: employees) {
    std::cout << employee << std::endl;
  }

  std::cout << employees.size() << std::endl;
  employees.erase(employees.find("Ufo"));

  for (const auto& employee: employees) {
    std::cout << employee << std::endl;
  }

  auto it1 = employees.lower_bound("J");
  auto it2 = employees.upper_bound("N");

  for (; it1 != it2; ++it1) {
    std::cout << *it1 << std::endl;
  }

  return 0;
}