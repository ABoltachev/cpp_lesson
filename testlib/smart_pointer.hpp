#ifndef SMART_POINTER_HPP
#define SMART_POINTER_HPP

#include <iostream>

template<typename T>
class AutoPtr {
private:
    T* m_ptr;
public:
    AutoPtr(T *ptr=nullptr);

    ~AutoPtr();

    AutoPtr(AutoPtr &a);

    AutoPtr& operator=(AutoPtr &a);

    T& operator*() const;
    T* operator->() const;
    bool isNull() const;
};

template<typename T>
class SmartPtr {
protected:
    T* m_ptr;
public:
    SmartPtr(T *ptr=nullptr);

    ~SmartPtr();

    SmartPtr(const SmartPtr &a);

    SmartPtr& operator=(const SmartPtr &a);

    T& operator*() const;
    T* operator->() const;
    bool isNull() const;
};

template<typename T>
class SmarterPtr : public SmartPtr<T> {
public:
    SmarterPtr(T *ptr=nullptr);

    SmarterPtr(const SmarterPtr &a);

    SmarterPtr(SmarterPtr &&a);

    SmarterPtr& operator=(SmarterPtr &&a);

    T& operator*() const;
    T* operator->() const;
    bool isNull() const;
};

class Item1 {
public:
    Item1();
    ~Item1();
};

class Item2 {
public:
    Item2();
    ~Item2();
};

class Item3 {
public:
    Item3();
    ~Item3();
};

SmartPtr<Item2> generateItem() {
    SmartPtr<Item2> item(new Item2);
    return item;
}

SmarterPtr<Item3> generateItem(int) {
    SmarterPtr<Item3> item(new Item3);
    return item;
}

class Example {
private:
    int m_data;
public:
    Example(int data=0);

    friend std::ostream& operator<<(std::ostream &out, const Example &obj);
};

Example& testFunc1(); // Так лучше никогда не делать

Example&& testFunc2(); // Так лучше никогда не делать

void testFunc(const int &ref);

void testFunc(int &&ref);

#include "smart_pointer.tpp"

#endif // SMART_POINTER_HPP
