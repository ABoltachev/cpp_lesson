#ifndef VIRTUAL_H
#define VIRTUAL_H

#include <iostream>
#include <string>

#ifdef _WIN32
    #ifdef TESTLIB_EXPORTS
        #define TESTLIB_API __declspec(dllexport)
    #else
        #define TESTLIB_API __declspec(dllimport)
    #endif
#else
    #define TESTLIB_API
#endif

namespace TestLib {
    #pragma region first
    class TESTLIB_API Animal {
    protected:
        std::string m_name;
    public:
        Animal(std::string name) : m_name(name) {}

        std::string getName() const { return m_name; }
        virtual const char* speak() const = 0;
    };
    
    class TESTLIB_API Cat : public Animal {
    public:
        Cat(std::string name) : Animal(name) {}

        const char* speak() const {
            Animal::speak();
            return "Meow";
        } // Сигнатура витруальных методов должна совпадать
    };

    class TESTLIB_API Dog : public Animal {
    public:
        Dog(std::string name) : Animal(name) {}

        const char* speak() const { return "Woof"; }
    };
    #pragma endregion first

    #pragma region second
    // class A {
    // public:
    //     virtual const char* getName1(int x) { return "A"; }
    //     virtual const char* getName2(int x) { return "A"; }
    //     virtual const char* getName3(int x) { return "A"; }
    // };
    
    // class B : public A {
    // public:
    //     virtual const char* getName1(short int x) override { return "B"; }  // ошибка компиляции, метод не является переопределением
    //     virtual const char* getName2(int x) const override { return "B"; }  // ошибка компиляции, метод не является переопределением
    //     virtual const char* getName3(int x) override { return "B"; }  // всё хорошо, метод является переопределением A::getName3(int)
    
    // };

    // class C {
    // public:
    //     virtual const char* getName() { return "A"; }
    // };

    // class D : public C {
    // public:
    //     virtual const char* getName() override final { return "B"; } // всё хорошо, переопределение A::getName()
    // };

    // class E : public D {
    // public:
    //     virtual const char* getName() override { return "C"; } // ошибка компиляции: переопределение метода B::getName(), который является final
    // };

    // class F {
    // public:
    //     virtual const char* getName() { return "A"; }
    // };

    // class G final : public F { // обратите внимание на модификатор final здесь
    // public:
    //     virtual const char* getName() override { return "B"; }
    // };
    
    // class H : public G { // ошибка компиляции: нельзя наследовать final-класс
    // public:
    //     virtual const char* getName() override { return "C"; }
    // };

    // class TESTLIB_API Parent {
    // public:
    //     // Этот метод getThis() возвращает указатель на класс Parent
    //     virtual Parent* getThis() { std::cout << "called Parent::getThis()\n"; return this; }
    //     void printType() { std::cout << "returned a Parent\n"; }
    // };

    // class TESTLIB_API Child : public Parent {
    // public:
    //     // Обычно, типы возврата переопределений и виртуальных функций родительского класса должны совпадать.
    //     // Однако, поскольку Child наследует класс Parent, следующий метод может возвращать Child* вместо Parent*
    //     virtual Child* getThis() { std::cout << "called Child::getThis()\n";  return this; }
    //     void printType() { std::cout << "returned a Child\n"; }
    // };
    #pragma endregion second

    #pragma region third
    class TESTLIB_API ParentB {
    public:
        virtual ~ParentB() {
            std::cout << "Calling ~ParentB()" << std::endl;
        }
    };

    class TESTLIB_API ChildB : public ParentB {
    private:
        int* m_array;

    public:
        ChildB(int length) {
            m_array = new int[length];
        }

        ~ChildB() {
            std::cout << "Calling ~ChildB()" << std::endl;
            delete[] m_array;
        }
    };
    #pragma endregion third
}

#endif // VIRTUAL_H
