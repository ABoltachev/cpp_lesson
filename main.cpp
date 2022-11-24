#include "employee.hpp"

#include <iostream>

/*
*/

int main() {
    std::cout << "Constructing A: \n";
    TestLib::A a;

    std::cout << "Constructing B: \n";
    TestLib::B b;

    std::cout << "Constructing C: \n";
    TestLib::C c;

    std::cout << "Constructing D: \n";
    TestLib::D d;

    TestLib::Employee emp;
    // emp.getAge();

    TestLib::Child child;
    // child.getId(); // Ошибка компиляции, непонятно какой метод вызывать
    child.ParentA::getId();

    TestLib::Human *ptr = new TestLib::Programmer("C++");
    ptr->print();
    reinterpret_cast<TestLib::Programmer*>(ptr)->print();

    TestLib::Human &ref = emp;
    ref.print();

    TestLib::Human obj = emp; // Происходит обрезание данных до родительского класса
    return 0;
}
