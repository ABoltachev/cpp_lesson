#include <testlib/virtual.hpp>

#include <iostream>

void report(TestLib::Animal &animal) {
    std::cout << animal.getName() << " says " << animal.speak() << std::endl;
}

int main() {
    // TestLib::Animal a; Нельзя создавать объекты абстрактных классов
    TestLib::Cat cat("Matros");
    TestLib::Dog dog("Barsik");

    // dog.Animal::speak();

    report(cat);
    report(dog);

    // TestLib::Child ch;
    // TestLib::Parent *p = &ch;
    // ch.getThis()->printType();
    // p->getThis()->printType();

    // TestLib::ChildB *child = new TestLib::ChildB(7);
    // TestLib::ParentB *parent = child;
    // delete parent;
}
