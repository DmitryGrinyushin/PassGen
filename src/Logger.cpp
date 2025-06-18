#include "Logger.h"
#include "PathUtils.h"
#include <fstream>
#include <ctime>
#include <iomanip>
#include <sstream>

std::string getCurrentTime() {
    std::time_t now = std::time(nullptr);
    std::tm* localTime = std::localtime(&now);
    std::ostringstream oss;
    oss << std::put_time(localTime, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

void Logger::log(const std::string& message, const std::string& level) {
    std::filesystem::path exePath = getExecutablePath();
    std::ofstream logFile(exePath.parent_path() / "log.txt", std::ios::app);
    logFile << "[" << getCurrentTime() << "] [" << level << "] " << message << std::endl;
}