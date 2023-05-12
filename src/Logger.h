//
// Created by sohaibalam on 12/05/23.
//

#ifndef GLEN_LOGGER_H
#define GLEN_LOGGER_H
#include <ctime>
#include <iostream>
#include <string>

namespace UTILITIES {
enum class LogLevel { INFO, WARNING, ERROR };

class SystemLogger {
public:
  static SystemLogger &getInstance() {
    static SystemLogger instance;
    return instance;
  }

  void log(LogLevel level, const std::string &message) {
    std::string levelStr;
    switch (level) {
    case LogLevel::INFO:
      levelStr = "INFO";
      break;
    case LogLevel::WARNING:
      levelStr = "WARNING";
      break;
    case LogLevel::ERROR:
      levelStr = "ERROR";
      break;
    }

    std::time_t now = std::time(nullptr);
    std::tm *timeInfo = std::localtime(&now);
    char buffer[80];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeInfo);

    std::cout << "[" << buffer << "] " << levelStr << ": " << message
              << std::endl;
  }

private:
  SystemLogger() {}
};

// Static instance of SystemLogger
static SystemLogger &logger = SystemLogger::getInstance();

} // namespace UTILITIES
#endif
