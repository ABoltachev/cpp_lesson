#include "LessonLib.hpp"

namespace TestLib {
    namespace Class {
        uint64_t PrivateEmployeeDataImprovedClass::counter = 0;

        void Employee::print() const {
            std::cout << "Employee_" << m_id << std::endl;
            std::cout << "\tAge: " << m_age << ", name: " << m_name << std::endl;
        }

        void Employee::print() {
            std::cout << "Employee_" << m_id << std::endl;
            std::cout << "\tAge: " << m_age << ", name: " << m_name << std::endl;
        }

        void PrivateEmployeeData::print() const {
            std::cout << "Employee_" << m_id << std::endl;
            std::cout << "\tSalary: " << m_salary << ", grade: " << m_grade << std::endl;
        }

        float& PrivateEmployeeData::salary() {
            return m_salary;
        }

        float PrivateEmployeeData::getSalary() const {
            // m_salary = 0;
            return m_salary;
        }

        void PrivateEmployeeData::setSalary(float salary) {
            m_salary = salary;
        }

        uint16_t PrivateEmployeeData::getGrade() const {
            return m_grade;
        }

        void PrivateEmployeeData::setGrade(uint16_t grade) {
            m_grade = grade;
        }

        PrivateEmployeeDataImprovedClass PrivateEmployeeDataImprovedClass::print() const {
            std::cout << this << std::endl;
            std::cout << "Employee_" << m_id << '(' << counter << ')' << std::endl;
            std::cout << "\tSalary: " << m_salary << ", grade: " << m_grade << std::endl;
            return {0};
        }

        PrivateEmployeeDataImprovedClass::PrivateEmployeeDataImprovedClass(uint64_t id, float salary, u_int16_t grade)
            : m_ref(id), m_grade(grade), m_salary(salary)
        {
            counter++;
            m_id = id;
        }

        PrivateEmployeeDataImprovedClass::PrivateEmployeeDataImprovedClass(float salary, u_int16_t grade)
            : PrivateEmployeeDataImprovedClass(0, salary, grade) //, m_id(0) так нельзя
        {}

        PrivateEmployeeDataImprovedClass::PrivateEmployeeDataImprovedClass(const PrivateEmployeeDataImprovedClass &other)
            : m_id(other.m_id), m_grade(other.m_grade), m_salary(other.m_salary), m_ref(other.m_ref)
        {
            counter++;
            if (other.m_ptr) {
                m_ptr = new uint64_t(*other.m_ptr);
            }
        }

        float& PrivateEmployeeDataImprovedClass::salary() {
            return m_salary;
        }

        float PrivateEmployeeDataImprovedClass::getSalary() const {
            return m_salary;
        }

        void PrivateEmployeeDataImprovedClass::setSalary(float salary) {
            m_salary = salary;
        }

        uint16_t PrivateEmployeeDataImprovedClass::getGrade() const {
            return m_grade;
        }

        void PrivateEmployeeDataImprovedClass::setGrade(uint16_t grade) {
            m_grade = grade;
        }

        uint64_t PrivateEmployeeDataImprovedClass::count() {
            // this->m_id; // В статических методах нет указателя this
            return counter;
        }

        PrivateEmployeeDataImprovedClass::~PrivateEmployeeDataImprovedClass() {
            delete m_ptr;
        }

        void print(const Employee &emp, const PrivateEmployeeDataImprovedClass &private_emp) {
            if (emp.m_id == private_emp.m_id) {
                emp.print();
                private_emp.print();
            }
        }

        void Printer::print(const PrivateEmployeeDataImprovedClass &obj) {
            std::cout << "Employee_" << obj.m_id << '(' << PrivateEmployeeDataImprovedClass::counter << ')' << std::endl;
            std::cout << "\tSalary: " << obj.m_salary << ", grade: " << obj.m_grade << std::endl;
        }

        void AnotherPrinter::print(const PrivateEmployeeDataImprovedClass &obj) {
            std::cout << "Employee_" << obj.m_id << '(' << PrivateEmployeeDataImprovedClass::counter << ')' << std::endl;
            std::cout << "\tSalary: " << obj.m_salary << ", grade: " << obj.m_grade << std::endl;
        }
    }

    namespace Struct {
        void Employee::print() {
            std::cout << "Age: " << m_age << ", name: " << m_name << std::endl;
        }
    }
}
