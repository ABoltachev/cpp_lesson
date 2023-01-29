#include <iostream>

#include <testlib/smart_pointer.hpp>
#include <testlib/timer.hpp>
#include <testlib/array.hpp>
#include <memory>

int main() {
    std::unique_ptr<Item1> ptr1 = std::make_unique<Item1>();
    std::unique_ptr<Item1> ptr2(std::move(ptr1));
    std::unique_ptr<Item1> ptr3(new Item1);

    std::shared_ptr<Item1> ptr4 = std::make_shared<Item1>();
    std::shared_ptr<Item1> ptr5(ptr4);
    std::shared_ptr<Item1> ptr6(std::move(ptr3));

    std::weak_ptr<Item1> ptr7(ptr6);
    ptr7.lock();

    Timer t;
    {
        AutoPtr<Item1> item1(new Item1);
        AutoPtr<Item1> item2;

        std::cout << "item1 is " << (item1.isNull() ? "null" : "not null") << std::endl;
        std::cout << "item2 is " << (item2.isNull() ? "null" : "not null") << std::endl;

        item2 = item1;

        std::cout << "item1 is " << (item1.isNull() ? "null" : "not null") << std::endl;
        std::cout << "item2 is " << (item2.isNull() ? "null" : "not null") << std::endl;
    }

    int val = 15;
    int &l_ref = val; // l-value ref
    int &&r_ref = 15; // r-value ref

    Example &&r_ref_2 = {15};
    std::cout << r_ref_2 << std::endl;

    testFunc(15);
    testFunc(val);

    std::cout << "#####" << std::endl;
    {
        SmartPtr<Item2> firtItem;
        firtItem = generateItem();
    }
    std::cout << "#####" << std::endl;

    std::cout << "#####" << std::endl;
    {
        SmarterPtr<Item3> secondItem;
        secondItem = generateItem(1);
    }
    std::cout << "#####" << std::endl;

    std::cout << "@@@@@" << std::endl;
    CopyArray<int> c_arr(100000000);

    for (int i = 0; i < c_arr.getLength(); i++)
        c_arr[i] = i;

    t.reset();
    c_arr = cloneArrayAndDouble(c_arr);

    std::cout << t.elapsed() << std::endl;
    std::cout << "@@@@@" << std::endl;

    std::cout << "@@@@@" << std::endl;
    MoveArray<int> m_arr(100000000);

    for (int i = 0; i < m_arr.getLength(); i++)
        m_arr[i] = i;

    t.reset();
    m_arr = cloneArrayAndDouble(m_arr);

    std::cout << t.elapsed() << std::endl;
    std::cout << "@@@@@" << std::endl;

    return 0;
}
