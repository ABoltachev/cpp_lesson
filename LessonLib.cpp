#include "LessonLib.hpp"

// std::ios::in
// std::ios::out
// std::ios::ate
// std::ios::binary

namespace Lesson {
    void configOut(const std::string &file_path, const std::ios::openmode &mode) {
        if (g_out.m_stream.is_open()) {
            g_out.m_stream.close();
        }
        if (!file_path.empty()) {
            g_out.m_stream.open(file_path, mode);
            g_out.m_mode = mode;
            char test = '1';
            if (mode != std::ios::out | std::ios::binary) {
                g_out.m_stream.write(&test, 1);
            }
        }
    }
}
