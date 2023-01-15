#include <testlib/logger.hpp>

#include <iostream>

int main() {
    std::cout << setcolor(ColorCodes::RED, ColorType::BACKGROUND) << "Test" << resetcolor << std::endl;
    std::cout << "Test 1" << std::endl;
    Log log("test.log");
    log.setLoggerType(LoggerType::WARRNING);
    log << "Test" << std::endl;
    log << LoggerType::DEBUG << "Test 1" << std::endl;
    log << LoggerType::INFO << "Test 2" << std::endl;
    log << LoggerType::WARRNING << "Test 3" << std::endl;
    log << LoggerType::ERROR << "Test 4" << std::endl;
    return 0;
}
