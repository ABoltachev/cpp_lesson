#include <testlib/templates.hpp>
#include <stdexcept>

#include <iostream>

/*
    non-type:
        * целочисленное значение или перечисление;
        * указатель или ссылка на объект класса;
        * указатель или ссылка на функцию;
        * указатель или ссылка на метод класса;
        * std::nullptr_t
*/

double div(double a, double b) {
    if (b == 0) {
        throw TestLib::ValueError("Can't divide by zero");
    }
    return a / b;
}

int main() {
    try {
        TestLib::Functor func(div);
        func(12, 0);
    }
    catch (const TestLib::ValueError &ex) {
        std::cerr << "Main catch exception: " << ex.what() << std::endl;
    }

    std::cout << TestLib::max(10, 5) << std::endl;
    std::cout << TestLib::max<double>(10, 15.5) << std::endl;
    std::cout << TestLib::max<char>(65, 66) << std::endl;

    TestLib::Array<int> arr_1(5);
    TestLib::Array<double> arr_2(5);
    std::cout << "arr_1 size: " << arr_1.getLength() << std::endl;
    std::cout << "arr_2 size: " << arr_2.getLength() << std::endl;

    TestLib::StaticArray<int, 5> static_arr_1;
    TestLib::StaticArray<double, 5> static_arr_2;
    TestLib::StaticArray<char, 5> static_arr_3;
    std::cout << "static_arr_1 size: " << static_arr_1.getLength() << std::endl;
    std::cout << "static_arr_2 size: " << static_arr_2.getLength() << std::endl;
    std::cout << "static_arr_3 size: " << static_arr_3.getLength() << std::endl;
    TestLib::print(static_arr_1);
    TestLib::print(static_arr_2);
    TestLib::print(static_arr_3);
    return 0;
}
