#include <testlib/logger.hpp>

setcolor::setcolor(
    ColorCodes color, ColorType colorType
) : m_color(color) {
    switch (colorType)
    {
    case ColorType::BACKGROUND:
        m_background = true;
        break;
    case ColorType::FOREGROUND:
        m_background = false;
        break;
    default:
        throw std::runtime_error("Unknown ColorType");
    }
}

std::ostream& operator<<(std::ostream &out, const setcolor &manip) {
    return out << "\033[1;" << (manip.m_background ? '4' : '3') << static_cast<int>(manip.m_color) << 'm';
}

std::ostream& resetcolor(std::ostream &out) {
    return out << "\033[0m";
}

int Log::Buffer::sync()
{
    if (m_log.m_msgType < m_log.m_loggerType) {
        str("");
        m_log.m_msgType = m_log.m_loggerType;
        return 0;
    }
    time_t ts = std::time(0);
    print_msg(m_log.m_out, ts);
    if (m_log.m_console) {
        switch (m_log.m_msgType)
        {
        case LoggerType::DEBUG:
        case LoggerType::INFO:
        case LoggerType::WARRNING:
            print_msg(std::cout, ts);
            break;
        case LoggerType::ERROR:
            print_msg(std::cerr, ts);
            break;
        }
    }

    str("");
    m_log.m_msgType = m_log.m_loggerType;
    return 0;
}

void Log::Buffer::print_msg(std::ostream &out, time_t ts) {
    auto it = m_log.loggerTypeNames.find(LoggerType::UNKNOWN);
    if (it == m_log.loggerTypeNames.end()) {
        std::cout << "There isn't key UNKNOWN" << std::endl;
    }
    out << "[" << std::localtime(&ts) << "][" << m_log.loggerTypeNames.at(m_log.m_msgType) << "] " << str();
}

bool Log::open(std::string const& file)
{
    m_file = file;
    m_out.open(file.c_str());
    return m_out.is_open();
}

std::ostream& operator<<(std::ostream& out, std::tm* dt)
{
    return out // ISO 8601 without timezone
        << std::setfill('0') << std::setw(4) << dt->tm_year + 1900 << "-"
        << std::setfill('0') << std::setw(2) << dt->tm_mday << "-"
        << std::setfill('0') << std::setw(2) << dt->tm_mon + 1 << " "
        << std::setfill('0') << std::setw(2) << dt->tm_hour << ":"
        << std::setfill('0') << std::setw(2) << dt->tm_min << ":"
        << std::setfill('0') << std::setw(2) << dt->tm_sec;
}
