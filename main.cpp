#include <testlib/virtual.hpp>
#include <stdexcept>

#include <iostream>

void func() {
    // throw -1.;
    auto p =  TestLib::Child();
    throw p;
    std::cout << "Test" << std::endl;
}

int main() {
    TestLib::Parent *ptr = new TestLib::Child;
    std::cout << *ptr << std::endl;

    dynamic_cast<TestLib::Child*>(ptr)->print(std::cout);
    std::cout << std::endl;

    // throw 2;
    try {
        // throw 2;
        throw std::runtime_error("Test");
        func();
    }
    catch (std::runtime_error ex) {
        ex.what()
    }
    catch (TestLib::Parent) {
        std::cout << "Parent ex\n";
    }
    catch (TestLib::Child) {
        std::cout << "Child ex\n";
    }
    catch (float ex) {
        std::cerr << "Float Exception: " << ex << std::endl;
    }
    catch (int ex) {
        std::cerr << "Exception: " << ex << std::endl;
    }
    catch (...) {
        std::cerr << "Unknown error" << std::endl;
    }
    return 0;
}
