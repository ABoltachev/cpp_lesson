#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <stdexcept>
#include <ctime>
#include <map>

enum class ColorCodes {
    BLACK,
    RED,
    GREEN,
    YELLOW,
    BLUE,
    MAGENTA,
    CYAN,
    WHITE,
};

enum class ColorType {
    FOREGROUND,
    BACKGROUND,
};

class setcolor {
private:
    ColorCodes m_color = ColorCodes::WHITE;
    bool m_background = false;
public:
    setcolor(ColorCodes color, ColorType colorType=ColorType::FOREGROUND);

    friend std::ostream& operator<<(std::ostream &out, const setcolor &manip);
};

std::ostream& resetcolor(std::ostream &out);

enum class LoggerType {
    DEBUG,
    INFO,
    WARRNING,
    ERROR,
    UNKNOWN,
};

class Log : public std::ostream {
public:
    Log()
        : std::ostream(&m_buffer)
        , m_buffer(*this)
        , m_console(true)
    {}

    Log(std::string const& file, bool console = true)
        : std::ostream(&m_buffer)
        , m_buffer(*this)
        , m_file(file)
        , m_out(file.c_str())
        , m_console(console)
    {}

    bool open(std::string const& file);
    void close() { m_out.close(); }
    bool isOpen() const { return m_out.is_open(); }

    std::string const& file() const { return m_file; }
    bool console() const { return m_console; }
    void console(bool c) { m_console = c; }
    void setMsgType(LoggerType type) { m_msgType = type; }
    void setLoggerType(LoggerType type) { m_loggerType = type; m_msgType = type; }

    std::ostream& operator<<(LoggerType type) {
        m_msgType = type;
        return *this;
    }

private:
    class Buffer : public std::stringbuf {
    public:
        Buffer(Log& log)
            : m_log(log)
        {}

        int sync();

        void print_msg(std::ostream &out, time_t ts);

    private:
        Log& m_log;
    };
    friend class Buffer;

    Buffer m_buffer;
    std::string m_file;
    std::ofstream m_out;
    bool m_console;
    LoggerType m_loggerType = LoggerType::INFO;
    LoggerType m_msgType = LoggerType::INFO;

    const std::map<LoggerType, std::string> loggerTypeNames = {
        std::make_pair(LoggerType::DEBUG, "DEBUG"),
        std::make_pair(LoggerType::INFO, "INFO"),
        std::make_pair(LoggerType::WARRNING, "WARRNING"),
        std::make_pair(LoggerType::ERROR, "ERROR"),
    };
};

std::ostream& operator<<(std::ostream& out, std::tm* dt);

#endif // LOGGER_H
