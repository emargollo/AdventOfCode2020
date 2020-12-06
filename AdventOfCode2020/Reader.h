#pragma once

#include "pch.h"

// See:
// https://stackoverflow.com/a/1567703/33758
// https://github.com/watmough/Advent-of-Code-2018/blob/master/reader.hpp


class line {
    std::string data;
public:
    friend std::istream& operator>>(std::istream& is, line& l) {
        std::getline(is, l.data);
        return is;
    }
    operator std::string() const { return data; }
};

std::vector<std::string> read_input(std::istream& ifs);

std::vector<int> read_ints(std::istream& ifs);