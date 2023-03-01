#ifndef TESTLIB_HPP
#define TESTLIB_HPP

#include <iostream>
#include <thread>
#include <atomic>
#include <mutex>
#include <chrono>

void race_condition();

void atomic();

void mutex();

void dead_lock();

void dead_lock_solved();

#endif // TESTLIB_HPP
