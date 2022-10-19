#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include "LessonLib.hpp"

int main () {
    Lesson::configOut("test.log", std::ios::out);

    auto print {
        [](auto arg) {
            static int coutner {0};
            Lesson::print(Lesson::g_out, "Counter:", ++coutner, "arg:", arg);
        }
    };
    print(3.14);
    print("Hello, world!");

    std::vector<std::string> fruits {"apple", "banana", "orange", "lemon"};
    std::string substring;
    std::cin >> substring;
    if (auto it = std::find_if(
            fruits.begin(), fruits.end(), [substring](const std::string &str) {
                // substring = "test"; // нельзя, так как substring захватывается как const
                return str.find(substring) != std::string::npos;
            }
        ) ; it != fruits.end()
    ) {
        Lesson::print(Lesson::g_out, "Found:", *it);
    } else {
        Lesson::print(Lesson::g_out, "Not found");
    }

    uint32_t i {0};
    auto counter {
        [i] () mutable { // [=]
            Lesson::print(Lesson::g_out, "Counter:", ++i);
        }
    };

    auto another_counter {counter};

    counter();
    another_counter();
    Lesson::print(Lesson::g_out, i);

    auto smart_counter {
        [&i] () { // [&]
            Lesson::print(Lesson::g_out, "Smart counter:", ++i);
        }
    };
    smart_counter();
    Lesson::print(Lesson::g_out, i);

    auto smart_counter_v2 {
        [test(i + 1)] () mutable {
            Lesson::print(Lesson::g_out, "Smart counter:", ++test);
        }
    };
    smart_counter_v2();

    Lesson::configOut("test.log.bin", std::ios::out | std::ios::binary);
    Lesson::print(Lesson::g_out, 10);
    Lesson::print(Lesson::g_out, 3.14);

    Lesson::configOut();

    std::ifstream in_file("test.log.bin", std::ios::binary);

    while (in_file) {
        uint32_t
    }

    return 0;
}
