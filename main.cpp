#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <algorithm>

/*
    Итераторы имеют следующие операторы:
        operator*
        operator++ и operator--
        operator== и operator!=
        operator=
    Контейнеры имеют следующие методы для работы с operator=
        begin() итератор на первый элемент
        end() итератор на элемент, следующий за последним
        cbegin() и cend() константные версии
        rbegin() и rend() реверсивные версии

    Операции можно проводить только с итераторами на одинаковые контейнеры и типы
*/

#include <testlib/tuple.hpp>

template <typename T>
const T& max(const T &a, const T &b) {
    return (a > b) ? a : b;
}

int testFunc(int a, double b) {
    return max<double>(a, b);
}

int main() {
    Tuple<int, float, std::string> tuple(1, 3.14, "Hello, world!");
    std::cout << get<0>(tuple) << ' ' << get<1>(tuple) << ' ' << get<2>(tuple) << std::endl;
    // std::cout << get<3>(tuple); // Здесь будет ошибка компиляции

    // Tuple<int, int> tuple2(1, 3);
    std::tuple<int, double> tuple2(1, 3);
    std::cout << call(testFunc, tuple2) << std::endl;

    std::vector<int> vect = {2, 3, 1};
    // std::vector<int>::iterator it
    std::vector<int>::const_iterator it = vect.begin() + 2;
    for (int item : vect) {
        std::cout << item << ' ';
    }
    std::cout << std::endl;

    for (;it != vect.end(); it++) {
        std::cout << *it << ' ';
    }
    std::cout << std::endl;

    std::set<int> set = {4, 5, 6};
    std::set<int>::const_iterator it_1 = set.begin();
    // std::advance(it_1, 2);
    it_1++;
    it_1++;
    for (int item : set) {
        std::cout << item << ' ';
    }
    std::cout << std::endl;

    std::map<int, std::string> map = {
        std::make_pair(1, "Test_1"),
        std::make_pair(2, "Test_2"),
        std::make_pair(3, "Test_3"),
    };
    for (auto item : map) {
        std::cout << item.first << ' ' << item.second << std::endl;
    }

    if (auto it = std::find(vect.begin(), vect.end(), 1); it != vect.end()) {
        std::cout << "Result: " << *it << std::endl;
    }
    if (std::find(vect.begin(), vect.end(), 4) == vect.end()) {
        std::cout << "There isn't 4" << std::endl;
    }
    std::sort(vect.begin(), vect.end());
    for (int item : vect) {
        std::cout << item << ' ';
    }
    std::cout << std::endl;
    std::sort(vect.begin(), vect.end(), [] (int a, int b) {return a > b;});
    for (int item : vect) {
        std::cout << item << ' ';
    }
    std::cout << std::endl;

    return 0;
}
