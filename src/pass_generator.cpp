#include "pass_generator.h"
#include <iostream>
#include <string>
#include <stdlib.h>
#include <random>

RandomPassword::RandomPassword(const std::string& charts, int min, int max) 
    :   gen(std::random_device{}()),
        len_dist(min, max),
        char_dist(0, charts.size() - 1),
        sw_chars(charts),
        min_length(min),
        max_length(max)
    {
        srand(time(NULL));
        if (min < 0 || max < 0 || min > max)
            throw std::invalid_argument("Invalid password length.");
        if (min == 0 || max == 0)
            throw std::invalid_argument("Character set cannot be empty.");
    }

    std::string RandomPassword::operator()() {
        int len_pass = len_dist(gen);  // length distribution
        pass.reserve(len_pass);
    
        for (int j = 0; j < len_pass; ++j) {
            pass += sw_chars[char_dist(gen)];  // character distribution
        }
        return pass;
    }

    RandomPassword::operator std::string() const {
        return pass;
    }