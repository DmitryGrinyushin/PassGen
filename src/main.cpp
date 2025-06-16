#include <iostream>
#include "pass_generator.h"
#include "Logger.h"
#include <cstring> // strcmp

void show_help() {
    std::cout << "Usage:\n"
              << "  passgen [options]\n\n"
              << "Options:\n"
              << "  -d, --digits    Digits only (0-9)\n"
              << "  -a, --all       All characters (A-Z, a-z, 0-9, !@#$%&*)\n"
              << "  -m, --min N     Minimum password length\n"
              << "  -x, --max N     Maximum password length\n"
              << "  -h, --help      Help\n\n"
              << "Examples:\n"
              << "  passgen -d -m 8 -x 12  # Password with digits only, length 8–12\n"
              << "  passgen -a -m 10 -x 10 # Password with all characters, length 10\n";
}

int main(int argc, char* argv[]) {

    // set defaults
    std::string chars = "QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm0123456789!@#$%&*";
    int min_len = 8;
    int max_len = 12;

    // parse command-line arguments
    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "-d") == 0 || strcmp(argv[i], "--digits") == 0) {
            chars = "0123456789";
        }
        else if (strcmp(argv[i], "-a") == 0 || strcmp(argv[i], "--all") == 0) {
            chars = "QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm0123456789!@#$%&*";
        }
        else if (strcmp(argv[i], "-m") == 0 || strcmp(argv[i], "--min") == 0) {
            if (i + 1 < argc) min_len = std::atoi(argv[++i]);
        }
        else if (strcmp(argv[i], "-x") == 0 || strcmp(argv[i], "--max") == 0) {
            if (i + 1 < argc) max_len = std::atoi(argv[++i]);
        }
        else if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            show_help();
            return 0;
        }
    }

    try {
        RandomPassword rnd(chars, min_len, max_len);
        
        std::string password = rnd();
        std::cout << std::endl;
        std::cout << "Generated password: " << std::endl;
        std::cout << password << std::endl;

        Logger::log("Password generated successfully");
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        
        Logger::log(e.what(), "ERROR");
        return 1;
    }

    return 0;
}