#pragma once

#include <iostream>
#include <string>
#include <random>

class RandomPassword {
    std::string sw_chars;
    int min_length;
    int max_length;
    std::string pass;
    std::mt19937 gen;
    std::uniform_int_distribution<int> len_dist;
    std::uniform_int_distribution<size_t> char_dist;

public:
    RandomPassword (const std::string& charts, int min, int max);
    
    std::string operator()();
    operator std::string() const;
};