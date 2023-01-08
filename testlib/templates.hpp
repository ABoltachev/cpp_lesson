#ifndef TEMPLATES_H
#define TEMPLATES_H

#include <iostream>
#include <string>
#include <stdexcept>

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
    class TESTLIB_API ValueError : public std::runtime_error {
    public:
        ValueError(const char *msg) : std::runtime_error(msg) {}
    };

    class Object {
    protected:
        std::string *m_name = nullptr;
    public:
        Object(const char *name = "") {
            // throw ValueError("Test");
            m_name = new std::string(name); // can throw std::bag_alloc
        }

        virtual ~Object() = default;
    };

    class TESTLIB_API Functor : public Object {
    protected:
        double (*m_func)(double, double) = nullptr;
    public:
        Functor(double (*func)(double, double)) try : m_func(func) {}
        catch (...) {
            std::cerr << "Construction of Functor failed" << std::endl;
        }

        double operator()(double a, double b) {
            try {
                return m_func(a, b);
            }
            catch(const ValueError &ex) {
                std::cerr << "An error occurred while executing func: " << ex.what() << std::endl;
                // throw ex;
                throw;
            }
            return 0;
        }
    };

    template<typename T>
    const TESTLIB_API T& max(const T &a, const T &b) {
        return (a > b) ? a : b;
    }

    template<>
    const TESTLIB_API char &max(const char &a, const char &b) {
        return (a < b) ? a : b;
    }


    template <class T>
    class TESTLIB_API Array {
    private:
        int m_length = 0;
        T *m_data = nullptr;
    public:
        Array() = default;
        Array(int length) {
            m_data = new T[length];
            m_length = length;
        }

        ~Array() {
            delete[] m_data;
        }
    
        void clear() {
            delete[] m_data;
            m_data = nullptr;
            m_length = 0;
        }

        T& operator[](int index);

        const T& operator[](int index) const;

        int getLength() const;
    };

    template <class T, size_t size>
    class TESTLIB_API StaticArray {
    private:
        T m_data[size];
    public:
        StaticArray() = default;

        T& operator[](size_t index);

        const T& operator[](size_t index) const;

        int getLength() const;
    };

    template <size_t size>
    class TESTLIB_API StaticArray<char, size> {
    private:
        char m_data[size];
    public:
        StaticArray() = default;

        int operator[](size_t index);

        const int operator[](size_t index) const;

        int getLength() const;
    };

    template<typename T, size_t size>
    void print(const StaticArray<T, size> &arr) {
        std::cout << "StaticArray:";
        for (size_t i = 0; i < size; ++i) {
            int a = arr[i];
            std::cout << ' ' << a;
        }
        std::cout << std::endl;
    }

    template<size_t size>
    void print(const StaticArray<double, size> &arr) {
        std::cout << "StaticArray<double>:";
        for (size_t i = 0; i < size; ++i) {
            std::cout << ' ' << std::scientific << arr[i];
        }
        std::cout << std::endl;
    }
}

#include "templates.tpp"

#endif // TEMPLATES_H
