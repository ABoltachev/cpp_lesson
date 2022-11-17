#include "integers.hpp"

namespace TestLib::Method {
    Integer::Integer(int data) : m_data(data) {}

    Integer Integer::operator+(const Integer &b) const {
        return Integer(m_data + b.m_data);
    }
    Integer Integer::operator-(const Integer &b) const {
        return Integer(m_data - b.m_data);
    }
    Integer Integer::operator*(const Integer &b) const {
        return Integer(m_data * b.m_data);
    }
    Integer Integer::operator/(const Integer &b) const {
        return Integer(m_data / b.m_data);
    }

    Integer Integer::operator+(int b) const {
        return Integer(m_data + b);
    }
    Integer Integer::operator-(int b) const {
        return Integer(m_data - b);
    }
    Integer Integer::operator*(int b) const {
        return Integer(m_data * b);
    }
    Integer Integer::operator/(int b) const {
        return Integer(m_data / b);
    }
}
