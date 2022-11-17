#include "integers.hpp"

using namespace TestLib::Friend;

namespace TestLib::Friend {
    Integer::Integer(int data) : m_data(data) {}

    Integer operator+(const Integer &a, const Integer &b) {
        return Integer(a.m_data + b.m_data);
    }
    Integer operator-(const Integer &a, const Integer &b) {
        return Integer(a.m_data - b.m_data);
    }
    Integer operator*(const Integer &a, const Integer &b) {
        return Integer(a.m_data * b.m_data);
    }
    Integer operator/(const Integer &a, const Integer &b) {
        return Integer(a.m_data / b.m_data);
    }

    Integer operator+(int a, const Integer &b) {
        return Integer(a + b.m_data);
    }
    Integer operator-(int a, const Integer &b) {
        return Integer(a - b.m_data);
    }
    Integer operator*(int a, const Integer &b) {
        return Integer(a * b.m_data);
    }
    Integer operator/(int a, const Integer &b) {
        return Integer(a / b.m_data);
    }

    Integer operator+(const Integer &a, int b) {
        return Integer(a.m_data + b);
    }
    Integer operator-(const Integer &a, int b) {
        return Integer(a.m_data - b);
    }
    Integer operator*(const Integer &a, int b) {
        return Integer(a.m_data * b);
    }
    Integer operator/(const Integer &a, int b) {
        return Integer(a.m_data / b);
    }
}
