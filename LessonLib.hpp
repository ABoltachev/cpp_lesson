#ifndef TESTLIB_H
#define TESTLIB_H

#include <iostream>
#include <string>

typedef int Data;
using Data = int;

/*
    !!! РЕКОМЕНДАЦИИ !!!
     * Использовать структуры только в качестве хранилища данных, а классы уже и для реализации функционала для хранимых данных
     * Все поля классов делать приватными
     * Не предоставлять доступ к полям классов из вне
     * Добавлять префикс или суфикс к полям класса, чтобы можно было отличить их от других конструкций
*/

/*
    Есть 3 модификатора доступа:
        public: делает члены открытыми;
        private: делает члены закрытыми;
        protected: открывает доступ к членам только для дружественных и дочерних классов
*/

namespace TestLib {
    namespace Class {
        class StaticTest {
        public:
            static uint64_t m_id;
        };

        class Test {
        private:
            u_int32_t m_id;
        public:
            Test(/* Test* const this, */ u_int32_t id) : m_id(id) {
                std::cout << "Constructor with id: " << this->m_id << std::endl;
                std::cout << "This: " << this << std::endl;
            }

            inline Test& add(u_int32_t i);

            inline Test& sub(u_int32_t i);

            ~Test(/* Test* const this */) {
                std::cout << "Destructor with id: " << this->m_id << std::endl;
            }
        };

        Test& Test::add(u_int32_t i) {
            m_id += i;
            return *this;
        }

        Test& Test::sub(u_int32_t i) {
            m_id -= i;
            return *this;
        }

        class PrivateEmployeeDataImprovedClass;

        class Employee {
        private:
            friend void print(const Employee &emp, const PrivateEmployeeDataImprovedClass &private_emp); // Не имеет значения в какой области видимости объявлена
        public:
            uint64_t m_id;
            uint16_t m_age;
            std::string m_name;

            void print() const;
            void print();
        };

        class PrivateEmployeeData {
            float m_salary; // Эти поля не имеют явного модификатора доступа
            uint16_t m_grade; // поэтому по умолчанию они private
        public:
            uint64_t m_id;

            // @property и @m_salary.setter
            float& salary();

            // @property
            float getSalary() const;
            // @m_salary.setter
            void setSalary(float salary);

            // @property
            uint16_t getGrade() const;
            // @m_grade.setter
            void setGrade(uint16_t grade);

            void print() const;
        };

        class PrivateEmployeeDataImprovedClass; // Это необходимо, чтобы сделать метод AnotherPrinter::print дружественным к PrivateEmployeeDataImprovedClass

        class AnotherPrinter {
        public:
            static void print(const PrivateEmployeeDataImprovedClass &obj);
        };

        class PrivateEmployeeDataImprovedClass {
        private:
            uint64_t m_id;
            float m_salary; // Эти поля не имеют явного модификатора доступа
            uint16_t m_grade; // поэтому по умолчанию они private
            uint64_t &m_ref;
            uint64_t *m_ptr = nullptr;
            static uint64_t counter;
            static const uint64_t some_constant = 10;
        public:
            PrivateEmployeeDataImprovedClass(uint64_t id, float salary=0., u_int16_t grade=0);

            PrivateEmployeeDataImprovedClass(float salary, uint16_t grade);

            PrivateEmployeeDataImprovedClass(const PrivateEmployeeDataImprovedClass&);

            // @property и @m_salary.setter
            float& salary();

            // @property
            float getSalary() const;
            // @m_salary.setter
            void setSalary(float salary);

            // @property
            uint16_t getGrade() const;
            // @m_grade.setter
            void setGrade(uint16_t grade);

            PrivateEmployeeDataImprovedClass print() const;

            static uint64_t count();

            friend void print(const Employee &emp, const PrivateEmployeeDataImprovedClass &private_emp);

            friend class Printer; // Теперь в Printer доступны все поля из PrivateEmployeeDataImprovedClass, но не наоборот
            friend void AnotherPrinter::print(const PrivateEmployeeDataImprovedClass&);

            ~PrivateEmployeeDataImprovedClass();
        };

        class Printer {
        public:
            static void print(const PrivateEmployeeDataImprovedClass &obj);
        };
    }

    namespace Struct {
        struct Employee {
            uint16_t m_age; // Эти поля не имеют явного модификатора доступа
            std::string m_name; // поэтому по умолчанию они public

            void print();
        };
    }
}

#endif
