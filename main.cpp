#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>

#include "testlib/test_lib.hpp"

void func(int a, std::string &str) {
    std::cout << "Test" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << str << std::endl;
}

std::timed_mutex g_t_mutex;

void time_mutex() {
    while (!g_t_mutex.try_lock_for(std::chrono::seconds(1))) {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    g_t_mutex.unlock();
    // std::chrono::time_point
    // std::chrono::system_clock // зависит от системного времени
    while (!g_t_mutex.try_lock_for(std::chrono::steady_clock::now() + std::chrono::seconds(10))) {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    g_t_mutex.unlock();
}

std::recursive_mutex g_r_mutex;

void recursive_func(int n) {
    if (n <= 0) {
        return;
    }
    g_r_mutex.lock();
    recursive_func(n - 1);
    g_r_mutex.unlock();
}

// std::recursive_timed_mutex

std::shared_mutex g_s_mutex;

void shared_func() {
    g_s_mutex.lock(); // эксклюзивное владение
    // smth code
    g_s_mutex.unlock();
    g_s_mutex.lock_shared(); // общее владение (несколько потоков могут блокировать одновременно)
    // smth code
    g_s_mutex.unlock();
}

// std::shared_timed_mutex

std::mutex g_mutex;

void lock_guard() {
    {
        std::lock_guard<std::mutex> lg(g_mutex); // g_mutex блокируется при создании lg и освобождается при его уничтожении
    }

    {
        g_mutex.lock(); // g_mutex блокируется
        std::lock_guard<std::mutex> lg(g_mutex, std::adopt_lock); // при создании lg мютекс запоминается им и освобождается при его уничтожении
    }
}

void unique_lock() {
    std::unique_lock ul(g_mutex, std::defer_lock);
    ul.owns_lock(); // true если ul владеет мютексом
}

int main()
{
    // race_condition();
    // atomic();
    // mutex();
    // dead_lock();

    {
        char buf[256] = "Hello, world!";

        // std::thread t(func, 15, buf);
        std::string str {buf};
        std::thread t(func, 15, std::ref(str));
        std::cout << t.get_id() << std::endl;
        t.detach();
    }
    dead_lock_solved();

    return 0;
}
