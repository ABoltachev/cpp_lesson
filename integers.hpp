#ifndef TESTLIB_H
#define TESTLIB_H

#include <iostream>

namespace TestLib::Friend {
    class Integer {
    private:
        int m_data;
    public:
        Integer() = default;

        explicit Integer(int data); // Ключевое слово explicit запрещает использовать неявное преобразование типа для записи Integer i = 0;

        Integer(const Integer&) = delete;

        friend Integer operator+(const Integer &a, const Integer &b);
        friend Integer operator-(const Integer &a, const Integer &b);
        friend Integer operator*(const Integer &a, const Integer &b);
        friend Integer operator/(const Integer &a, const Integer &b);

        friend Integer operator+(int a, const Integer &b);
        friend Integer operator-(int a, const Integer &b);
        friend Integer operator*(int a, const Integer &b);
        friend Integer operator/(int a, const Integer &b);

        friend Integer operator+(const Integer &a, int b);
        friend Integer operator-(const Integer &a, int b);
        friend Integer operator*(const Integer &a, int b);
        friend Integer operator/(const Integer &a, int b);
    };
}

namespace TestLib::Func {
    class Integer {
    private:
        int m_data;
    public:
        Integer() = default;

        Integer(int data);

        int getData() const;
    };

    Integer operator+(const Integer &a, const Integer &b);
    Integer operator-(const Integer &a, const Integer &b);
    Integer operator*(const Integer &a, const Integer &b);
    Integer operator/(const Integer &a, const Integer &b);

    Integer operator+(int a, const Integer &b);
    Integer operator-(int a, const Integer &b);
    Integer operator*(int a, const Integer &b);
    Integer operator/(int a, const Integer &b);

    Integer operator+(const Integer &a, int b);
    Integer operator-(const Integer &a, int b);
    Integer operator*(const Integer &a, int b);
    Integer operator/(const Integer &a, int b);
}

namespace TestLib::Method {
    class Integer {
    private:
        int m_data;
    public:
        Integer() = default;

        Integer(int data);

        Integer operator+(const Integer &b) const;
        Integer operator-(const Integer &b) const;
        Integer operator*(const Integer &b) const;
        Integer operator/(const Integer &b) const;

        Integer operator+(int a) const;
        // Integer operator+=(const Integer&);
        Integer operator-(int a) const;
        Integer operator*(int a) const;
        Integer operator/(int a) const;
    };
}

namespace TestLib {
    class Integer {
    private:
        int m_data;
    public:
        Integer() = default;
        Integer(int data);
        Integer(const Integer &another);

        // Бинарные
        friend Integer operator+(const Integer &lft, const Integer &rgh);
        friend Integer operator-(const Integer &lft, const Integer &rgh);
        friend Integer operator*(const Integer &lft, const Integer &rgh);
        friend Integer operator/(const Integer &lft, const Integer &rgh);

        friend Integer operator+(int lft, const Integer &rgh);
        friend Integer operator-(int lft, const Integer &rgh);
        friend Integer operator*(int lft, const Integer &rgh);
        friend Integer operator/(int lft, const Integer &rgh);

        friend Integer operator+(const Integer &lft, int rgh);
        friend Integer operator-(const Integer &lft, int rgh);
        friend Integer operator*(const Integer &lft, int rgh);
        friend Integer operator/(const Integer &lft, int rgh);

        // Унарные
        Integer operator-() const;
        Integer operator+() const;
        bool operator!() const;

        // Операторы сравнения
        friend bool operator==(const Integer &lft, const Integer &rgh);
        friend bool operator!=(const Integer &lft, const Integer &rgh);
        friend bool operator>(const Integer &lft, const Integer &rgh);
        friend bool operator<(const Integer &lft, const Integer &rgh);
        friend bool operator>=(const Integer &lft, const Integer &rgh);
        friend bool operator<=(const Integer &lft, const Integer &rgh);

        // Инкремент и декремент
        Integer& operator++(); // ++var; префикс
        Integer& operator--(); // --var; префикс
        Integer operator++(int); // var++; постфикс
        Integer operator--(int); // var--; постфикс

        // Преобразование типов
        operator int();
        operator double();

        // Ввод/вывод
        friend std::ostream& operator<<(std::ostream &out, const Integer &ogj);
        friend std::istream& operator>>(std::istream &in, Integer &ogj);

        // Копирование
        Integer& operator=(const Integer &another);
    };

    class Accumulator {
    private:
        int m_data;
    public:
        int operator()(int a);
    };

    class Array {
    private:
        int m_data[2];
    public:
        int& operator[](bool is_even);
        const int& operator[](bool is_even) const;
    };
}

#endif
