#include <iostream>
#include <string>
#include "LessonLib.hpp"

int main () {
    TestLib::Class::Employee emp_class {0, 25, "Anchovy Class"};
    emp_class.print();

    TestLib::Class::PrivateEmployeeData private_emp_1; // {50, 11, 0}; такая запись невалидна из-за приватных полей. И так тоже нельзя {0};
    private_emp_1.print();
    private_emp_1.salary() = 10;
    std::cout << private_emp_1.salary() << std::endl;
    private_emp_1.setSalary(50);
    private_emp_1.setGrade(11);
    private_emp_1.print();
    TestLib::Class::PrivateEmployeeData private_emp_2 = private_emp_1; // Эт норм

    std::cout << "PrivateEmployeeDataImprovedClass::counter: " << TestLib::Class::PrivateEmployeeDataImprovedClass::count() << std::endl;
    // TestLib::Class::PrivateEmployeeDataImprovedClass private_emp_3; А это нет !!!
    TestLib::Class::PrivateEmployeeDataImprovedClass private_emp_3 = 10; // А это норм
    // TestLib::Class::PrivateEmployeeDataImprovedClass private_emp_3 (0); или так
    // TestLib::Class::PrivateEmployeeDataImprovedClass private_emp_3 {0}; или так
    private_emp_3.print();
    TestLib::Class::PrivateEmployeeDataImprovedClass private_emp_4 = private_emp_3;
    // TestLib::Class::PrivateEmployeeDataImprovedClass private_emp_4 (private_emp_3); или так
    // TestLib::Class::PrivateEmployeeDataImprovedClass private_emp_4 {private_emp_3}; или так
    TestLib::Class::PrivateEmployeeDataImprovedClass pp = private_emp_4.print();
    pp.print();
    std::cout << "PrivateEmployeeDataImprovedClass::counter: " << private_emp_4.count() << std::endl;

    // TestLib::Class::PrivateEmployeeDataImprovedClass private_emp_3 = 0, 50, 11; А это уже не норм

    TestLib::Struct::Employee emp_struct {25, "Anchovy Struct"};
    emp_struct.print();

    // TestLib::Class::print(emp_class, private_emp_4);

    std::cout << "######## Part 2 ########" << std::endl;
    TestLib::Class::Test a(1), b(2), c(3);
    TestLib::Class::Test d(10);
    d.add(15).sub(1); // d = d + 15 - 1;

    // exit(0); // при вызове exit деструкторы не будут вызваны

    TestLib::Class::StaticTest aa, bb;

    TestLib::Class::PrivateEmployeeDataImprovedClass(0).print(); // анонимный объект

    return 0;
}
