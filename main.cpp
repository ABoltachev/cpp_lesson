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

    // TestLib::Class::PrivateEmployeeDataImprovedClass private_emp_3; А это нет !!!
    TestLib::Class::PrivateEmployeeDataImprovedClass private_emp_3 = 10; // А это норм
    // TestLib::Class::PrivateEmployeeDataImprovedClass private_emp_3 (0); или так
    // TestLib::Class::PrivateEmployeeDataImprovedClass private_emp_3 {0}; или так
    private_emp_3.print();
    TestLib::Class::PrivateEmployeeDataImprovedClass private_emp_4 = private_emp_3;
    // TestLib::Class::PrivateEmployeeDataImprovedClass private_emp_4 (private_emp_3); или так
    // TestLib::Class::PrivateEmployeeDataImprovedClass private_emp_4 {private_emp_3}; или так
    private_emp_4.print();

    // TestLib::Class::PrivateEmployeeDataImprovedClass private_emp_3 = 0, 50, 11; А это уже не норм

    TestLib::Struct::Employee emp_struct {25, "Anchovy Struct"};
    emp_struct.print();

    return 0;
}
