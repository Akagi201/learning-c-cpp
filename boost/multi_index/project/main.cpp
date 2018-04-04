#include <string>
#include <iostream>

#include "boost/multi_index_container.hpp"
#include "boost/multi_index/random_access_index.hpp"
#include "boost/multi_index/ordered_index.hpp"
#include "boost/multi_index/mem_fun.hpp"

struct by_name_length {};

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
            // tag 定义
            boost::multi_index::tag<by_name_length>,
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

    // name_length("Google") == 6
    auto name_length_iter = employees.get<by_name_length>().find(6);
    auto iter = employees.project<1>(name_length_iter);

    for (; iter != employees.get<1>().end(); ++iter) {
        std::cout << iter->name << std::endl;
    }

    return 0;
}