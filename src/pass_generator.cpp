#include "pass_generator.h"
#include <iostream>
#include <string>
#include <stdlib.h>

RandomPassword::RandomPassword(const std::string& charts, int min, int max) 
    : sw_chars(charts), min_length(min), max_length(max) {
        if (min < 0 || max < 0 || min > max)
            throw std::invalid_argument("Неверная длина пароля.");
        if (min == 0 || max == 0)
            throw std::invalid_argument("Набор символов не может быть пустым.");
    }

    std::string RandomPassword::operator()() {
        srand(time(NULL));
        int len_pass = rand() % (max_length - min_length + 1) + min_length;
        pass.resize(len_pass);
        for (int j = 0; j < len_pass; ++j) {
            pass[j] = sw_chars[rand() % (sw_chars.length())];
        }
        return pass;
    }

    RandomPassword::operator std::string() const {
        return pass;
    }