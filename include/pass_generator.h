#pragma once

#include <iostream>
#include <string>

class RandomPassword {
    std::string sw_chars;
    int min_length;
    int max_length;
    std::string pass;

public:
    RandomPassword (const std::string& charts, int min, int max);
    
    std::string operator()();
    operator std::string() const;
};