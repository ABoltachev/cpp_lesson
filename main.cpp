#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>
#include "LessonLib.hpp"

// goodbit — всё хорошо. good()
// badbit — произошла какая-то фатальная ошибка. bad()
// eofbit — поток достиг конца файла. eof()
// failbit — произошла какая-то НЕ фатальная ошибка. fail()
// clear(state) - сбрасывает все текущие флаги состояния потока
//      и устанавливает флаг, переданный в качестве параметра (state)
// rdstate() — возвращает текущие установленные флаги
// setstate(state) — устанавливает флаг состояния, переданный в качестве параметра (state)


/*
isalnum(int) — возвращает ненулевое значение, если параметром является буква или цифра
isalpha(int) — возвращает ненулевое значение, если параметром является буква
iscntrl(int) — возвращает ненулевое значение, если параметром является управляющий символ
isdigit(int) — возвращает ненулевое значение, если параметром является цифра
isgraph(int) — возвращает ненулевое значение, если параметром является выводимый символ (но не пробел)
isprint(int) — возвращает ненулевое значение, если параметром является выводимый символ, включая пробел
ispunct(int) — возвращает ненулевое значение, если параметром не являются ни буква, ни цифра, ни пробел
isspace(int) — возвращает ненулевое значение, если параметром является пробел
isxdigit(int) — возвращает ненулевое значение, если параметром является шестнадцатеричная цифра
*/

int main () {
    TestLib::Logger *logger = TestLib::initLogger("test.log");

    auto print {
        [logger](auto arg) {
            static int coutner {0};
            TestLib::print(*logger, "Counter:", ++coutner, "arg:", arg);
        }
    };
    print(3.14);
    print("Hello, world!");

    std::vector<std::string> fruits {"apple", "banana", "orange", "lemon"};
    std::string substring;
    std::cout << "Введите подстроку: ";
    std::cin >> substring;
    if (auto it = std::find_if(
            fruits.begin(), fruits.end(), [substring](const std::string &str) {
                // substring = "test"; // нельзя, так как substring захватывается как const
                return str.find(substring) != std::string::npos;
            }
        ) ; it != fruits.end()
    ) {
        TestLib::print(*logger, "Found:", *it);
    } else {
        TestLib::print(*logger, "Not found");
    }

    uint32_t i {0};
    auto counter {
        [i, logger] () mutable { // [=]
            TestLib::print(*logger, "Counter:", ++i);
        }
    };

    auto another_counter {counter};

    counter();
    another_counter();
    TestLib::print(*logger, i);

    auto smart_counter {
        [&i, logger] () { // [&]
            TestLib::print(*logger, "Smart counter:", ++i);
        }
    };
    smart_counter();
    TestLib::print(*logger, i);

    auto smart_counter_v2 {
        [test(i + 1), logger] () mutable {
            TestLib::print(*logger, "Smart counter:", ++test);
        }
    };
    smart_counter_v2();

    TestLib::closeLogger(&logger);
    logger = TestLib::initLogger("test.log.bin", true);
    TestLib::print(*logger, 10);
    TestLib::print(*logger, 3.14);

    TestLib::closeLogger(&logger);

    // Валидация

    bool flag;

    do {
        flag = true;
        std::cout << "Введите любой текст без цифр: ";
        std::string text;
        std::getline(std::cin, text);

        for (size_t i = 0; i < text.length() && !flag; i++) {
            if (isalpha(text[i])) {
                continue;
            }

            if (text[i] == ' ') {
                continue;
            }

            flag = false;
        }
    } while(flag);

    do {
        flag = true;
        int number;

        std::cout << "Введите любое натуральное число: ";
        std::cin >> number;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<u_int32_t>::max(), '\n');
            continue;
        }

        if (number <= 0) {
            continue;
        }

        flag = false;
    } while(flag);

    return 0;
}
