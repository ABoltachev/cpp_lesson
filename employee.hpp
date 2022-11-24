#ifndef EMPLYEE_H
#define EMPLYEE_H

#include <iostream>
#include <string>

namespace TestLib {
    class Human {
    // public:
    protected:
        std::string m_name;
        uint16_t m_age;

    public:
        Human(const std::string &name="", uint16_t age=0);

        uint16_t getAge() const;

        void print() const;
    };

    class Employee : public Human {
    private:
        using Human::getAge;
    protected:
        // uint16_t getAge() = delete;
        uint64_t m_id;
        float m_salary;
    public:
        Employee(const std::string &name="", uint16_t age=0, uint64_t id=0, float salary=0.);

        void print() const;
    };

    class Programmer : public Employee {
    protected:
        std::string m_prog_lang;

    public:
        Programmer(const std::string &prog_lang, const std::string &name="", uint16_t age=0,
                   uint64_t id=0, float salary=0.);

        void print() const;
    };

    class A {
    public:
        A() {
            std::cout << "A" << std::endl;
        }
    };
    
    class B: public A {
    public:
        B() {
            std::cout << "B" << std::endl;
        }
    };
    
    class C: public B {
    public:
        C() {
            std::cout << "C" << std::endl;
        }
    };
    
    class D: public C {
    public:
        D() {
            std::cout << "D" << std::endl;
        }
    };

    class RootParent {
    protected:
        size_t size;
    };

    class ParentA : public RootParent {
    private:
        uint32_t m_id;
    public:
        uint32_t getId() {return m_id;}
    };

    class ParentB : public RootParent {
    private:
        uint64_t m_id;
    public:
        uint64_t getId() {return m_id;}
    };

    class Child : public ParentA, public ParentB {};
}

#endif // EMPLYEE_H
