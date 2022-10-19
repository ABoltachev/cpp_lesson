#ifndef LESSONLIB_H
#define LESSONLIB_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

namespace Lesson {
    struct Logger
    {
        std::fstream m_stream;
        std::ios::openmode m_mode = std::ios::out;
    } g_out;

    void configOut(
        const std::string &file_path="",
        const std::ios::openmode &mode=std::ios::out
    );

    template<class... Args>
    void print(const Logger &log, Args... args);

    template<class Head, class... Tail>
    void print(const Logger &log, Head head, Tail... tail) {
        if (g_out.m_stream.is_open()) {
            if (g_out.m_mode == std::ios::binary) {
                size_t head_size {sizeof(head)};
                g_out.m_stream
                    .write(reinterpret_cast<char*>(&head_size), sizeof(uint32_t))
                    .write(reinterpret_cast<char*>(&head), head_size);
            } else {
                g_out.m_stream << head << ' ';
            }
        } else {
            std::cout << head << ' ';
        }
        print(log, tail...);
    }

    template<>
    void print(const Logger &log) {
        static char end = '\n';
        static uint32_t end_size {1};
        if (g_out.m_stream.is_open()) {
            if (g_out.m_mode == std::ios::binary) {
                g_out.m_stream
                    .write(reinterpret_cast<char*>(&end_size), sizeof(uint32_t))
                    .write(&end, 1);
            } else {
                g_out.m_stream << end;
            }
            g_out.m_stream.flush();
        } else {
            std::cout << end;
            std::cout.flush();
        }
    }
}

#endif // LESSONLIB_H
