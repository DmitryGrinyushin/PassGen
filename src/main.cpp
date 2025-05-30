#include <iostream>
#include "pass_generator.h"
#include <cstring> // для strcmp

void show_help() {
    std::cout << "Использование:\n"
              << "  passgen [опции]\n\n"
              << "Опции:\n"
              << "  -d, --digits    Только цифры (0-9)\n"
              << "  -a, --all       Все символы (A-Z, a-z, 0-9, !@#$%&*)\n"
              << "  -m, --min N     Минимальная длина пароля\n"
              << "  -x, --max N     Максимальная длина пароля\n"
              << "  -h, --help      Справка\n\n"
              << "Примеры:\n"
              << "  passgen -d -m 8 -x 12  # Пароль из цифр длиной 8-12\n"
              << "  passgen -a -m 10 -x 10 # Пароль из всех символов длиной ровно 10\n";
}

int main(int argc, char* argv[]) {
    // Параметры по умолчанию
    std::string chars = "QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm0123456789!@#$%&*";
    int min_len = 8;
    int max_len = 12;

    // Парсинг аргументов
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
        std::cout << "Сгенерированный пароль: " << std::endl;
        std::cout << password << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}