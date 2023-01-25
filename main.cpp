#include <iostream>
#include <deque>
#include <map>
#include <string>
#include <stack>

/*
Последовательные
Есть operator[] для const
    * std::vector
    * std::array
    * std::list нет произвольного доступа
    * std::forward_list нет произвольного доступа
    * std::deque
    * std::basic_string

Ассоциативные
Нет operator[] для const
    * std::set нет operator[]
    * std::map
    * std::multiset нет operator[]
    * std::multimap

Адаптеры
    * std::stack
    * std::queue нет top
    * std::priority_queue

*/

int main() {
    std::deque<int> deq {10, 15}; // кол-во элементов
    const std::deque<int> deq_2 {deq}; // копирование
    std::deque<int> {1, 2, 3}; // std::initialized_list

    deq[2];

    deq.front(); // элемент из начала
    deq.back(); // элемент из конца

    deq.empty(); // пустой = True
    deq.size();
    deq.resize(15, 1);

    deq.clear();
    deq.insert(deq.begin() + 3, 15);
    deq.erase(deq.begin() + 3);
    deq.push_back(15);
    deq.pop_back(); // Просто удаляет элемент из конца
    deq.emplace_back(15);
    deq.emplace();


    std::map<std::string, int> dict {
        std::make_pair("Test", 1),
        std::make_pair("Test_2", 2),
    };
    std::map<std::string, int> dict_2 {dict};

    dict.empty(); // пустой = True
    dict.size();

    dict.clear();
    dict.insert(std::make_pair("Test_3", 15));
    dict.emplace(std::make_pair("Test_4", 25));
    dict.erase("Test_4");

    dict.count('Test_2');
    auto it = dict.find("Test");
    it = dict.lower_bound("Test_2");
    it = dict.upper_bound("Test");

    std::stack<int, std::deque<int>> stack;

    stack.top();
    stack.empty();
    stack.size();

    stack.push(15);
    stack.pop();

    return 0;
}
