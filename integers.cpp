#include "integers.hpp"

namespace TestLib {
    Integer::Integer(int data) : m_data(data) {}
    Integer::Integer(const Integer &another) : m_data(another.m_data) {
        std::cout << "Copy constructor" << std::endl;
    }

    Integer operator+(const Integer &a, const Integer &b) {
        return {a.m_data + b.m_data};
    }
    Integer operator-(const Integer &a, const Integer &b) {
        return {a.m_data - b.m_data};
    }
    Integer operator*(const Integer &a, const Integer &b) {
        return {a.m_data * b.m_data};
    }
    Integer operator/(const Integer &a, const Integer &b) {
        return {a.m_data / b.m_data};
    }

    Integer operator+(int a, const Integer &b) {
        return {a + b.m_data};
    }
    Integer operator-(int a, const Integer &b) {
        return {a - b.m_data};
    }
    Integer operator*(int a, const Integer &b) {
        return {a * b.m_data};
    }
    Integer operator/(int a, const Integer &b) {
        return {a / b.m_data};
    }

    Integer operator+(const Integer &a, int b) {
        return {a.m_data + b};
    }
    Integer operator-(const Integer &a, int b) {
        return {a.m_data - b};
    }
    Integer operator*(const Integer &a, int b) {
        return {a.m_data * b};
    }
    Integer operator/(const Integer &a, int b) {
        return {a.m_data / b};
    }

    Integer Integer::operator-() const {
        return {-m_data};
    }
    Integer Integer::operator+() const {
        return {m_data};
    }
    bool Integer::operator!() const {
        return !m_data;
    }

    bool operator==(const Integer &lft, const Integer &rgh) {
        return lft.m_data == rgh.m_data;
    }
    bool operator!=(const Integer &lft, const Integer &rgh) {
        return !(lft.m_data == rgh.m_data);
    }
    bool operator>(const Integer &lft, const Integer &rgh) {
        return lft.m_data > rgh.m_data;
    }
    bool operator<(const Integer &lft, const Integer &rgh) {
        return lft.m_data < rgh.m_data;
    }
    bool operator>=(const Integer &lft, const Integer &rgh) {
        return !(lft.m_data < rgh.m_data);
    }
    bool operator<=(const Integer &lft, const Integer &rgh) {
        return !(lft.m_data > rgh.m_data);
    }

    Integer& Integer::operator++() {
        ++m_data;
        return *this;
    }
    Integer& Integer::operator--() {
        --m_data;
        return *this;
    }
    Integer Integer::operator++(int) {
        Integer tmp {m_data};
        ++m_data;
        return tmp;
    }
    Integer Integer::operator--(int) {
        Integer tmp {m_data};
        --m_data;
        return tmp;
    }

    Integer::operator int() {
        return m_data;
    }
    Integer::operator double() {
        return static_cast<double>(m_data);
    }

    std::ostream& operator<<(std::ostream &out, const Integer &obj) {
        out << obj.m_data;
        return out;
    }
    std::istream& operator>>(std::istream &in, Integer &obj) {
        in >> obj.m_data;
        return in;
    }

    // var = var; самокопирование
    // a = b = c;
    Integer& Integer::operator=(const Integer &another) {
        if (this != &another) {
            m_data = another.m_data;
        }
        return *this;
    }

    int Accumulator::operator()(int a) {
        m_data += a;
        return m_data;
    }

    int& Array::operator[](bool is_even) {
        return is_even ? m_data[1] : m_data[0];
    }
    const int& Array::operator[](bool is_even) const {
        return is_even ? m_data[1] : m_data[0];
    }
}
