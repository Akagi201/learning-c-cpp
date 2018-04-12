#include <string>
#include <iostream>

#include "boost/multi_index_container.hpp"
#include "boost/multi_index/random_access_index.hpp"
#include "boost/multi_index/ordered_index.hpp"
#include "boost/multi_index/mem_fun.hpp"

// Employee只有name一个成员
// name_length成员函数返回name的长度
struct Employee {
    Employee(const std::string& name_) :
        name(name_) {
        }

    std::size_t name_length() const { return name.size(); }

    std::string name;
};// Employee

typedef boost::multi_index::multi_index_container<
    Employee,
    boost::multi_index::indexed_by<
        // 第一个索引使用 const_mem_fun 定义，fun取Employee::name_length，也就是name的长度
        boost::multi_index::ordered_non_unique<
            boost::multi_index::const_mem_fun<Employee, std::size_t, &Employee::name_length>,
            // 降序排列
            std::greater<std::size_t>
        >,
        // 支持按照插入顺序随机读写
        boost::multi_index::random_access<>
    >
> EmployeeSet;

int main() {
    EmployeeSet employees;

    employees.insert({"Jeff Dean"});
    employees.insert({"Google"});
    employees.insert({"Bidu"});
    employees.insert({"Markus Heule"});
    employees.insert({"Vlad Losev"});

    // ordered_non_unique按照name长度降序输出
    // Markus Heule
    // Vlad Losev
    // Jeff Dean
    // Google
    // Bidu
    for (const auto employee : employees.get<0>()) {
        std::cout << employee.name << std::endl;
    }

    // random_access按照插入顺序顺序输出
    // Jeff Dean
    // Google
    // Bidu
    // Markus Heule
    // Vlad Losev
    for (const auto employee : employees.get<1>()) {
        std::cout << employee.name << std::endl;
    }

    // random_access 支持 operator[] at capacity reserve 等接口
    // Jeff Dean
    std::cout << employees.get<1>()[0].name << std::endl;
    // Google
    std::cout << employees.get<1>().at(1).name << std::endl;

    return 0;
}