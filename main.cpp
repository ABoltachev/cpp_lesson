#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <shared_mutex>
#include <memory>
#include <condition_variable>
#include <future>
#include <vector>

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
    while (!g_t_mutex.try_lock_for(std::chrono::seconds(10))) {
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

struct Resources {
    int x;
};

std::shared_ptr<Resources> g_ptr;

void initResources(const std::string &name) {
    if (!g_ptr) {
        g_ptr.reset(new Resources);
    }
}

std::once_flag g_resources_flag;

void test_init() {
    // 1
    // std::unique_lock<std::mutex> lg(g_mutex);
    // initResources();
    // lg.unlock();

    // 2
    // if (!g_ptr) {
    //     std::unique_lock<std::mutex> lg(g_mutex);
    //     initResources();
    // }

    // 3
    std::call_once(g_resources_flag, initResources, "Test"); // Аргументы не копируются используется std::forward

    // 4
    static std::shared_ptr<Resources> s_ptr(new Resources); // До 11 стандарта будет состояние гонки
}

/*
    Notifier
        1) Блокируем std::mutex (m1)
        2) Выполняем модификацию общего флага. После снимается блокировка
        3) notify_one notify_all
    Waiter
        1) С помощью std::unique_lock блокируем m1
        2) Вызываем метод wait, wait_for или wait_until
*/

std::condition_variable g_cv;
bool g_ready = false;

void worker() {
    std::unique_lock<std::mutex> lg(g_mutex);
    g_ready = true;
    g_cv.notify_one();
    std::notify_all_at_thread_exit(g_cv, std::move(lg));
}

void waiter() {
    // bool is_done = false;
    // while (!is_done) {
    //     std::this_thread::sleep_for(std::chrono::seconds(10));
    // }

    std::unique_lock<std::mutex> lg(g_mutex);
    g_cv.wait(lg, []{ return g_ready; });
    // smth work
    lg.unlock();
}

/*
    С помощью std::promise возвращаем значение или эксепшен
    std::furure для получения значения
*/

void test_promise(std::vector<int> arr, std::promise<int> acc_promise) {
    int sum = 0;
    for (int item : arr) {
        sum += item;
    }
    acc_promise.set_value(sum);
}

std::vector<float> t_div(const std::vector<int> &arr, int den) {
    if (den == 0) {
        throw std::out_of_range("x==0"); // Бросаем исключение
    }
    std::vector<float> res;
    for (int item : arr) {
        res.push_back(item / den);
    }
    return res;
}

void test_div(std::vector<int> arr, int den, std::promise<std::vector<float>> div_promise) {
    if (den == 0) {
        div_promise.set_exception(std::make_exception_ptr(std::out_of_range("den==0")));
        return;
    }
    try {
        div_promise.set_value(t_div(arr, den));
    }
    catch (...) {
        div_promise.set_exception(std::current_exception());
    }
}

int main()
{
    // race_condition();
    // atomic();
    // mutex();
    // dead_lock();

    // {
    //     char buf[256] = "Hello, world!";

    //     // std::thread t(func, 15, buf);
    //     std::string str {buf};
    //     std::thread t(func, 15, std::ref(str));
    //     std::cout << t.get_id() << std::endl;
    //     t.detach();
    // }
    dead_lock_solved();

    std::vector<int> arr = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::promise<int> acc_promise;
    std::future<int> acc_future = acc_promise.get_future();
    std::thread t1(test_promise, arr, std::move(acc_promise));

    std::cout << "Result acc: " << acc_future.get() << std::endl;

    t1.join();

    std::vector<int> arr_2 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::promise<std::vector<float>> div_promise;
    std::future<std::vector<float>> div_future = div_promise.get_future();
    // div_future.valid(); // false если не привязан к promise
    std::thread t2(test_div, arr_2, 0, std::move(div_promise));
    // div_future.get();
    t2.detach();
    std::vector<float> res;
    try {
        res = div_future.get();
    }
    catch (const std::out_of_range &ex) {
        std::cerr << "Exception: " << ex.what() << std::endl;
    }

    std::future<std::vector<float>> div_furure_2 = std::async(std::launch::async, t_div, arr_2, 2);
    // std::future<std::vector<float>> div_furure_2 = std::async(std::launch::deferred, t_div, arr_2, 2); // Не создает отдельный поток
    // std::future<std::vector<float>> div_furure_2 = std::async(t_div, arr_2, 2); // равносильно std::launch::async | std::launch::deferred
    div_furure_2.wait();
    try {
        res = div_furure_2.get();
        std::cout << "get2" << std::endl;
    }
    catch (const std::out_of_range &ex) {
        std::cerr << "Exception: " << ex.what() << std::endl;
    }

    return 0;
}
