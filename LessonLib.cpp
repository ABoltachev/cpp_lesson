#include "LessonLib.hpp"

namespace TestLib {
    Logger* initLogger(const std::string &file_path, bool is_binary) {
        std::ios::openmode mode = (is_binary) ? std::ios::out | std::ios::binary : std::ios::out;

        // Logger *logger = new Logger {std::ofstream(file_path, mode), is_binary};
        Logger *logger = new Logger;
        logger->is_binary = is_binary;
        logger->log_file.open(file_path, mode);
        // if (logger->log_file.is_open())
        if (!logger->log_file) {
            delete logger;
            logger = nullptr;
        }
        return logger;
    }

    void closeLogger(Logger **logger) {
        if ((*logger)->log_file) {
            (*logger)->log_file.close();
        }
        delete (*logger);
        (*logger) = nullptr;
    }

    void old_print(Logger &logger, uint32_t count, ...) {
        va_list list;

        va_start(list, count);

        for (int i = 0; i < count; i++) {
            logger.log_file << va_arg(list, int);
        }

        va_end(list);
    }
}
