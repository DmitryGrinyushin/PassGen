#include <iostream>
#include "pass_generator.h"

int main()
{
    int min = 1, max = 1, type = 0;

    std::cout << "Укажите тип пароля (0 - только цифры / 1 - все символы)" << std::endl;
    std::cin >> type;
    std::string data;
    type == 0 ? data = "0123456789" : data = "QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm0123456789!@#$%&*";
    
    std::cout << "Введите минимальную / максимальную длину пароля" << std::endl;
    std::cin >> min >> max;
    
    try {
        RandomPassword rnd(data, min, max);
        std::string psw = rnd();
        std::cout << "Результат выполнения: " << std::endl;
        std::cout << psw << std::endl;
    }
    catch (const std::exception& e) {
    std::cerr << "Ошибка: " << e.what() << std::endl;
    }

    return 0;
}