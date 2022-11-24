#include "employee.hpp"

namespace TestLib {
    Human::Human(const std::string &name, uint16_t age) : m_name(name), m_age(age) {}

    // Employee::Employee(const std::string &name, uint16_t age, uint64_t id,
    //                    float salary) : m_id(id), m_salary(salary) {
    //     m_name = name;
    //     m_age = age;
    // }

    Employee::Employee(const std::string &name, uint16_t age, uint64_t id,
                       float salary) : m_id(id), m_salary(salary), Human(name, age) {}

    // Programmer::Programmer(const std::string &prog_lang, const std::string &name,
    //                        uint16_t age, uint64_t id, float salary) : m_prog_lang(prog_lang) {
    //     m_name = name;
    //     m_age = age;
    //     m_id = id;
    //     m_salary = salary;
    // }

    Programmer::Programmer(const std::string &prog_lang, const std::string &name,
                           uint16_t age, uint64_t id, float salary)
                            : m_prog_lang(prog_lang), Employee(name, age, id, salary) {}

    uint16_t Human::getAge() const {
        return m_age;
    }

    void Human::print() const {
        std::cout << "Human info [Name: " << m_name << ", age: " << m_age << ']' << std::endl;
    }

    void Employee::print() const {
        // std::cout << "Human info [Name " << m_name << ", age: " << m_age << ']' << std::endl;
        Human::print();
        std::cout << "Emplyee info [Id: " << m_id << ", salary: " << m_salary << ']' << std::endl;
    }

    void Programmer::print() const {
        // std::cout << "Human info [Name " << m_name << ", age: " << m_age << ']' << std::endl;
        // std::cout << "Emplyee info [ID: " << m_id << ", salary: " << m_salary << ']' << std::endl;
        Employee::print();
        // Human::print();
        std::cout << "Programmer info [Prog lang: " << m_prog_lang << ']' << std::endl;
    }

}
