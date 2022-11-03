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
        class Employee {
        public:
            uint64_t m_id;
            uint16_t m_age;
            std::string m_name;

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
            float getSalary();
            // @m_salary.setter
            void setSalary(float salary);

            // @property
            uint16_t getGrade();
            // @m_grade.setter
            void setGrade(uint16_t grade);

            void print();
        };

        class PrivateEmployeeDataImprovedClass {
        private:
            uint64_t m_id;
            float m_salary; // Эти поля не имеют явного модификатора доступа
            uint16_t m_grade; // поэтому по умолчанию они private
            uint64_t &m_ref;
            uint64_t *m_ptr = nullptr;
        public:
            PrivateEmployeeDataImprovedClass(uint64_t id, float salary=0., u_int16_t grade=0);

            PrivateEmployeeDataImprovedClass(const PrivateEmployeeDataImprovedClass&);

            // @property и @m_salary.setter
            float& salary();

            // @property
            float getSalary();
            // @m_salary.setter
            void setSalary(float salary);

            // @property
            uint16_t getGrade();
            // @m_grade.setter
            void setGrade(uint16_t grade);

            void print();

            ~PrivateEmployeeDataImprovedClass();
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
