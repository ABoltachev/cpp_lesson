#include "test_lib.hpp"

void race_condition() {
    unsigned long long g_count = 0;

    std::thread t1([&]()
    {
        for(auto i = 0; i < 1'000'000; ++i)
            ++g_count;
    });

    std::thread t2([&]()
    {
        for(auto i = 0; i < 1'000'000; ++i)
            ++g_count;
    });

    t1.join();
    t2.join();
    // t2.detach(); // отсоединение потока
    // t2.joinable(); // возвращает true, если можно вызвать join или detach
    
    std::cout << g_count;

    std::cout << std::endl;
}

void atomic() {
    std::atomic<unsigned long long> g_count { 0 };

    std::thread t1([&]()
    {
        for(auto i = 0; i < 1'000'000; ++i)
            g_count.fetch_add(1);
    });
    
    std::thread t2([&]()
    {
        for(auto i = 0; i < 1'000'000; ++i)
            g_count.fetch_add(1);
            // g_count += 1;
            // ++g_count;
    });
    
    t1.join();
    t2.join();
    
    std::cout << g_count;

    std::cout << std::endl;
}

void mutex() {
    unsigned long long g_count = 0;
    std::mutex g_count_mutex;

    std::thread t1([&]()
    {
        for(auto i = 0; i < 1'000'000; ++i) {
            g_count_mutex.lock();
            // g_count_mutex.try_lock(); // возвращает bool возвращает false, когда мютекс недоступен (может ложно возвращать false)
            g_count += 1;
            g_count_mutex.unlock();
        }
    });
    
    std::thread t2([&]()
    {
        for(auto i = 0; i < 1'000'000; ++i) {
            g_count_mutex.lock();
            g_count += 1;
            g_count_mutex.unlock();
        }
    });
    
    t1.join();
    t2.join();
    
    std::cout << g_count;

    std::cout << std::endl;
}

void dead_lock() {
    std::mutex m1;
    std::mutex m2;

    auto f1 = [&m1, &m2]() {
        std::lock_guard<std::mutex> lg1(m1);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        std::lock_guard<std::mutex> lg2(m2);
    };

    auto f2 = [&m1, &m2]() {
        std::lock_guard<std::mutex> lg1(m2);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        std::lock_guard<std::mutex> lg2(m1);
    };

    std::thread thread1([&f1, &f2]() {
        f1();
    });

    std::thread thread2([&f1, &f2]() {
        f2();
    });

    thread1.join();
    thread2.join();
}

void dead_lock_solved() {
    std::mutex m1;
    std::mutex m2;

    auto f1 = [&m1, &m2]() {
        std::scoped_lock lg(m2, m1);

        // std::lock(m1, m2);
        // std::lock_guard<std::mutex> lg1(m1, std::adopt_lock);
        // std::lock_guard<std::mutex> lg2(m2, std::adopt_lock);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    };

    auto f2 = [&m1, &m2]() {
        std::scoped_lock lg(m1, m2);
        // std::lock(m1, m2);
        // std::lock_guard<std::mutex> lg1(m1, std::adopt_lock);
        // std::lock_guard<std::mutex> lg2(m2, std::adopt_lock);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    };

    std::thread thread1([&f1, &f2]() {
        f1();
    });

    std::thread thread2([&f1, &f2]() {
        f2();
    });

    thread1.join();
    thread2.join();
}
