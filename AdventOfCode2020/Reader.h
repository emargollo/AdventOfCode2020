#pragma once

// See:
// https://stackoverflow.com/a/1567703/33758
// https://github.com/watmough/Advent-of-Code-2018/blob/master/reader.hpp

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>

class line {
    std::string data;
public:
    friend std::istream& operator>>(std::istream& is, line& l) {
        std::getline(is, l.data);
        return is;
    }
    operator std::string() const { return data; }
};

std::vector<std::string> read_input(std::istream& ifs)
{
    std::vector<std::string> lines;
    std::copy(std::istream_iterator<line>(ifs),
        std::istream_iterator<line>(),
        std::back_inserter(lines));
    return lines;
}

std::vector<int> read_ints(std::istream& ifs)
{
    std::vector<int> lines;
    std::transform(std::istream_iterator<line>(ifs),
        std::istream_iterator<line>(),
        std::back_inserter(lines), [&](const line& l) {return std::stoi(l); });
    return lines;
}