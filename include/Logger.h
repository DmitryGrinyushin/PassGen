#pragma once

#include <string>

class Logger {
public:
    static void log(const std::string& message, const std::string& level = "INFO");

};