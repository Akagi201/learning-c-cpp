#include <iostream>
#include <string>

#include "boost/multi_index_container.hpp"//boost::multi_index::multi_index_container
#include "boost/multi_index/ordered_index.hpp"//insert
#include "boost/multi_index/identity.hpp"//identity
#include "boost/multi_index/member.hpp"//member

struct Employee {
    Employee(int id_, const std::string& name_) :
        id(id_),
        name(name_) {
        }

    int id;
    std::string name;

    //default compare by id
    bool operator<(const Employee& employee) const {
        return id < employee.id;
    }

    friend std::ostream& operator<<(std::ostream& out, const Employee& employee) {
        out << employee.id << "\t" << employee.name << std::endl;
        return out;
    }
};//Employee

typedef boost::multi_index::multi_index_container<
        Employee,
        boost::multi_index::indexed_by<
            boost::multi_index::ordered_unique<
                boost::multi_index::identity<Employee> >,
            boost::multi_index::ordered_non_unique<
                boost::multi_index::member<Employee, std::string, &Employee::name> >
            >
        > EmployeeSet;

int main() {
    EmployeeSet employees;

    employees.insert({5, "Jeff Dean"});
    employees.insert({1, "Google"});
    employees.insert({3, "Bidu"});
    employees.insert({2, "Markus Heule"});
    employees.insert({4, "Vlad Losev"});

    //1       Google
    //2       Markus Heule
    //3       Bidu
    //4       Vlad Losev
    //5       Jeff Dean
    std::copy(
            employees.begin(), //equal to employees.get<0>()
            employees.end(),
            std::ostream_iterator<Employee>(std::cout));

    //3       Bidu
    //1       Google
    //5       Jeff Dean
    //2       Markus Heule
    //4       Vlad Losev
    const EmployeeSet::nth_index<1>::type& name_index = employees.get<1>();
    std::copy(
            name_index.begin(),
            name_index.end(),
            std::ostream_iterator<Employee>(std::cout));

    return 0;
}