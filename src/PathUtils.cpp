#include "PathUtils.h"

#ifdef __APPLE__
#include <mach-o/dyld.h>
#elif defined(__linux__)
#include <unistd.h>
#endif

#include <vector>
#include <stdexcept>

std::filesystem::path getExecutablePath() {
    std::vector<char> buffer(1024);

#ifdef __APPLE__
    uint32_t size = buffer.size();
    if (_NSGetExecutablePath(buffer.data(), &size) != 0) {
        buffer.resize(size);
        if (_NSGetExecutablePath(buffer.data(), &size) != 0) {
            throw std::runtime_error("Failed to get executable path (macOS)");
        }
    }
#elif defined(__linux__)
    ssize_t count = readlink("/proc/self/exe", buffer.data(), buffer.size());
    if (count == -1) {
        throw std::runtime_error("Failed to get executable path (Linux)");
    }
    buffer[count] = '\0';
#else
    throw std::runtime_error("Unsupported platform");
#endif

    return std::filesystem::canonical(buffer.data());
}