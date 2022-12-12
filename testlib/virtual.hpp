#ifndef VIRTUAL_H
#define VIRTUAL_H

#include <iostream>
#include <string>

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
    class Exception : public std::exception {
        
    };
    #pragma region first
    class PoweredDevice {
    public:
        PoweredDevice(int power) {
            std::cout << "PoweredDevice: " << power << '\n';
        }
    };
    
    class Scanner: virtual public PoweredDevice {
    public:
        Scanner(int scanner, int power)
            : PoweredDevice(power) {
            std::cout << "Scanner: " << scanner << '\n';
        }
    };
    
    class Printer: virtual public PoweredDevice {
    public:
        Printer(int printer, int power)
            : PoweredDevice(power) {
            std::cout << "Printer: " << printer << '\n';
        }
    };
    
    class Copier: public Scanner, public Printer {
    public:
        Copier(int scanner, int printer, int power)
            : Scanner(scanner, power), Printer(printer, power), PoweredDevice(power) {}
    };
    #pragma endregion first

    #pragma region second
    class Parent {
    public:
        Parent() {}
    
        // Перегрузка оператора вывода <<
        friend std::ostream& operator<<(std::ostream &out, const Parent &p) {
            // Делегируем выполнение операции вывода методу print()
            return p.print(out);
        }
    
        // Делаем метод print() виртуальным
        virtual std::ostream& print(std::ostream& out) const {
            out << "Parent";
            return out;
        }
    };
    
    class Child: public Parent {
    public:
        Child() {}
    
        // Переопределение метода print() для работы с объектами класса Child
        virtual std::ostream& print(std::ostream& out) const override {
            out << "Child";
            return out;
        }
    };
    #pragma endregion second
}

#endif // VIRTUAL_H
