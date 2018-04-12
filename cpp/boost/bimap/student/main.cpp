#include <string>
#include <iostream>

#include <boost/bimap.hpp>

int main() {
  boost::bimap<boost::bimaps::tagged<int, struct id>, boost::bimaps::tagged<std::string, struct name>> students;

  int student_id = 1;
  students.by<id>().insert(std::make_pair(student_id++, "Jeff"));
  students.by<id>().insert(std::make_pair(student_id++, "Tom"));
  students.by<name>().insert(std::make_pair("Ying", student_id++));
  students.by<name>().insert(std::make_pair("Shabby", student_id++));
  students.by<name>().insert(std::make_pair("Tom", student_id++));

  for (const auto& iter: students) {
    std::cout << iter.left << "->" << iter.right << std::endl;
  }

  std::cout << students.by<id>().find(3)->second << std::endl; // Ying
  std::cout << students.by<name>().count("Tom") << std::endl; // 2

  return 0;
}