#pragma once
#include <string>

struct Patient {
    std::string name;
    int id;

    std::string toString() const {
        return std::to_string(id) + " " + name;
    }
};