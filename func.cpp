#include "integers.hpp"

namespace TestLib::Func {
    Integer::Integer(int data) : m_data(data) {}

    int Integer::getData() const {
        return m_data;
    }

    Integer operator+(const Integer &a, const Integer &b) {
        return {a.getData() + b.getData()};
    }
    Integer operator-(const Integer &a, const Integer &b) {
        return {a.getData() - b.getData()};
    }
    Integer operator*(const Integer &a, const Integer &b) {
        return {a.getData() * b.getData()};
    }
    Integer operator/(const Integer &a, const Integer &b) {
        return {a.getData() / b.getData()};
    }

    Integer operator+(int a, const Integer &b) {
        return {a + b.getData()};
    }
    Integer operator-(int a, const Integer &b) {
        return {a - b.getData()};
    }
    Integer operator*(int a, const Integer &b) {
        return {a * b.getData()};
    }
    Integer operator/(int a, const Integer &b) {
        return {a / b.getData()};
    }

    Integer operator+(const Integer &a, int b) {
        return {a.getData() + b};
    }
    Integer operator-(const Integer &a, int b) {
        return {a.getData() - b};
    }
    Integer operator*(const Integer &a, int b) {
        return {a.getData() * b};
    }
    Integer operator/(const Integer &a, int b) {
        return {a.getData() / b};
    }
}
