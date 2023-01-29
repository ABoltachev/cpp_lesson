#include <testlib/smart_pointer.hpp>

Item1::Item1() {
    std::cout << "Item1 acquired" << std::endl;
}

Item1::~Item1() {
    std::cout << "Item1 destroyed" << std::endl;
}

Item2::Item2() {
    std::cout << "Item2 acquired" << std::endl;
}

Item2::~Item2() {
    std::cout << "Item2 destroyed" << std::endl;
}

Item3::Item3() {
    std::cout << "Item3 acquired" << std::endl;
}

Item3::~Item3() {
    std::cout << "Item3 destroyed" << std::endl;
}

Example::Example(int data) : m_data(data) {}

std::ostream& operator<<(std::ostream &out, const Example &obj) {
    return out << obj.m_data;
}

Example& testFunc1() {
    Example tmp {11};
    return tmp;
}

Example&& testFunc2() {
    return {12};
}

void testFunc(const int &ref) {
    std::cout << "l-value ref: " << ref << std::endl;
}

void testFunc(int &&ref) {
    std::cout << "r-value ref: " << ref << std::endl;
}
