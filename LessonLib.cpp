#include "LessonLib.hpp"

namespace TestLib {
    namespace Class {
        void Employee::print() {
            std::cout << "Employee_" << m_id << std::endl;
            std::cout << "\tAge: " << m_age << ", name: " << m_name << std::endl;
        }

        void PrivateEmployeeData::print() {
            std::cout << "Employee_" << m_id << std::endl;
            std::cout << "\tSalary: " << m_salary << ", grade: " << m_grade << std::endl;
        }

        float& PrivateEmployeeData::salary() {
            return m_salary;
        }

        float PrivateEmployeeData::getSalary() {
            return m_salary;
        }

        void PrivateEmployeeData::setSalary(float salary) {
            m_salary = salary;
        }

        uint16_t PrivateEmployeeData::getGrade() {
            return m_grade;
        }

        void PrivateEmployeeData::setGrade(uint16_t grade) {
            m_grade = grade;
        }

        void PrivateEmployeeDataImprovedClass::print() {
            std::cout << "Employee_" << m_id << std::endl;
            std::cout << "\tSalary: " << m_salary << ", grade: " << m_grade << std::endl;
        }

        PrivateEmployeeDataImprovedClass::PrivateEmployeeDataImprovedClass(uint64_t id, float salary, u_int16_t grade)
            : m_ref(id), m_grade(grade), m_salary(salary)
        {
            m_id = id;
        }

        PrivateEmployeeDataImprovedClass::PrivateEmployeeDataImprovedClass(const PrivateEmployeeDataImprovedClass &other)
            : m_id(other.m_id), m_grade(other.m_grade), m_salary(other.m_salary), m_ref(other.m_ref)
        {
            if (other.m_ptr) {
                m_ptr = new uint64_t(*other.m_ptr);
            }
        }

        float& PrivateEmployeeDataImprovedClass::salary() {
            return m_salary;
        }

        float PrivateEmployeeDataImprovedClass::getSalary() {
            return m_salary;
        }

        void PrivateEmployeeDataImprovedClass::setSalary(float salary) {
            m_salary = salary;
        }

        uint16_t PrivateEmployeeDataImprovedClass::getGrade() {
            return m_grade;
        }

        void PrivateEmployeeDataImprovedClass::setGrade(uint16_t grade) {
            m_grade = grade;
        }

        PrivateEmployeeDataImprovedClass::~PrivateEmployeeDataImprovedClass() {
            delete m_ptr;
        }
    }

    namespace Struct {
        void Employee::print() {
            std::cout << "Age: " << m_age << ", name: " << m_name << std::endl;
        }
    }
}
