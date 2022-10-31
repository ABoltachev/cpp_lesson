#ifndef TESTLIB_H
#define TESTLIB_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdarg>

namespace TestLib {
    struct Logger {
        std::ofstream log_file;
        bool is_binary;
    };

    Logger* initLogger(const std::string &file_path, bool is_binary=false);

    void closeLogger(Logger **logger);

    template<typename... Args>
    void getStr(std::stringstream &str_stream, Args... args);

    template<typename Head, typename... Tail>
    void getStr(
        std::stringstream &str_stream, const Head &head, Tail... tail
    ) {
        str_stream << head << ' ';
        print(tail...);
    }

    template<typename Head>
    void getStr(std::stringstream &str_stream, const Head &head) {
        str_stream << head;
        std::cout << str_stream.str();
    }

    void old_print(Logger &logger, uint32_t count, ...);

    template<typename... Args>
    void print(Logger &logger, Args... args);

    template<typename Head, typename... Tail>
    void print(Logger &logger, const Head &head, Tail... tail) {
        std::cout << head << ' ';
        if (logger.log_file) {
            if (logger.is_binary) {
                uint32_t head_size = sizeof(head);
                logger.log_file.write(
                    reinterpret_cast<char*>(&head_size), sizeof(uint32_t)
                );
                logger.log_file.write(
                    reinterpret_cast<const char*>(&head), head_size
                );
            } else {
                logger.log_file << head << ' ';
            }
        }
        print(logger, tail...);
    }

    template<typename Head>
    void print(Logger &logger, const Head &head) {
        std::cout << head;
        if (logger.log_file) {
            if (logger.is_binary) {
                uint32_t head_size = sizeof(head);
                logger.log_file.write(
                    reinterpret_cast<char*>(&head_size), sizeof(uint32_t)
                );
                logger.log_file.write(
                    reinterpret_cast<const char*>(&head), head_size
                );
            } else {
                logger.log_file << head;
            }
        }
        print(logger);
    }

    template<>
    void print(Logger &logger) {
        std::cout << std::endl;
        if (logger.log_file) {
            if (!logger.is_binary) {
                logger.log_file << "\n";
            }
            flush(logger.log_file);
        }
    }

    void readLogFile(/*TODO тут должна быть строка*/);
}

#endif
